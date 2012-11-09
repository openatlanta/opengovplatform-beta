$Id: README.txt,v 1.10.4.18 2010/10/04 19:12:10 michellec Exp $

CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Installation

INTRODUCTION
------------
Advanced Profile Kit (http://drupal.org/project/advanced_profile) provides building
blocks for putting together fancy user profile pages like those commonly found on social
networking sites.

INSTALLATION
------------
Since this is a kit module, it is not necessary to install this exactly as directed.
Depending on your experience, you can pick and choose which pieces to use to build your
unique profiles. The instructions here will get you up and running with the standard APK
profile.

Install and enable APK
  1) Copy the entire advanced_profile module directory into your normal directory for
     modules, usually sites/all/modules
  2) Enable Advanced Profile Kit in the "other" fieldset at ?q=admin/build/modules
  3) Copy advanced_profile_author-pane.tpl.php from the 'theme' directory inside of the
     'advanced_profile' project directory to the root of your theme directory. This
     is a customized version of the Author Pane template designed for APK. You can
     make further modifications to this if needed.

Install modules that APK uses (submodules needed are listed in parentheses). Remember
that none of these are required; they are simply the modules that APK will make use of.
  * Author Pane 2.x (Author pane) Also see the Author Pane project page for modules it
    supports to add more functionality.
  * Panels 3.x (Panels)
  * CTools (Chaos Tools, Page Manager)
  * Views 2.x (Views, Views content panes, Views UI)
  * CCK 2.x (Content, Content Copy, Fieldgroup, Option Widgets, Text)
  * Content Profile
  * Link (Link - grouped with CCK)
  * User Relationships (UR-API, UR-UI, UR-Views)
  * Statistics (part of core, needed for user visits pane)
  * Comment (part of core, needed for topics/replies/posts views)
  * Facebook-style Statuses for a user "wall". (Alternately you can add the
    comments/comment form and use comments on the node for this.)
  * If you are using User Relationships and the "Friends" view for it, I highly recommend
    ImageCache Profiles and its dependencies to be able to size the avatars.

Configure Advanced Profile Kit
  1) Change configuration settings by going to ?q=admin/settings/advanced-profile.
    a) Redirect from profile node to user page: When using nodes as profiles, you have
       the node sitting out there just like other nodes. This redirect will prevent
       anyone from visiting that node as it will redirect them to the profile page of
       the owner of the profile node.
    b) Text of user page view tab: Provides an easy way to change the tab text. You will
       need to clear the cache if you use this option.
    c) Number of entries: Enter the number of profile visits to show at one time.
    d) Show only the last visit from each user: If checked, a given person will only be
       listed once no matter how many times they visit.
    e) Granularity of time ago: The granularity on the profile vists list defaults to 2.
       Set it to 1 to take up less room or to 3 for more precision.
    f) Roles to exclude: Check any roles you don't want to show up on the list. Make note
       of the performance warning.

Create the user profile node type
  * The short version: import the contents of uprofile.full.export via content copy.
  * The long version: http://drupal.org/node/579468

Configure core
  1) Navigate to ?q=admin/user/settings and enable picture support if you want users to
     have avatars on their profiles.
  2) Configure statistics module:
      a) Navigate to ?q=admin/reports/settings
      b) Enable access log: Enabled

Set access control
  1) Navigate to ?q=admin/user/permissions
  2) Enable "administer advanced profile" for your admins
  3) Enable "access user profiles" for everyone that you want to be able to view user
     profiles.
  4) Enable "edit any uprofile content" for your admins so they can edit anyone's profile.
  5) Allow users to create profile nodes by giving them access to "create uprofile
     content" and "edit own uprofile content". You will not want to give them delete perms.

Configure the user profile page
  1) Navigate to ?q=admin/build/pages
  2) Enable the "user_view" system page. If this is not enabled, APK cannot take over
     the user profile page. If you are using APK in a custom way and don't wish to use
     it with Page Manager, you can leave this disabled.
  3) Once it is enabled, click edit on "user_view" to make any desired changes to the
     profile content or layout.

Theming the profile page
  APK does not enable any styles for the profile page by default. This is to prevent you
  from having to undo APK's styles before you can do your own styling but means that it
  looks pretty ugly until you style it. To give you a jump start, it comes with premade
  style sheets that you can add to your theme. If you would like to use a pre-made style,
  follow these steps:

  1) Navigate to the 'theme' directory inside of the 'advanced_profile' project directory.
  2) Copy the CSS file you want to use to your theme.
  3) Open the .info file of your theme and add stylesheets[all][] = FILENAME.css where
     FILENAME to the actual file name of the CSS file you copied in #2.
  4) Clear the cache.


