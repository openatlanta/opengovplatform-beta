
Content Profile Create User module for Drupal 6.x.
This module allows the creation of user from anonymous Contnent Profiles.

REQUIREMENTS
------------
* Email Field
* Content Profile

USAGE INSTRUCTIONS
------------------
Ensure that your Content Profile includes at least one Email Field.  This field 
will be used as the new user's email address.

Users can be created from one of several places: the Content Profile's node 
edit page, from admin/content/node, as a Views Bulk Operation, or from
admin/user/content_profile.  All locations save the node edit form allow for
bulk user creation.