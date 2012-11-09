<?php

/**
 * @file
 * The core functions that ldapauth supplies for submodules.  Will be included
 * by default by ldapauth.
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Server Information CRUD functions

/**
 * Retrieve server setting object by sid or machine_name
 * ( menu load function too)
 *
 * @param Mixed $sid Either the sid number or the machine name
 * @param boolean $reset  Cache is cleared if true.
 * @return The server object or FALSE
 */
function ldapauth_server_load( $sid, $reset=FALSE ) {
  static $servers = array();

  if ( $reset ) {
    $servers = array();
  }
  if ( isset($servers[$sid]) ) {
    return $servers[$sid];
  }

  if ( is_numeric($sid) ) {
    $where = "sid = %d";
  }
  else {
    $where = "machine_name = '%s'";
  }
  $server = db_fetch_object(
    db_query("SELECT * FROM {ldapauth} WHERE " . $where, $sid));
  $servers[$sid] = $server;
  return $server;
}
/**
 * Retrieve server settings by human name.
 *
 * @param String $name The description name of the server.
 * @return Object or FALSE if not found.
 */
function ldapauth_server_load_by_name( $name ) {
  $server = db_fetch_object(db_query("SELECT * FROM {ldapauth} WHERE name = '%s'", $name));
  if ( ! $server ) {
    return FALSE;
  }
  return $server;
}
/**
 * Retrieve all servers from database.
 *
 * @param Boolean $reset Clear the static cache if TRUE
 * @return An array of server objects ordered by weight with sid as key.
 */
function ldapauth_server_load_all( $reset=FALSE ) {
  static $servers = array();
  if ( $reset ) {
    $servers = array();
  }

  if ( empty($servers) || $reset ) {
    $results = db_query("SELECT * FROM {ldapauth} ORDER BY weight");
    while ($server = db_fetch_object($results)) {
      $servers[$server->sid] = $server;
    }
  }
  return $servers;
}
/**
 * Create/Update server settings... updates if $server->sid is set or not.
 * Uses machine_name as the key field for features.
 *
 * @param Mixed $server Server settings to save as object or array
 * @param Boolean $quiet If true, no success message will be displayed to user.
 * @param Boolean $use_sid If true, use sid to update entry rather than machine name.
 */
function ldapauth_server_save( &$server, $quiet=FALSE, $use_sid=FALSE ) {
  if ( is_array($server)) {
    $server = (object)$server;
    $array = TRUE;
  }
  else {
    $array = FALSE;
  }
  if ( isset($server->sid ) ) {
    $type = "updated";
    if ( $use_sid ) {
      $update = 'sid';
    }
    else {
      $update = 'machine_name';
    }
  }
  else {
    $type = "added";
    $update = array();
  }
  $params = array('%name' => $server->name, '%type' => $type);
  if ($rc = drupal_write_record('ldapauth', $server, $update)) {
    if ( ! $quiet ) {
      drupal_set_message(t('Server settings for %name have been %type.', $params));
    }
    watchdog('ldapauth', 'LDAP Configuration %name has been %type.', $params);
  }
  else {
    drupal_set_message(t('Failed to write the server settings for %name .', array('%name' => $server->name)), 'warning');
  }
  if ( $array ) {
    $server = ( array ) $server;
  }
  return $rc;
}
/**
 * Delete server settings
 *
 * @param Mixed $server A server object, array, or an integer sid.
 * @param Boolean $quiet
 */
function ldapauth_server_delete( $server, $quiet=FALSE ) {
  if ( is_numeric( $server ) ) {
    $server = ldapauth_server_load($server);
  }
  elseif ( is_array($server)) {
    $server = (object)$server;
  }
  if ( $server && isset($server->sid) ) {
    ldapauth_userinfo_delete_by_sid($server);
    db_query("DELETE FROM {ldapauth} WHERE sid = %d", $server->sid);
    if ( ! $quiet ) {
      drupal_set_message(t('LDAP Configuration %name has been deleted.', array('%name' => $server->name)));
    }
    watchdog('ldapauth', 'LDAP Configuration %name has been deleted.', array('%name' => $server->name));
  }
}
//////////////////////////////////////////////////////////////////////////////
// LDAP User Information CRUD functions

/**
 * Create / Update a record in the ldapauth_users table.
 *
 * @param Mixed $userinfo Object or Array containing record info.
 */
function ldapauth_userinfo_save( $userinfo ) {
  if ( is_array($userinfo)) {
    $userinfo = (object)$userinfo;
    $array = TRUE;
  }
  else {
    $array = FALSE;
  }
  if ( isset($userinfo->luid ) ) {
    $update = 'luid';
  }
  if (!($rc = drupal_write_record('ldapauth_users', $userinfo, $update))) {
    drupal_set_message(t('Failed to write the ldap user info for uid: %name .', array('%name' => $userinfo->uid)), 'warning');
  }
  if ( $array ) {
    $userinfo = ( array ) $userinfo;
  }
  return $rc;
}
/**
 * Load a ldapauth_user record
 *
 * @param unknown_type $luid
 */
function ldapauth_userinfo_load( $luid ) {
  $userinfo = db_fetch_object(
    db_query("SELECT * FROM {ldapauth_users} WHERE luid = '%s'", $luid));
  return $userinfo;
}
/**
 * Load a ldapauth_user record by puid
 *
 * @param String $puid The users puid (after convertion from binary if needed).
 */
function ldapauth_userinfo_load_by_puid( $puid ) {
  $userinfo = db_fetch_object(
    db_query("SELECT * FROM {ldapauth_users} WHERE puid = '%s'", $puid));
  return $userinfo;
}
/**
 * Load a ldapauth_user record by uid
 *
 * @param int $uid The user's uid
 */
function ldapauth_userinfo_load_by_uid( $uid ) {
  $userinfo = db_fetch_object(
    db_query("SELECT * FROM {ldapauth_users} WHERE uid = %d", $uid));
  return $userinfo;
}/**
 * Delete a ldapauth_users record.
 *
 * @param Mixed $userinfo Either the luid or the full object to delete
 */
function ldapauth_userinfo_delete( $userinfo ) {
  if ( is_numeric( $userinfo ) ) {
    $userinfo = ldapauth_userinfo_load($userinfo);
  }
  elseif ( is_array($userinfo)) {
    $userinfo = (object)$userinfo;
  }
  if ( $userinfo && isset($userinfo->luid) ) {
    db_query("DELETE FROM {ldapauth_users} WHERE luid = %d", $userinfo->luid);
  }
}
/**
 * Clear all entries from {ldapauth_users} who match the given server id.
 *
 * @param Mixed $sid A server object or sid
 */
function ldapauth_userinfo_delete_by_sid( $server ) {
  if ( isset($server->sid ) ) {
    $sid = $server->sid;
  }
  else {
    $sid = $server;
  }
  if ( is_numeric($sid)  ) {
    db_query("DELETE FROM {ldapauth_users} WHERE sid = %d", $sid);
  }
}
//////////////////////////////////////////////////////////////////////////////
// Attribute search functions.
/**
 * get array of required attributes for an ldap query.
 *
 * The op parameter should be one of the LDAPAUTH_SYNC_CONTEXT* constants.
 *
 * @param string $op is operation being performed
 * @param string $sid server id being used
 */
function ldapauth_attributes_needed($op, $sid = NULL, $reset=FALSE) {
  static $attributes = array();
  if ( $reset ) {
    $attributes = array();
  }
  if (!isset($attributes[$sid][$op])) {
    drupal_alter('ldap_attributes_needed', $attributes[$sid][$op], $op, $sid);
    // attributes array needs to have no gaps of ldap_search(), ldap_read(), ldap_list() so apply array_values()
    $attributes[$sid][$op] = array_values(array_unique($attributes[$sid][$op]));
  }
  return $attributes[$sid][$op];
}
//////////////////////////////////////////////////////////////////////////////
// PUID Common functions
/**
 * Extracts the puid value from an ldap search result with binary handling
 *
 * @param Mixed $server The server object or sid
 * @param The drupal user name
 * @param Array $ldap_entry LDAP search or retrieveAttributes result.
 */
function ldapauth_extract_puid( $server, $name, $ldap_entry ) {
  if ( is_numeric( $server )) {
    $server = ldapauth_server_load($server);
  }
  // DO NOT CONVERT TO Drupal STRING FUNCTIONS AS CODER SUGGESTS...
  // These are byte operations.
  $puid = $ldap_entry[strtolower($server->puid_attr)][0];
  if ( $puid && $server->binary_puid ) {
    if (strlen($puid) == 16) {  // Assume a binary GUID ala MS
      $hex_string = bin2hex($puid);
      // (MS?) GUID are displayed with first three GUID parts as "big endian"
      // Doing this so String value matches what other LDAP tool displays for AD.
      $puid=strtoupper(substr( $hex_string, 6, 2) . substr( $hex_string, 4, 2) .
        substr( $hex_string, 2, 2) . substr( $hex_string, 0, 2) . '-' .
        substr( $hex_string, 10, 2) . substr( $hex_string, 8, 2) . '-' .
        substr( $hex_string, 14, 2) . substr( $hex_string, 12, 2) . '-' .
        substr( $hex_string, 16, 4) . '-' . substr( $hex_string, 20, 12));
    }
    else {
      $puid = bin2hex($puid);
    }
  }
  if ( empty($puid) ) {
     // Give other modules a chance to create a puid if needed.
     drupal_alter('ldap_user_puid', $puid, $name, $ldap_entry['dn'], $server->sid);
  }
  return $puid;
}
/**
 * Create a "binary safe" LDAP search filter for finding objects from puid.
 *
 * @param Mixed $server Server object or sid
 * @param String $puid The puid value from ldapauth_users
 */
function ldapauth_puid_filter( $server, $puid ) {
  if ( is_numeric( $server )) {
    $server = ldapauth_server_load($server);
  }
  $filter = $server->puid_attr . "=";
  $match = '';
  if ( $server->binary_puid ) {
    // Is it a simple Hex string
    if ( preg_match('/^[a-f0-9]+$/i', $puid ) ) {
      for ( $i=0; $i < strlen($puid); $i=$i+2 ) {
        $match .= '\\' . substr($puid, $i, 2);
      }
    }
    elseif ( preg_match('/^[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}$/i', $puid)) {
      // Reconstruct proper "memory" order from GUID string.
      $hex_string = str_replace('-', '', $puid);
      $puid = substr( $hex_string, 6, 2) . substr( $hex_string, 4, 2) .
        substr( $hex_string, 2, 2) . substr( $hex_string, 0, 2) .
        substr( $hex_string, 10, 2) . substr( $hex_string, 8, 2) .
        substr( $hex_string, 14, 2) . substr( $hex_string, 12, 2) .
        substr( $hex_string, 16, 4) . substr( $hex_string, 20, 12);
      for ( $i=0; $i < strlen($puid); $i=$i+2 ) {
        $match .= '\\' . substr($puid, $i, 2);
      }
    }
  }
  else {
    $match = $puid;
  }
  return $filter . $match;
}
/**
 * Map an LDAP user to a Drupal user account if one exists.
 *
 * @param LDAPInterface $ldap An initialized LDAP server interface object.
 * @param String $name The user name (from login form)
 * @param String $dn The user's dn
 * @param String $error An error message or '' if no errors.  NOTE: Errors NOT reported via watchdog
 * @param String $puid Save an ldap query if the PUID is already known (e.g ldapsync)
 *
 * @return A user object, FALSE (user not found) or NULL (if error)
 */
function ldapauth_drupal_user_lookup( $ldap, $name, $dn, &$error, $puid=NULL ) {

  $error = '';
  if (!$ldap) {
    $error = t('LDAPInterface not initialized in ldapauth_drupal_user_lookup!');
    return NULL;
  }

  $sid = $ldap->getOption('sid');

  // If a PUID attribute is set, then use this to map users
  if ( $ldap->getOption('puid_attr')) {
    if ( ! $puid ) {
      $ldap_entry = ldapauth_user_lookup_by_dn($ldap, $dn, LDAPAUTH_SYNC_CONTEXT_AUTHENTICATE_DRUPAL_USER);
      if ( empty($ldap_entry )) {
        $error = t("Error looking up user in LDAP:  Supplied dn not found! sid=%sid dn=%dn", array('%sid' => $sid, '%dn' => $dn));
        return NULL;
      }
      $puid = ldapauth_extract_puid($sid, $name, $ldap_entry);
    }

    // Try to get PUID to UID mapping.
    if ( ! empty($puid) ) {
      $user_info = ldapauth_userinfo_load_by_puid( $puid );
      // Found matching ldapauth_users entry.  Return this users.
      if ( isset($user_info->uid ) ) {
        $account = user_load($user_info->uid);
        $account->ldap_puid = $puid;
        return $account;
      }
    }
    else {
      $error = t("LDAP user did not have required PUID attribute, %puid_attr! sid=%sid dn=%dn", array('%puid_attr' => $ldap->getOption('puid_attr'), '%sid' => $sid, '%dn' => $dn));
      return NULL;
    }

    // Have PUID but no matching userinfo, then see if entry needs to be rebuilt.
    // Most likely one of the following:
    //   Converting from prePUID to PUID;
    //   Changed PUID attribute; or
    //   Server re-created with new sid.
    // TODO: Make this configurable?
    $drupal_name = ldapauth_drupal_user_name($name, $ldap, $dn);;
    $account = user_load(array('name' => $drupal_name));
    if ( ! $account ) {
      return FALSE;
    }
    // Does the name map to an existing LDAP related account.
    if ( isset($account->ldap_authentified) ) {
      $user_info = ldapauth_userinfo_load_by_uid( $account->uid );
      // No user with different PUID
      if ( empty( $user_info )) {
        // DNs match.
        if ( drupal_strtolower($account->ldap_dn) == drupal_strtolower($dn)) {
          $old_server = ldapauth_server_load($account->ldap_config);
          // Do sids match or old sid does not exist
          if ( $account->ldap_config == $sid || empty( $old_server )) {
            $user_info = array(
              'uid' => $account->uid,
              'sid' => $sid,
              'machine_name' => $ldap->getOption('machine_name'),
              'dn' => $dn,
              'puid' => $puid,
            );
            ldapauth_userinfo_save($user_info);
            $account->ldap_puid = $puid;
            return $account;
          }
        }
      }
      else {
        $error = t('User, %name, already associated with a different LDAP user', array('%name' => $name));
        return NULL;
      }
    }
    // Return normal drupal account so login process can decide to map or not.
    $account->ldap_puid = $puid;
    return $account;
  }
  // Not using PUID so just use name.
  else {
    $drupal_name = ldapauth_drupal_user_name($name, $ldap, $dn);;
    $account = user_load(array('name' => $drupal_name));

    if ( ! $account ) {
      return FALSE;
    }
    // Double check that ldap user matches this account.
    if ( $account->ldap_authentified ) {
      // Do DNs map
      if ( drupal_strtolower($account->ldap_dn) == drupal_strtolower($dn)) {
        $old_server = ldapauth_server_load($account->ldap_config);
        // Do sids match or old sid does not exist
        if ( $account->ldap_config == $sid || empty( $old_server )) {
          $account->ldap_puid = $name;  // Default if puid attr not set.
          return $account;
        }
      }
      return FALSE;
    }
    $account->ldap_puid = $name;  // Default if puid attr not set.
    return $account;
  }
}
/**
 * Create a new Drupal user from an LDAP user entry with checks to ensure that:
 *
 * The admin settings allow account creation
 * The user name is unique.
 * The e-mail is unique and not a reserved address.
 * If PUID are used that the PUID is unique and not null.
 *
 * @param LDAPInterface $ldap An initialized LDAP server Interface object
 * @param String $name The LDAP user name/login name.  If Null, user name will be extracted from attributes.
 * @param Mixed $ldap_user The user's dn or and with the user's ldap attributes.
 * @param String $error An error message or '' if no errors.  Errors also logged via watchdog.
 * @return The new user object or FALSE if an error occured.
 */
function ldapauth_drupal_user_create( $ldap, $name, $ldap_user, &$error ) {

  if ( is_string( $ldap_user ) ) {
    $is_dn = TRUE;
    $dn = $ldap_user;
  }
  elseif ( isset($ldap_user['dn'])) {
    $is_dn = FALSE;
    $dn = $ldap_user['dn'];
  }
  else { // Hmm invalid entry maybe should log this?
    $error = t('Invalid LDAP information supplied!  Could not find dn.');
    watchdog('ldapauth', 'Drupal user %name could not be created because the ldap_user parameter did not contain a valid dn.', array('%name' => $name), WATCHDOG_ERROR);
    return FALSE;
  }

  $error = '';
  // Has the admin turned of automatic account creation?
  if (!variable_get('ldapauth_create_users', TRUE)) {
    $error = t('Your account is not authorized to access this system.');
    watchdog('ldapauth', 'The valid LDAP account %name was denied access because there was no matching Drupal account.', array('%name' => $name), WATCHDOG_ERROR);
    return FALSE;
  }

  if ( $is_dn ) {
    $ldap_user = ldapauth_user_lookup_by_dn($ldap, $dn, LDAPAUTH_SYNC_CONTEXT_AUTHENTICATE_DRUPAL_USER );
  }

  // Get drupal name from ldap uid name
  if ( ! $name ) {
    $name_attr = $ldap->getOption('user_attr') ? $ldap->getOption('user_attr') : LDAPAUTH_DEFAULT_USER_ATTR;
    $name = isset($ldap_user[$name_attr][0]) ? $ldap_user[$name_attr][0] : (isset($ldap_user[drupal_strtolower($name_attr)][0]) ? $ldap_user[drupal_strtolower($name_attr)][0] : $name);
  }
  // Let other modules change this if needed.
  $drupal_name = ldapauth_drupal_user_name($name, $ldap, $dn);
  // Check for unique name probably already done but double check to be sure.
  if ( user_load(array('name' => $drupal_name) ) ) {
    watchdog('ldapauth', 'LDAP user with DN %dn has a naming conflict with a local Drupal user %name', array('%dn' => $dn, '%name' => $drupal_name), WATCHDOG_ERROR);
    $error = t('Another user already exists in the system with the same login name. You should contact the system administrator in order to solve this conflict.');
    return FALSE;
  }


  if ( $ldap_user) {
    // If mail attribute is missing, set the name as mail.
    $init = $mail = key_exists(($ldap->getOption('mail_attr') ? $ldap->getOption('mail_attr') : LDAPAUTH_DEFAULT_MAIL_ATTR), $ldap_user) ? $ldap_user[$ldap->getOption('mail_attr')][0] : $name;

    // Check that the e-mail is not denied.
    if (drupal_is_denied('mail', $mail)) {
      $error = t('The name %name is registered using a reserved e-mail address and therefore could not be logged in.', array('%name' => $name));
      return FALSE;
    }

    // Check that e-mail is unique
    if ( $existing_user_by_email = user_load(array('mail' => $mail))) {
      $error = t('The e-mail address, %mail, associated with this account is already in use.', array('%mail' => $mail));
      watchdog('ldapauth', 'The valid LDAP account %name was denied access their email address, %mail, was already in use.', array('%name' => $name, '%mail' => $mail), WATCHDOG_ERROR);
      return FALSE;
    }

    $sid = $ldap->getOption('sid');

    // Validate / Create PUID entry.
    if ( $ldap->getOption('puid_attr') ) {
      $puid = ldapauth_extract_puid($sid, $name, $ldap_user);
      if ( empty($puid) ) {
        // Give other modules a chance to create a puid if needed.
        drupal_alter('ldap_user_puid', $puid, $name, $dn, $sid);
      }
      if ( empty($puid) ) {
        $error = t("This LDAP user entry was not configured properly (No PUID).  Please contact your system administrator.");
        watchdog('ldapauth', 'LDAP user did not have required PUID attribute! ldap_attr=%attr sid=%sid dn=%dn',
          array(
            '%attr' => $ldap->getOption('puid_attr'),
            '%sid' => $sid,
            '%dn' => $dn
          ),
          WATCHDOG_ERROR);
        return FALSE;
      }
      if ( ldapauth_userinfo_load_by_puid( $puid ) ) {
        $error = t("This LDAP user entry was not configured properly (Duplicate PUID).  Please contact your system administrator.");
        watchdog('ldapauth', 'A duplicate PUID was found! attr=%attr sid=%sid dn=%dn',
          array(
            '%attr' => $ldap->getOption('puid_attr'),
            '%sid' => $sid,
            '%dn' => $dn
          ),
          WATCHDOG_ERROR);
        return FALSE;
      };
    }
    else {
      $puid = $name; // default to $name for PUID.
    }

    // Use name as is set in the LDAP server.
    $name_attr = $ldap->getOption('user_attr') ? $ldap->getOption('user_attr') : LDAPAUTH_DEFAULT_USER_ATTR;
    $name_new = isset($ldap_user[$name_attr][0]) ? $ldap_user[$name_attr][0] : (isset($ldap_user[drupal_strtolower($name_attr)][0]) ? $ldap_user[drupal_strtolower($name_attr)][0] : $name);
    // Unless another module has altered it.
    if ( $drupal_name != $name ) {
      $name_new = $drupal_name;
    }
    // Generate a random drupal password. LDAP password will be used anyways.
    $pass_new = (LDAPAUTH_LOGIN_PROCESS == LDAPAUTH_AUTH_EXCLUSIVED || !LDAPAUTH_SYNC_PASSWORDS) ? user_password(20) : $pass;

    $new_user = array(
      'name' => $name_new,
      'pass' => $pass_new,
      'mail' => $mail,
      'init' => $init,
      'status' => 1,
      'authname_ldapauth' => $name,
      'ldap_authentified' => TRUE,
      'ldap_dn' => $ldap_user['dn'],
      'ldap_config' => $ldap->getOption('sid'),
      'ldap_name' => $name,
    );
    $account = user_save('', $new_user);

    // Save ldapauth_users info.
    $user_info = array(
      'uid' => $account->uid,
      'sid' => $sid,
      'machine_name' => $ldap->getOption('machine_name'),
      'dn' => $dn,
      'puid' => $puid,
    );
    ldapauth_userinfo_save($user_info);
    watchdog('ldapauth', 'New external user %name created from the LDAP server %server.', array('%name' => $name, '%server' => $ldap->getOption('name')), WATCHDOG_NOTICE, l(t('edit'), 'user/'. $user->uid .'/edit'));
    // Invoke post user creation hook.
    module_invoke_all('ldapauth_create', $account);
    return $account;
  }
  $error = t("Could not find dn entry! dn=%dn", array('%dn' => $dn));
  return FALSE;
}
/**
 * Retrieves required attributes for specific user and operation.
 *
 * @param LDAPInterface $ldap An initialized LDAP server Interface object
 * @param String $dn The LDAP user's dn
 * @param String $op The type of load operation (see LDAPAUTH_SYNC_CONTEXT* constants)
 * @param boolean $reset If true the cache will be cleared.
 * @return An array of the user's ldap attributes as defined by the operation.
 */
function ldapauth_user_lookup_by_dn( $ldap, $dn, $op, $reset=FALSE ) {
  static $ldap_user_cache = array();;

  if ( $reset ) {
    $ldap_user_cache = array();
  }

  if ( ! $ldap ) {  // Allow cache resets without lookup.
    return FALSE;
  }
  $sid = $ldap->getOption('sid');
  if ( ! isset( $ldap_user_cache[$op][$sid][$dn]) ) {
    $attrs = ldapauth_attributes_needed($op, $ldap->getOption('sid'));
    $ldap_user_cache[$op][$sid][$dn] = $ldap->retrieveAttributes($dn, $attrs );
  }
  return $ldap_user_cache[$op][$sid][$dn];
}
/**
 * Allow modules to do site dependent login form name to drupal account name
 * mapping.
 *
 * Calls the hook_ldap_drupal_user_name_alter function(s) once per name.
 *
 * @param String $name Name entered on login form (case insensitive match to user attr).
 * @param LDAPInterface $ldap Fully initialized LDAP server interface object
 * @param boolean $reset If true the cache will be cleared.
 * @param String $dn The DN that has been authenticated with LDAP.
 */
function ldapauth_drupal_user_name( $name, $ldap, $dn, $reset=FALSE ) {
  static $drupal_names = array();

  if ( $reset ) {
    $drupal_name = array();
  }
  if ( ! $name ) {  // Allow reset with no lookup.
    return FALSE;
  }

  if ( ! isset($drupal_names[$name])) {
    drupal_alter('ldap_drupal_user_name', $name, $ldap, $dn);
    $drupal_names[$name] = $name;
  }
  return $drupal_names[$name];
}
/**
 * Allows other modules (like ldapgroups) to deny an ldap user access to the
 * server.
 *
 * @param LDAPInterface $ldap Fully initialized LDAP server interface object
 * @param String $name The ldap user name (from login form)
 * @param String $dn The DN for the authenticated user
 * @param Object $account The local drupal account object or FALSE if none found.
 * @return TRUE is user is to be denied access.
 */
function ldapauth_user_denied( $ldap, $name, $dn, $account ) {
  $denied = FALSE;
  drupal_alter('ldap_user_deny', $denied, $ldap, $name, $dn, $account );
  return $denied;
}
