<?php

/**
 * @file
 * LDAPGroups API function documentation
 */

/**
 * Allows an LDAP user's set of ldap groups be altered or added to.
 *
 * This hook is called after the group detection methods defined in
 * the admin UI have been processed but before any access rules or role
 * mapping has been done..
 *
 * @param Array $groups An array whose values are the user's groupsr
 * @param LDAPInterface $ldap LDAP server interface object bound to server as ldap user.
 * @param String $dn The DN for the user being processed.
 * @param String $name The user's LDAP user name.
 */
function hook_ldap_user_groups_alter( &$groups, $ldap, $dn, $name ) {
  // Some example code to add a group that is the parent on the
  // user's dn, e.g. cn=Bob Admin,ou=admins,ou=dept1,dc=myorg will have a
  // group added like:  ou=admin,ou=dept1,dc=myorg.  This can then be used
  // in access rules or role mapping.
  $parts = explode(",", $dn, 2);
  $groups[] = $parts[1];
}
/**
 * Allows the roles an ldap user will be assigned to be altered.
 *
 * This hook is called after the mapping defined in the admin ui has been
 * performed but before the user has been granted a role.
 *
 * @param Array $roles An array who's values are role names.
 * @param Object $account The user object
 * @param String $dn The user's ldap dn.
 * @param Array $groups All of the user's ldap groups found
 * @param Array $filtered_groups The user's groups after filtered by mapping rules.
 */
function hook_ldap_user_roles_alter(&$roles, $account, $dn, $groups, $filtered_groups ) {
  // Some example code to add a role if the user is in two groups
  if ( in_array("cn=Joplin Fans,ou=Groups,dc=myorg", $groups ) && in_array("cn=Morton Fans,ou=Groups,dc=myorg", $groups )) {
    if ( ! in_array("Ragtime", $roles)) {
      $roles[] = "Ragtime";
    }
  }
}