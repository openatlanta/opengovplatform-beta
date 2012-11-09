<?php

/**
 * @file
 * LDAPAuth API function documentation
 */

/**
 * hook_ldapauth_create
 *
 * Ldapauth will invoke this after a new Drupal user has been created from
 * the LDAP data and saved.
 *
 * @param User $account The user object for the new user.
 */
function hook_ldapauth_create( $account ) {
  // Some example code to create an e-mail if ldap didn't provide one
  if ( $account->name == $account->mail ) {
    user_save($account, array( 'mail' => $account->name . "@mydomain.com", ));
  }
}
/**
 * hook_default_ldap_servers
 *
 * Called by features revert and rebuild hooks
 */
function hook_default_ldap_servers() {

}

/**
 * Perform alterations of ldap attributes before query is made.
 *
 * To avoid excessive attributes in an ldap query, modules should
 * alter attributes needed based on $op parameter
 *
 * See ldapauth_attributes_needed() function.
 *
 * @param array $attributes
 *   array of attributes to be returned from ldap queries
 * @param enum $op
 *   context query will be run in. Should be one of the LDAPATUH_SYNC_CONTEXT* constants.
 * @param mixed $server
 *   server id (sid) or server object.
 *
 */
function hook_ldap_attributes_needed_alter(&$attributes, $op, $server) {
  // Sample code to add homedirectory attribute to all standard calls..

  $attributes[] = 'dn';  // DN is minimum attribute for all ops.

  if ( $server ) {
    $ldap_server = is_object( $server ) ? $server : ldapauth_server_loade($server);

    switch ($op) {
      case LDAPAUTH_SYNC_CONTEXT_AUTHENTICATE_DRUPAL_USER:
      case LDAPAUTH_SYNC_CONTEXT_INSERT_DRUPAL_USER:
      case LDAPAUTH_SYNC_CONTEXT_UPDATE_DRUPAL_USER:
        $attributes[] = 'homedirectory';
        break;
    }
  }
}
/**
 * Called if PUID attribute is defined but a valid LDAP user does not have
 * this attribute (or is empty).
 *
 * This is intended to allow modules to generate a PUID for new users if needed.
 * Note that LDAPAuth will NOT write this to LDAP.  The implementor will need
 * to do this.
 *
 * @param String $puid The PUID (empty or null)
 * @param String $dn The user's dn
 * @param Integer $sid The id of server the user was found on.
 */
function hook_ldap_user_puid_alter( &$puid, $name, $dn, $sid) {

}
/**
 * Called after LDAP user has been authenticated but before the drupal
 * user mapping/creation done.
 *
 * Allows modules to alter the drupal account name that maps to an ldap account.
 * For example, adding a prefix or suffix based on server.
 *
 * @param String $name The name to alter
 * @param LDAPInterface $ldap LDAP server interface object bound to server as ldap user.
 * @param String $dn The DN for the authenticated user
 */
function hook_ldap_drupal_user_name_alter( &$name, $ldap, $dn ) {
  // Some example code to add the server machine name to the drupal name
  // E.g. LDAP user on server AD1 with sAMAccount=jsmith will map to drupal
  // user AD1-jsmith.  While LDAP user on server OL1 with uid=jsmith will
  // map to drupal user OL1-jsmith.
  $server = ldapauth_server_load($ldap->getOption('sid'));
  $name = $server->machine_name . "-" . $name;
}
/**
 * Allow other modules (e.g. ldapgroups) to deny ldap user access to
 * the server.
 *
 * Called after ldap user authenticated and mapped to Drupal account (if any)
 * but before new account creation / existing account updates.
 *
 * @param boolean $denied If set to TRUE, the account will be denied.
 *                        Implementors should not reset to FALSE.
 * @param LDAPInterface $ldap LDAP server interface object bound to server as ldap user.
 * @param String $name The ldap user name (from login form)
 * @param String $dn The DN for the authenticated user
 * @param Object $account The local drupal account object or FALSE if none found.
 */
function hook_ldap_user_deny_alter( &$denied, $ldap, $name, $dn, $account ) {
  // Some example code to deny if homedirectory attribute not set
  $ldap = ldapauth_user_lookup_by_dn($ldap, $dn, LDAPAUTH_SYNC_CONTEXT_AUTHENTICATE_DRUPAL_USER);
  if ( ! isset( $ldap['homedirectory'][0] )) { //Note attribute name must be lowercase
    $denied = TRUE;
  }
}
