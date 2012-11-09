<?php

/**
 * @file
 * Module admin page callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// ldapgroups settings

 /**
 * Implements the settings page.
 *
 * @return
 *   The form structure.
 */
function ldapgroups_admin_settings() {
  $form['list']['#value'] = ldapgroups_admin_list();

  return $form;
}

/**
 * Implements the LDAP servers list.
 *
 * @return
 *   The HTML table with the servers list.
 */
function ldapgroups_admin_list() {
  $rows = array();
  $result = db_query("SELECT sid, name, status FROM {ldapauth} ORDER BY weight");
  while ($row = db_fetch_object($result)) {
    $rows[] = array(
      'data' => array(
        $row->name,
        l(t('edit'), 'admin/settings/ldap/ldapgroups/edit/'. $row->sid),
        l(t('reset'), 'admin/settings/ldap/ldapgroups/reset/'. $row->sid),
      ),
      'class' => $row->status ? 'menu-enabled' : 'menu-disabled',
    );
  }

  $header = array(
    t('Server'),
    array('data' => t('Operations'), 'colspan' => 2),
  );

  return theme('table', $header, $rows);
}

/**
 * Implements the LDAP server edit page.
 *
 * @param $form_state
 *   A form state array.
 * @param $op
 *   An operatin - edit or reset.
 * @param $sid
 *   A LDAP server ID.
 *
 * @return
 *   The form structure.
 */

function ldapgroups_admin_edit(&$form_state, $op, $sid) {
  if (($op == 'reset') && $sid) {
    $form['sid'] = array(
      '#type' => 'value',
      '#value' => $sid,
      );
    return confirm_form(
      $form,
      t('Are you sure you want to reset the groups mapping to defaults ?'),
      'admin/settings/ldap/ldapgroups',
      t('<em>This action cannot be undone.</p>'),
      t('Reset'),
      t('Cancel')
    );
  }
  elseif ($op == 'edit' && $sid) {
    $edit = db_fetch_array(db_query("SELECT * FROM {ldapauth} WHERE sid = %d", $sid));

    $form['description'] = array(
      '#value' => t('Configure LDAP groups to Drupal roles mapping settings for the %server.', array('%server' => $edit['name'])),
    );

    // How to find groups section
    $form['group-definitions'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group Definitions'),
      '#description' => t('Define how group information is stored in your LDAP database by using one or more of the methods below.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['group-definitions']['group_dn'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group by DN'),
      '#description' => t('Use this method if your users\' DNs look like <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">cn=jdoe,<strong>ou=Group1</strong>,cn=example,cn=com</em> and <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">Group1</em> turns out to be the group you want.</p>'),
      '#collapsible' => TRUE,
      '#collapsed' => !$edit['ldapgroups_in_dn'],
    );
    $form['group-definitions']['group_dn']['ldapgroups_in_dn'] = array(
      '#type' => 'checkbox',
      '#title' => t('Group is specified in user\'s DN'),
      '#default_value' => $edit['ldapgroups_in_dn'],
      '#description' => t('Check to enable this method.'),
    );
    $form['group-definitions']['group_dn']['ldapgroups_dn_attribute'] = array(
      '#type' => 'textfield',
      '#title' => t('Attribute of the DN which contains the group name'),
      '#default_value' => $edit['ldapgroups_dn_attribute'],
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('The name of the attribute which contains the group name. In the example above, it would be <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">ou</em>, as the DN contains the string <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">ou=Group1</em> and <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">Group1</em> happens to be the desired group name. Note:  If the attribute appears more than once in the DN, the user will be listed in multiple groups.'),
    );

    $form['group-definitions']['group_attr'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group by attribute'),
      '#description' => t('Use this method if your user\'s LDAP entries contain attributes that define their group membership, e.g. AD\'s memberof attribute.</p>'),
      '#collapsible' => TRUE,
      '#collapsed' => !$edit['ldapgroups_in_attr'],
    );
    $form['group-definitions']['group_attr']['ldapgroups_in_attr'] = array(
      '#type' => 'checkbox',
      '#title' => t('Groups are specified by LDAP attributes'),
      '#description' => t('Check to enable this method.'),
      '#default_value' => $edit['ldapgroups_in_attr'],
    );
    $form['group-definitions']['group_attr']['ldapgroups_attr'] = array(
      '#type' => 'textarea',
      '#title' => t('Attribute names (one per line)'),
      '#default_value' => implode("\n", ($edit['ldapgroups_attr'] ? unserialize($edit['ldapgroups_attr']) : array())),
      '#cols' => 50,
      '#rows' => 6,
      '#description' => t('If the groups are stored in the user entries, along with the rest of their data, then enter here a list of attributes which may contain them.'),
    );

    $form['group-definitions']['group_entry'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group by entry'),
      '#description' => t('Groups exist as LDAP entries with a multivalued attribute containing either the members\' DNs or username.  E.g. Standard LDAP group objects like groupOfNames that use the \'member\' multivalue attribute or posixGroup with memberUID.'),
      '#collapsible' => TRUE,
      '#collapsed' => !$edit['ldapgroups_as_entries'],
    );
    $form['group-definitions']['group_entry']['ldapgroups_as_entries'] = array(
      '#type' => 'checkbox',
      '#title' => t('Groups exist as LDAP entries with a multivalued membership attribute'),
      '#description' => t('Check to enable this method.'),
      '#default_value' => $edit['ldapgroups_as_entries'],
    );
    $form['group-definitions']['group_entry']['ldapgroups_entries'] = array(
      '#type' => 'textarea',
      '#title' => t('Base LDAP DNs containing groups (one per line)'),
      '#default_value' => implode("\n", ($edit['ldapgroups_entries'] ? unserialize($edit['ldapgroups_entries']) : array())),
      '#cols' => 50,
      '#rows' => 6,
      '#description' => t('Base DNs to search for group entries. The module will look under each of these for group entries.'),
    );
    $form['group-definitions']['group_entry']['ldapgroups_entries_attribute'] = array(
      '#type' => 'textfield',
      '#title' => t('Attribute holding group members'),
      '#default_value' => $edit['ldapgroups_entries_attribute'],
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('Name of the multivalued attribute which holds either the DNs or LDAP usernames of group members, for example: !attr', array('!attr' => theme('placeholder', LDAPGROUPS_DEFAULT_ENTRIES_ATTRIBUTE))),
    );

    // Access rules section
    $form['groups_limit'] = array(
      '#type' => 'fieldset',
      '#title' => t('LDAP Groups Server Access Rules'),
      '#collapsible' => TRUE,
      '#collapsed' => !$edit['ldapgroups_groups'],
    );
    $form['groups_limit']['info'] = array(
      '#type' => 'fieldset',
      '#title' => t('Server Access Rules Help'),
      '#description' => t('<p>Rules can be define below that will limit who can access this server.  These rules can take two forms.</p>' .
        '<p>First, it can just be a list of groups.  In this case, the user must be a member of at least one of these groups to be allowed access.</p>' .
        '<p>The second form uses rules of the format: &quot;action-type: group-name&quot;. Each rule group-name is compared to the user\'s groups.  If the user is a member of the rule\'s group, the action is applied.  The last matching rule determines the user\'s access rights.  Note that all rule sets start with access denied.</p>' .
        '<p>The action types are:</p>' .
        '<ul><li>ALLOW - Access granted if user is in the group and not denied by rule below it.</li>' .
        '<li>ALLOW-X - If the user is in the group, access is granted and rule processing ends</li>' .
        '<li>DENY - User is denied if they are in the group unless granted by a rule below this one.</li>' .
        '<li>DENY-X - User denied if in group and no further rules are processed.</li></ul>' .
        '<p>In addition, there are two "PSEUDO" groups that can be used in rules:</p>' .
        '<ul><li>ALL - Matches all authenticated LDAP users</li>' .
        '<li>EXISTING - Matches existing users who have been authenticated by LDAP in the past.</li></ul>' .
        '<p>Here\'s an example ruleset to deny all Group1 users but allow existing users and (new) Group2 users to access the server.</p>' .
        '<ul><li>DENY-X: cn=Group1,ou=Groups,dc=myorg</li>' .
        '<li>ALLOW-X: EXISTING</li>' .
        '<li>ALLOW: cn=Group2,ou=Groups,dc=myorg</li></ul>' .
        '<p>Note that rule types and groups are case insensitive.  However, group names must have the same spacing as returned by the server to match.  E.g. if server return cn=X,ou=Groups... then a rule group name, cn=X, ou=Groups... will not match because of the space after the comma.</p>'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['groups_limit']['ldapgroups_groups'] = array(
      '#type' => 'textarea',
      '#title' => t('Group access rules'),
      '#default_value' => implode("\n", ($edit['ldapgroups_groups'] ? unserialize($edit['ldapgroups_groups']) : array())),
      '#cols' => 50,
      '#rows' => 5,
      '#description' => t('Leave blank to allow all LDAP authenticated users access. Otherwise, enter a one per line list of LDAP groups or access rules. If the user is not in any of those groups or the last matching rule denies access, the login will be denied.'),
    );

    // Mappings section
    $form['group_filter'] = array(
      '#type' => 'fieldset',
      '#title' => t('LDAP group to Drupal role filtering'),
      '#description' => t('If there is nothing entered in this section, the module will automatically decide Drupal roles name.  These will be based on the names of the LDAP groups. For example:<ul><li>LDAP group: Admins => Drupal role: Admins</li><li>LDAP group: ou=Underlings,dc=myorg,dc=mytld => Drupal role: Underlings.</li></ul>'),
      '#collapsible' => TRUE,
      '#collapsed' => !($edit['ldapgroups_mappings'] || $edit['ldapgroups_filter_php'] || $edit['ldapgroups_mappings_filter']),
    );
    $options_filter_mode = array(
      LDAPGROUPS_ROLE_MODE_AUTO => t("Use automatic LDAP group name to Drupal role name mapping"),
      LDAPGROUPS_ROLE_MODE_USE_MAP => t("Use LDAP group to Drupal role mapping defined below"),
      LDAPGROUPS_ROLE_MODE_DISABLED => t("Do not user LDAP groups for Drupal roles (i.e. access restrictions only).")
      );

    $form['group_filter']['ldapgroups_mappings_filter'] = array(
      '#type' => 'radios',
      '#title' => t('Select how to map LDAP groups to Drupal roles'),
      '#options' => $options_filter_mode,
      '#default_value' => $edit['ldapgroups_mappings_filter'],
//      '#description' => t('In automatic mode a Drupal role will be created for every group the user is associated with.')
    );
    $mappings = '';
    foreach (($edit['ldapgroups_mappings'] ? unserialize($edit['ldapgroups_mappings']) : array()) as $group => $role)
      $mappings .= $group .'|'. $role ."\n";
    $form['group_filter']['ldapgroups_mappings'] = array(
      '#type' => 'textarea',
      '#title' => t('Mapping of LDAP groups to Drupal roles'),
      '#default_value' => $mappings,
      '#cols' => 50,
      '#rows' => 5,
      '#description' => t('Enter a list of LDAP groups and their Drupal role mappings, one per line with a | delimiter. Should be in the form [ldap group]|[drupal role],[drupal role] such as:<br/>cn=ED IT NAG Staff,DC=ad,DC=uiuc,DC=edu|admin<br/>cn=Ed Webs UIUC Webmasters,DC=ad,DC=uiuc,DC=edu|author, reviewer'),
    );
    $form['group_filter']['ldapgroups_filter_php'] = array(
      '#type' => 'textarea',
      '#title' => t('PHP to filter roles by'),
      '#default_value' => $edit['ldapgroups_filter_php'],
      '#cols' => 25,
      '#rows' => 5,
      '#description' => t('Enter PHP to filter LDAP groups. Careful, bad PHP code here will break your site. If left empty, no filtering will be done. The groups array <code>$groups</code> is available in the code context. It should return a filtered <code>$groups</code> array as in example below. The code is evaluated before the above mapping is applied.<br /><code>$groups = array_filter($groups, create_function(\'$a\', \'return preg_match(\\\'/Staff/\\\', $a);\'));</code><br /><code>return $groups;</code>'),
    );

    $form['sid'] = array(
      '#type' => 'hidden',
      '#value' => $sid,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );

    return $form;
  }
  else {
    drupal_goto('admin/settings/ldap/ldapgroups');
  }
}

/**
 * Validate hook for the settings form.
 */
function ldapgroups_admin_edit_validate($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  $values = $form_state['values'];
  switch ($op) {
    case t('Update'):
      if ($values['ldapgroups_in_dn'] && !trim($values['ldapgroups_dn_attribute']))
        form_set_error('ldapgroups_dn_attribute', t('DN attribute is missing.'));
      if ($values['ldapgroups_in_attr'] && !trim($values['ldapgroups_attr']))
        form_set_error('ldapgroups_attr', t('Attribute names are missing.'));
      if ($values['ldapgroups_as_entries'] && !trim($values['ldapgroups_entries']))
        form_set_error('ldapgroups_entries', t('Nodes are missing.'));
      if ($values['ldapgroups_as_entries'] && !trim($values['ldapgroups_entries_attribute']))
        form_set_error('ldapgroups_entries_attribute', t('Attribute is missing.'));

      $form_state['ldapgroups_attr'] = array();
      foreach ((trim($values['ldapgroups_attr']) ? explode("\n", trim($values['ldapgroups_attr'])) : array()) as $line)
        if (trim($line))
          $form_state['ldapgroups_attr'][] = trim($line);
      $form_state['ldapgroups_attr'] = !empty($form_state['ldapgroups_attr']) ? serialize($form_state['ldapgroups_attr']) : '';

      $form_state['ldapgroups_entries'] = array();
      foreach ((trim($values['ldapgroups_entries']) ? explode("\n", trim($values['ldapgroups_entries'])) : array()) as $line)
        if (trim($line))
          $form_state['ldapgroups_entries'][] = trim($line);
      $form_state['ldapgroups_entries'] = !empty($form_state['ldapgroups_entries']) ? serialize($form_state['ldapgroups_entries']) : '';

      $form_state['ldapgroups_mappings'] = array();
      $ldapgroups_role_mappings = TRUE;
      foreach ((trim($values['ldapgroups_mappings']) ? explode("\n", trim($values['ldapgroups_mappings'])) : array()) as $line) {
        if (count($mapping = explode('|', trim($line))) == 2)
          $form_state['ldapgroups_mappings'] += array(trim($mapping[0]) => trim($mapping[1]));
        else
          $ldapgroups_role_mappings = FALSE;
      }
      $form_state['ldapgroups_mappings'] = !empty($form_state['ldapgroups_mappings']) ? serialize($form_state['ldapgroups_mappings']) : '';
      if (!$ldapgroups_role_mappings)
        form_set_error('ldapgroups_mappings', t('Bad mapping syntax.'));

      if ($values['ldapgroups_mappings_filter'] == LDAPGROUPS_ROLE_MODE_USE_MAP && !trim($values['ldapgroups_mappings']))
        form_set_error('ldapgroups_mappings', t('Mappings are missing.'));

      $form_state['ldapgroups_groups'] = array();
      foreach ((trim($values['ldapgroups_groups']) ? explode("\n", trim($values['ldapgroups_groups'])) : array()) as $line)
        if (trim($line))
          $form_state['ldapgroups_groups'][] = trim($line);
      $form_state['ldapgroups_groups'] = !empty($form_state['ldapgroups_groups']) ? serialize($form_state['ldapgroups_groups']) : '';
      break;
  }
}

/**
 * Submit hook for the settings form.
 */
function ldapgroups_admin_edit_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  $values = $form_state['values'];
  switch ($op) {
    case t('Update'):

      // Update the ldapgroups configuration.
      db_query("UPDATE {ldapauth} SET ldapgroups_in_dn = %d, ldapgroups_dn_attribute = '%s', ldapgroups_in_attr = %d, ldapgroups_attr = '%s', ldapgroups_as_entries = %d, ldapgroups_entries = '%s', ldapgroups_entries_attribute = '%s', ldapgroups_mappings = '%s', ldapgroups_mappings_filter = %d, ldapgroups_filter_php = '%s', ldapgroups_groups = '%s' WHERE sid = %d", $values['ldapgroups_in_dn'], trim($values['ldapgroups_dn_attribute']), $values['ldapgroups_in_attr'], $form_state['ldapgroups_attr'], $values['ldapgroups_as_entries'], $form_state['ldapgroups_entries'], trim($values['ldapgroups_entries_attribute']), $form_state['ldapgroups_mappings'], $values['ldapgroups_mappings_filter'], trim($values['ldapgroups_filter_php']), $form_state['ldapgroups_groups'], $values['sid']);
      drupal_set_message(t('The configuration options have been saved.'));
      $form_state['redirect'] = 'admin/settings/ldap/ldapgroups';
      break;
    case t('Reset'):
      if ($values['confirm'] == 1) {

        // Settings reset.
        db_query("UPDATE {ldapauth} SET ldapgroups_in_dn = 0, ldapgroups_dn_attribute = '', ldapgroups_in_attr = 0, ldapgroups_attr = '', ldapgroups_as_entries = 0, ldapgroups_entries = '', ldapgroups_entries_attribute = '', ldapgroups_mappings = '', ldapgroups_mappings_filter = '0', ldapgroups_filter_php = '', ldapgroups_groups = '' WHERE sid = %d", $values['sid']);
        drupal_set_message(t('The configuration options have been reset to their default values.'));
      }
      $form_state['redirect'] = 'admin/settings/ldap/ldapgroups';
      break;
  }
}
/**
 * Test users against the current ldapgroups settings
 *
 * @param Array $form_state
 */
function ldapgroups_user_test(&$form_state) {

  $servers = ldapauth_server_load_all();
  $options_servers = array();
  foreach ( $servers as $server ) {
    $options_servers[$server->sid] = $server->name;
  }

  $form['user_selection'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Selection'),
    '#description' => t('This page will let you test the ldapgroups settings against different users.  This is useful to make sure they are setup correctly and to help debug settings (e.g. user group name does not match rule name).  Enter either an existing LDAP authenticated Drupal user name or a server / dn combination and press Test to see results'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['user_selection']['test_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal User name to test'),
    '#size' => 50,
    '#maxlength' => 255,
    '#default_value' => $form_state['values']['test_user'],
    '#description' => t('Enter an existing LDAP authenticated Drupal user to test group settings with.'),
  );
  $form['user_selection']['or'] = array(
    '#value' => t('OR'),
  );
  $form['user_selection']['server'] = array(
    '#type' => 'radios',
    '#title' => t('Select a server'),
    '#options' => $options_servers,
    '#default_value' => $form_state['values']['server'],
  );
  $form['user_selection']['dn'] = array(
    '#type' => 'textfield',
    '#title' => t('LDAP DN to test'),
    '#size' => 100,
    '#maxlength' => 255,
    '#description' => t('Enter an LDAP user\'s DN to test group settings with.'),
    '#default_value' => $form_state['values']['dn'],
  );
  $form['user_selection']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Test'),
  );

  if ( isset($form_state['storage']['results'])) {
    $form['results'] = array(
      '#type' => 'fieldset',
      '#title' => t('Test Results'),
      '#description' => t('The following information was found for this user.'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['results']['test_user_results'] = array(
      '#title' => t('Test Results'),
      '#value' => $form_state['storage']['results'],
    );
  }

  return $form;
}
/**
 * Validate the supplied test info.
 *
 * @param Array $form
 * @param Array $form_state
 */
function ldapgroups_user_test_validate($form, &$form_state ) {

  module_load_include('inc', 'ldapgroups', 'ldapgroups');

  $values = $form_state['values'];

  if ( $values['server'] && $values['dn'] && $values['test_user']) {
    form_set_error('', t('Can not have all three fields filled.  Use only a Drupal name or LDAP server/dn pair.'));
    return;
  }

  if ( $values['server'] && $values['dn'] ) {
    if ( ! ldapgroups_is_configured( $values['server']) ) {
      form_set_error('', t('Server, @server, has no LDAP group settings defined yet.', array("@server" => $values['server'])));
    }
    return;
  }

  $account = user_load(array('name' => $values['test_user']));
  if ( ! $account ) {
    form_set_error('test_user', t("Invalid user name") );
    return;
  }
  if (  ! $account->ldap_authentified  || $account->ldap_authentified != 1 ) {
    form_set_error('test_user', t("User was not an LDAP authenticated user."));
    return;
  }
  if ( ! ldapgroups_is_configured( $account->ldap_config) ) {
    form_set_error('', t('Server, @server, has no LDAP group settings defined yet.', array("@server" => $account->ldap_config)));
    return;
  }
  $form_state['values']['account'] = $account;
}
/**
 * Submit handler for testing user against the ldapgroups settings.
 *
 * @param Array $form
 * @param Array $form_state
 */
function ldapgroups_user_test_submit($form, &$form_state ) {

  if ( isset($form_state['values']['account']) ) {
    $account = $form_state['values']['account'];
    $dn = $account->ldap_dn;
    $sid = $account->ldap_config;
  }
  else {
    $account = NULL;
    $dn = $form_state['values']['dn'];
    $sid = $form_state['values']['server'];
  }
  $form_state['storage']['results'] = ldapgroups_user_test_output( $account, $sid, $dn );
}
/**
 * Generate the test results for the user and ldap settings.
 *
 * @param Object $account
 * @param int $sid
 * @param String $dn
 */
function ldapgroups_user_test_output( $account, $sid, $dn ) {
  global $_ldapgroups_ldap;

  module_load_include('inc', 'ldapgroups', 'ldapgroups');

  // Setup the global $_ldapgroups_ldap object.
  if (!_ldapgroups_ldap_init($sid)) {
    drupal_set_message(t('Could not initialize the LDAP connection object!'), 'error');
    return FALSE;
  }


  // Use the lookup dn/password or announymous if not set.
  // Note: This may fail if LDAP security limits access to needed info.
  $bind_dn = $_ldapgroups_ldap->getOption('binddn');
  $pass = $_ldapgroups_ldap->getOption('bindpw');
  if (!$_ldapgroups_ldap->connect($bind_dn, $pass)) {
    $bind_name = empty($bind_dn ) ? t("anonymous") : $bind_dn;
    drupal_set_message(t('Could not bind to the LDAP server as @name!', array('@name' => $bind_name)), 'error');
    return FALSE;
  }

  $ldap_info = ldapauth_user_lookup_by_dn($_ldapgroups_ldap, $dn, LDAPAUTH_SYNC_CONTEXT_AUTHENTICATE_DRUPAL_USER);
  if ( empty($ldap_info) ) {
    drupal_set_message(t("Could not find specified DN"));
    return FALSE;
  }

  $name_attr = $_ldapgroups_ldap->getOption('user_attr');
  $ldap_name = isset($ldap_info[$name_attr][0]) ? $ldap_info[$name_attr][0] : $ldap_info[drupal_strtolower($name_attr)][0];
  if ( ! $account ) {
    $account = ldapauth_drupal_user_lookup($_ldapgroups_ldap, $ldap_name, $dn, $error );
  }

  $output = '<p>';
  $output .= "<b>" . t('Drupal User Info') . "</b><br/>";
  if ( $account ) {
    $output .= t("Drupal user name") . ":  {$account->name}<br/>";
    $output .= t("LDAP Authentified") . ": " . ( $account->ldap_authentified ? "Yes" : "No") . "<br/>";
  }
  else {
    $output .= t("No matching Drupal User found.") . "<br/>";
  }
  $output .= "<br/><b>" . t("LDAP User Info") . "</b><br/>";
  $output .= t("LDAP server") . ": {$_ldapgroups_ldap->getOption('name')}<br/>";
  $output .= t("LDAP user name") . ": {$ldap_name}<br/>";
  $output .= t("LDAP dn") . ": {$dn}<br/>";


  // First, we figure out the appropriate groups.
  $groups = ldapgroups_groups_load($_ldapgroups_ldap, $dn, $ldap_name );
  $output .= "<br/><b>" . t("User's LDAP Groups") . "</b><br/>";

  if ( $groups ) {
    foreach ( $groups as $group ) {
      $output .= "{$group}<br/>";
    }
  }
  else {
    if ( $groups === FALSE ) {
      $output .= t("An error occured getting group information!") . "<br/>";
    }
    else {
      $output .= t("No groups found") . "<br/>";
    }
  }

  $output .= "<br/><b>" . t("Server Access") . "</b><br/>";
  $groups_allowed = _ldapgroups_ldap_info($sid, 'ldapgroups_groups');
  if ( empty($groups_allowed)  ) { // Nothing to do here.
    $output .= t("No access rules defined.") . "<br/>";
  }

  $denied = FALSE;
  ldapgroups_ldap_user_deny_alter( $denied, $_ldapgroups_ldap, $ldap_name, $dn, $account );
  $access = ! $denied ? t("Allowed") : t("Denied");
  $output .= t("Server access") . ": {$access}<br/>";

  $output .= "<br/><b>" . t("User's Drupal Roles") . "</b><br/>";
  $role_mapping = _ldapgroups_ldap_info($sid, 'ldapgroups_mappings_filter');
  switch ( $role_mapping ) {
    case LDAPGROUPS_ROLE_MODE_AUTO:
      $role_mapping_mode = t("Automatic mode");
      break;
    case LDAPGROUPS_ROLE_MODE_USE_MAP:
      $role_mapping_mode = t("Mapping defined in server settings");
      break;
    case LDAPGROUPS_ROLE_MODE_DISABLED:
      $role_mapping_mode =  t("Role mapping disabled");
      break;
  }

  $output .= t("Role Mapping Mode") . ": {$role_mapping_mode}<br/>";

  // Is Role mapping disabled?
  if ( $role_mapping != LDAPGROUPS_ROLE_MODE_DISABLED ) {

    // Apply site-specific rules.
    $filtered_groups = _ldapgroups_filter($sid, $groups);

    // At this point, the roles are in the full DN format or role names.
    $roles = array();
    if (!empty($filtered_groups)) {
      foreach ($filtered_groups as $group) {
        $role = _ldapgroups_mapping($sid, $group);
        $roles[] = $role;
      }
    }
    $roles = array_unique($roles);

    drupal_alter("ldap_user_roles", $roles, $account, $dn, $groups, $filtered_groups );

    if ( ! empty($roles) ) {
      foreach ( $roles as $role ) {
        $output .= "{$role}<br/>";
      }
    }
    else {
      $output .= t("No roles found") . "<br/>";
    }
  }

  $output .= "</p>";
  return $output;
}
