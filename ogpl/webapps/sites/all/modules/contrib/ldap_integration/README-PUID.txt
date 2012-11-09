
LDAP Integration Module - Persistent and Unique IDs (PUID)

Overview
========

LDAP Integration needs to map Drupal users to LDAP user.  Generally, just 
mapping via the user name works.  However, LDAP in enterprise settings can
be a very dynamic. People can change user names and e-mail addresses, be moved 
between LDAP trees (e.g. ou=Contract -> ou=Employee), and the like.

The PUID attribute can be used to better map LDAP users to Drupal users.  This
will allow LDAP Integration to definitively map an LDAP object to a Drupal user.

The PUID can be a site specific attribute such as employeeNumber.  It can also
use one of the various default attributes that LDAP servers supply for this
purpose.  Some examples are:

entryUUID - RFC 4530 standard operational attribute which the server assigns
            a unique GUID to each LDAP object.  OpenLDAP, Apache DS, and other
            impliment this.
            
objectGUID - Microsoft Active Directory standard attribute which get a unique
             GUID as well.  NOTE:  This is a binary attributes.

Note that most major LDAP servers currently have an attribute that supplies
this functionality, even if the don't support RFC 4530.  Review your server
documentation to determine what this is.
             
             
Using PUID with LDAP Integration
================================

The first step is make sure you have the latest version of LDAP Integration
install (after 4/24/2012) and have run UPDATE.php

Next, you can edit your LDAP server settings to define the attribute to use
for a PUID.

Once you define a PUID, new users will be automatically be associated with 
this as their accounts are created.  Existing users will be mapped to the
PUID as they log on.  With the next version of ldapsync, this can also be 
done by syncing the LDAP to Drupal users.

An existing Drupal user is mapped via the PUID to an LDAP user if the following
test are all true:

- The Drupal user name matches the Authenticated ldap user name attribute.
- The matching user is marked as an ldap user.
- The Drupal user's stored dn matches the ldap dn
- The Drupal user's server id matches the ldap server id or the Drupal sid does 
  not exist anymore (i.e. server deleted/recreated)
  
Note that if the matching user is not an ldap user, the User conflict settings
will be used to associate this or deny access.

Some Operational Notes
======================

The PUID LDAP to Drupal user mappings are cleared when:

- The PUID attribute is changed (or set initially) or
- The Server entry is deleted.

This should not have any major impact other than causing the "matching" rules
to come into play as existing users log in.  You may want to use ldapsync to
prevent any problems with name changes before the person logs in.


Note that not all tools and LDAP backup software will properly migrate 
the operational UUID attributes.  Many do, so make sure that your backup 
and recovery/migrate processes include the PUID attributes.

If your recover/migrate without these, you will have to clear the 
ldapauth_users info for the effected server(s).  This can be done by 
blanking out the PUID attribute, saving the server, then reentering the
PUID value and saving the server.  Existing users will be mapped according 
to the rules above. 

Developer Notes:
================

The PUID mapping information is stored in the ldapauth_users table and can be
managed by the ldapauth_userinfo_* CRUD functions in the ldap.core.inc file.

There are two hooks that can effect Drupal to LDAP user mapping.  These are:

/**
 * Called if the LDAP user's PUID attribute does not exist or is empty.
 */
hook_ldap_user_puid_alter( &$puid, $name, $dn, $sid)

This is a way for a site specific module to create or calculate PUID values for
users.  Note that implementors will need to save this to the LDAP entry since 
ldapauth may not have LDAP auth write priviledges.
   
/**
 * Called after the ldap user is authenticated but before the Drupal user
 * lookup/create process is done.
 */
hook_ldap_drupal_user_name_alter( &$name, $ldap, $dn )

This allows sites to use a custom module to define the Drupal user name that 
will be used to map to an LDAP user.  

For example, if you have multiple servers with a possiblity of duplicate user 
names, you can use this to prefix the Drupal name with the server machine name.
So, LDAP user jsmith on the Student server maps to Drupal user id student-jsmith
while jsmith on the Staff server maps to staff-jsmith.

With a PUID, both users can log on using jsmith and their password and be 
correctly mapped to different Drupal users.  Of course, if both users happen 
to choose the same password... there may be problems.
   
See the ldapauth.api.php file for argument details.
