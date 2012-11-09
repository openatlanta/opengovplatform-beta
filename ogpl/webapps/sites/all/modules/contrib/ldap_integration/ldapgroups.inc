<?php

/**
 * @file
 * ldapgroups include file.
 */

//////////////////////////////////////////////////////////////////////////////
// hook_user() functions

/**
 * Implements hook_user() login operation.
 *
 * @param Object $account A user object verified to be ldap_authentified.
 */
function ldapgroups_user_login(&$account) {

  // Don't do anything if disabled mode has been enabled.
  if ( _ldapgroups_ldap_info($account, 'ldapgroups_mappings_filter') == LDAPGROUPS_ROLE_MODE_DISABLED ) {
    return;
  }

  // Don't do anything until LDAP groups are configured in admin screens.
  if (! ldapgroups_is_configured($account->ldap_config))
    return;

  // Setup the global $_ldapgroups_ldap object.
  if (!_ldapgroups_ldap_init($account))
    return;

  // First, we figure out the appropriate groups.
  $groups = _ldapgroups_detect_groups($account);
  if ($groups === FALSE) {  // Hmm, could not contact LDAP so make no changes..
    return;
  }

  // Then, we take every LDAP mapped role from the user, later below
  // we'll grant back those deserved.
  $account->ldap_drupal_roles = isset($account->ldap_drupal_roles) ? $account->ldap_drupal_roles : array();
  foreach ($account->ldap_drupal_roles as $role) {
    _ldapgroups_deny_role($account, $role);
  }

  // Next, we apply site-specific rules.
  $filtered_groups = _ldapgroups_filter($account, $groups);

  // At this point, the roles are in the full DN format or role names.
  $roles = array();
  if (!empty($filtered_groups)) {
    foreach ($filtered_groups as $group) {
      $role = _ldapgroups_mapping($account, $group);
      $roles[] = $role;
    }
  }
  $roles = array_unique($roles);

  drupal_alter("ldap_user_roles", $roles, $account, $dn, $groups, $filtered_groups );

  foreach ($roles as $role ) {
    _ldapgroups_create_role($role);
    _ldapgroups_grant_role($account, $role);
  }

  // Store roles in the user object so we know which ones
  // were granted here.
  user_save($account, array('ldap_drupal_roles' => $roles));
}

//////////////////////////////////////////////////////////////////////////////
// Auxiliary functions

/**
 * Detect user groups from the LDAP.
 *
 * @param $account
 *   A user object that has already been checked if it is "ldap_authentified".
 *
 * @return An array of user groups, an empty array if none found and
 *         FALSE if none defined/could not search LDAP.
 */
function _ldapgroups_detect_groups($account) {
  global $_ldapgroups_ldap;

  // Nothing to do if there are no groups configured.
  if (! ldapgroups_is_configured($account->ldap_config))
    return FALSE;

  // First try to connect with the stored user's DN and password.
  // If unsuccessful, connect with the BINDDN and BINDPW stored in the database for this config.
  $dn = isset($_SESSION['ldap_login']['dn']) ? $_SESSION['ldap_login']['dn'] : '';
  $pass = isset($_SESSION['ldap_login']['pass']) ? $_SESSION['ldap_login']['pass'] : '';

  // If I try to connect using a blank dn and pass, I dont get an error until ldap_read,
  // so I just check to see if they would be blank, based on ldap_forget_passwords, and
  // make it read from the database.
  if (LDAPAUTH_FORGET_PASSWORDS || !$_ldapgroups_ldap->connect($dn, $pass)) {
    $row2 = db_fetch_object(db_query("SELECT binddn, bindpw FROM {ldapauth} WHERE sid = %d", $_ldapgroups_ldap->getOption('sid')));
    $dn = $row2->binddn;
    $pass = $row2->bindpw;
    if (!$_ldapgroups_ldap->connect($dn, $pass)) {
      watchdog('ldapgroups', "User login: user %name data could not be read in the LDAP directory", array('%name' => $account->name), WATCHDOG_WARNING);
      return FALSE;
    }
  }

  $groups = ldapgroups_groups_load($_ldapgroups_ldap, $account->ldap_dn, $account->name );

  $_ldapgroups_ldap->disconnect();
  return $groups;
}

/**
 * Create an array of LDAP groups related to a dn/user.
 *
 * @param LDAPInterface $ldap An initialized LDAP server interface object.
 * @param String $name The ldap user name (from login form)
 * @param String $dn The user's dn
 *
 * @return An array of user groups, an empty array if none found and
 *         FALSE if none defined/could not search LDAP.
 */
function ldapgroups_groups_load( $ldap, $dn, $name, $reset=FALSE ) {
  static $groups_cache = array();
  if ( $reset ) {
    $groups_cache = array();
  }
  if ( ! $ldap ) {  // allow cache clearing only calls.
    return FALSE;
  }

  if ( ! isset($groups_cache[$dn]) ) {
    $sid = $ldap->getOption('sid');

    // Nothing to do if there are no groups configured.
    if (! ldapgroups_is_configured($sid))
      return FALSE;

    // Strategy 1: group extracted from user's DN.
    $dn_groups = array();
    if (_ldapgroups_ldap_info($sid, 'ldapgroups_in_dn')) {
      $pairs = ldap_explode_dn($dn, 0);
      foreach ($pairs as $p) {
        $pair = explode('=', $p);
        if (drupal_strtolower(trim($pair[0])) == drupal_strtolower(_ldapgroups_ldap_info($sid, 'ldapgroups_dn_attribute')))
          $dn_groups[] = trim($pair[1]);
      }
    }

    // Strategy 2: groups in user attributes.
    $attrib_groups = array();
    if (_ldapgroups_ldap_info($sid, 'ldapgroups_in_attr')) {
      foreach (_ldapgroups_ldap_info($sid, 'ldapgroups_attr') as $attribute)
        $attrib_groups = array_merge($attrib_groups, $ldap->retrieveMultiAttribute($dn, $attribute));
    }

    // Strategy 3: groups as entries.
    $entries_groups = array();
    $ldapgroups_entries_attribute = _ldapgroups_ldap_info($sid, 'ldapgroups_entries_attribute');
    if (_ldapgroups_ldap_info($sid, 'ldapgroups_as_entries')) {
      foreach (_ldapgroups_ldap_info($sid, 'ldapgroups_entries') as $branch) {
        $entries = $ldap->search($branch, $ldapgroups_entries_attribute .'='. $dn, array($ldapgroups_entries_attribute));
        if (empty($entries) || $entries['count'] == 0)
          $entries = $ldap->search($branch, $ldapgroups_entries_attribute .'='. $name, array($ldapgroups_entries_attribute));
        foreach ($entries as $entry) {
          if (isset($entry['dn']))
            $entries_groups[] = $entry['dn'];
        }
      }
    }
    $groups = array_unique(array_merge($dn_groups, $attrib_groups, $entries_groups));

    // Allow other modules to modify user groups.
    drupal_alter("ldap_user_groups", $groups, $ldap, $dn, $name );

    $groups_cache[$dn] = $groups;
  }

  return $groups_cache[$dn];
}

/**
 * Grant a user with a role.
 *
 * @param $account
 *   A user object.
 * @param $rolename
 *   A name of the role.
 *
 * @return
 */
function _ldapgroups_grant_role($account, $rolename) {
  $result = db_query("SELECT * FROM {role} WHERE LOWER(name) = LOWER('%s')", $rolename);
  if ($row = db_fetch_object($result)) {
    $result = db_query("SELECT * FROM {users_roles} WHERE uid = %d AND rid = %d", $account->uid, $row->rid);
    if (!db_fetch_object($result)) {
      db_query("INSERT INTO {users_roles} (uid, rid) VALUES (%d, %d)", $account->uid, $row->rid);
    }
  }
}

/**
 * Deny a user with a role.
 *
 * @param $account
 *   A user object.
 * @param $rolename
 *   A name of the role.
 *
 * @return
 */
function _ldapgroups_deny_role($account, $rolename) {
  $result = db_query("SELECT * FROM {role} WHERE LOWER(name) = LOWER('%s')", $rolename);
  if ($row = db_fetch_object($result)) {
    $result = db_query("SELECT * FROM {users_roles} WHERE uid = %d AND rid = %d", $account->uid, $row->rid);
    if (db_fetch_object($result)) {
      db_query("DELETE FROM {users_roles} WHERE uid = %d AND rid = %d", $account->uid, $row->rid);
    }
  }
}

/**
 * Create a new role.
 *
 * @param $rolename
 *   A name of the role.
 *
 * @return
 */
function _ldapgroups_create_role($rolename) {
  $result = db_query("SELECT * FROM {role} WHERE LOWER(name) = LOWER('%s')", $rolename);
  if (!($row = db_fetch_object($result)))
    db_query("INSERT INTO {role} (name) VALUES ('%s')", $rolename);
}

/**
 * Filters groups only to the groups defined in the role mapping.
 *
 * @param $groups
 *   An array of the LDAP groups.
 *
 * @return
 *   An array of the filtered groups.
 */
function _ldapgroups_filter($account, $groups) {

  // Filter by php code first
  if ($code = _ldapgroups_ldap_info($account, 'ldapgroups_filter_php')) {
    $groups = drupal_eval($code);
  }

  if (_ldapgroups_ldap_info($account, 'ldapgroups_mappings_filter') == LDAPGROUPS_ROLE_MODE_USE_MAP && count(_ldapgroups_ldap_info($account, 'ldapgroups_mappings') > 0)) {
    $groups_new = array();
    foreach ($groups as $group) {
      foreach (_ldapgroups_ldap_info($account, 'ldapgroups_mappings') as $group_approved => $role) {
        if (strcasecmp($group_approved, $group) == 0) {
          $roles = explode(',', $role);
          foreach ( $roles as $r ) {
            $groups_new[] = trim($r);
          }
        }
      }
    }
    $groups = array_unique($groups_new);
  }
  return $groups;
}

/**
 * Maps LDAP group name to a Drupal role.
 *
 * @param $account
 *   A user object or sid.
 * @param $group
 *   A LDAP group name.
 *
 * @return
 *   An Drupal role.
 */
function _ldapgroups_mapping($account, $group) {
  $ldapgroups_mappings = _ldapgroups_ldap_info($account, 'ldapgroups_mappings');
  if (isset($ldapgroups_mappings[$group]))
    return $ldapgroups_mappings[$group];
  elseif (preg_match('/^[^=]+=([^,]+),.*$/', $group, $matches))
    return $matches[1];
  else
    return $group;
}

/**
 * Initiates the LDAPInterfase class.
 *
 * @param $sid
 *   A server ID or user object.
 *
 * @return
 */
function _ldapgroups_ldap_init($sid) {
  global $_ldapgroups_ldap;

  if (!($sid = is_object($sid) ? (isset($sid->ldap_config) ? $sid->ldap_config : NULL) : $sid))
    return;

  $server = ldapauth_server_load($sid);

  if (! empty($server) && $server->status == 1 ) {
    $_ldapgroups_ldap = new LDAPInterface();
    $_ldapgroups_ldap->setOption('sid', $sid);
    $_ldapgroups_ldap->setOption('name', $server->name);
    $_ldapgroups_ldap->setOption('machine_name', $server->machine_name);
    $_ldapgroups_ldap->setOption('server', $server->server);
    $_ldapgroups_ldap->setOption('port', $server->port);
    $_ldapgroups_ldap->setOption('tls', $server->tls);
    $_ldapgroups_ldap->setOption('enc_type', $server->enc_type);
    $_ldapgroups_ldap->setOption('basedn', $server->basedn);
    $_ldapgroups_ldap->setOption('user_attr', $server->user_attr);
    $_ldapgroups_ldap->setOption('binddn', $server->binddn);
    $_ldapgroups_ldap->setOption('bindpw', $server->bindpw);
    return $_ldapgroups_ldap;
  }
}

/**
 * Retrieve the saved ldapgroups saved setting.
 *
 * @param $sid
 *   A server ID or user object.
 * @param $req
 *   An attribute name.
 *
 * @return
 *   The attribute value.
 */
function _ldapgroups_ldap_info($sid, $req) {
  if (!($sid = is_object($sid) ? (isset($sid->ldap_config) ? $sid->ldap_config : NULL) : $sid))
    return;

  $server = ldapauth_server_load($sid);

  switch ($req) {
    case 'ldapgroups_in_dn':
      return $server->ldapgroups_in_dn;
    case 'ldapgroups_dn_attribute':
      return !empty($server->ldapgroups_dn_attribute) ? $server->ldapgroups_dn_attribute : LDAPGROUPS_DEFAULT_DN_ATTRIBUTE;
    case 'ldapgroups_in_attr':
      return $server->ldapgroups_in_attr;
    case 'ldapgroups_attr':
      return !empty($server->ldapgroups_attr) ? unserialize($server->ldapgroups_attr) : array();
    case 'ldapgroups_as_entries':
      return $server->ldapgroups_as_entries;
    case 'ldapgroups_entries':
      return !empty($server->ldapgroups_entries) ? unserialize($server->ldapgroups_entries) : array();
    case 'ldapgroups_entries_attribute':
      return !empty($server->ldapgroups_entries_attribute) ? $server->ldapgroups_entries_attribute : LDAPGROUPS_DEFAULT_ENTRIES_ATTRIBUTE;
    case 'ldapgroups_mappings':
      return !empty($server->ldapgroups_mappings) ? unserialize($server->ldapgroups_mappings) : array();
    case 'ldapgroups_mappings_filter':
      return $server->ldapgroups_mappings_filter;
    case 'ldapgroups_filter_php':
      return $server->ldapgroups_filter_php;
    case 'ldapgroups_groups':
      return !empty($server->ldapgroups_groups) ? unserialize($server->ldapgroups_groups) : array();
  }
}
/**
 * Retrieve the ldapgroups access rules for the specified server.
 *
 * @param int $sid The server id to get the access rules for.
 * @return An array of access rules with each element an array of type and group
 */
function ldapgroups_access_rules( $sid, $reset=FALSE ) {
  static $acl = array();
  if ( $reset ) {
    $acl = array();
  }
  if ( $sid === FALSE ) { // Allow resets without lookup.
    return;
  }
  if ( ! isset($acl[$sid])) {
    $config_info = _ldapgroups_ldap_info($sid, 'ldapgroups_groups');
    if ( empty($config_info) ) {
      $acl[$sid][] = array(LDAPGROUPS_RULE_TYPE_ALLOW, LDAPGROUPS_GROUP_ALL);
    }
    else {
      // All rule sets start with deny all
      $acl[$sid][] = array(LDAPGROUPS_RULE_TYPE_DENY, LDAPGROUPS_GROUP_ALL);
      // Is just a list of groups?
      if ( ! preg_match("/^(" . LDAPGROUPS_RULE_TYPE_ALLOW . ")|(" . LDAPGROUPS_RULE_TYPE_DENY . ")??[:]\s.*/i", $config_info[0] ) ) {
        foreach ( $config_info as $group ) {
          if ( ! empty ($group) ) {
            $acl[$sid][] = array(LDAPGROUPS_RULE_TYPE_ALLOW, $group);
          }
        }
      }
      // A valid ruleset
      else {
        foreach ( $config_info as $rule ) {
          if ( ! empty($rule) ) {
            $parts = explode(":", $rule, 2);
            $acl[$sid][] = array(drupal_strtoupper($parts[0]), trim($parts[1]));
          }
        }
      }
    }
  }
  return $acl[$sid];
}
function ldapgroups_is_configured( $sid ) {
  static $configured = array();

  if ( ! isset($configured[$sid]) ) {
    $configured[$sid] = (_ldapgroups_ldap_info($sid, 'ldapgroups_in_dn') || _ldapgroups_ldap_info($sid, 'ldapgroups_in_attr') || _ldapgroups_ldap_info($sid, 'ldapgroups_as_entries'));
  }
  return $configured[$sid];
}
