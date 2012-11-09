<?php

/**
 * @file
 * Module admin page callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// ldapauth settings

/**
 * Implements the settings page.
 *
 * @return
 *   The form structure.
 */
function ldapauth_admin_settings() {
  $options_login_process = array(
    LDAPAUTH_AUTH_MIXED => t('Mixed mode. The LDAP authentication is performed only if Drupal authentication fails'),
    LDAPAUTH_AUTH_EXCLUSIVED => t('LDAP directory only')
  );
  $options_login_conflict = array(
    LDAPAUTH_CONFLICT_LOG => t('Disallow login and log the conflict'),
    LDAPAUTH_CONFLICT_RESOLVE => t('Associate local account with the LDAP entry')
  );
  $options_username_field = array(
    LDAPAUTH_USERNAME_FIELD_NO => t('Do nothing'),
    LDAPAUTH_USERNAME_FIELD_REMOVE => t('Remove username field from form'),
    LDAPAUTH_USERNAME_FIELD_DISABLE => t('Disable username field on form'),
  );

  $form['system-options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Authentication mode'),
    '#description' => t('<strong>NOTE:</strong> These settings have no effect on Drupal user with uid 1. The admin account never uses LDAP.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['system-options']['ldapauth_login_process'] = array(
    '#type' => 'radios',
    '#title' => t('Choose authentication mode'),
    '#description' => t('Pick the mode based on the types of user accounts and other configuration decisions. If <i>LDAP directory only</i> option is activated some UI modifications will be applied.'),
    '#default_value' => LDAPAUTH_LOGIN_PROCESS,
    '#options' => $options_login_process,
    '#required' => TRUE,
  );
  $form['system-options']['ldapauth_login_conflict'] = array(
    '#type' => 'radios',
    '#title' => t('Choose user conflict resolve procedure'),
    '#description' => t('Pick what should be done if the local Drupal account already exists with the same login name.'),
    '#default_value' => LDAPAUTH_LOGIN_CONFLICT,
    '#options' => $options_login_conflict,
    '#required' => TRUE,
  );

  $form['security-options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Security Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['security-options']['ldapauth_forget_passwords'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not store users\' passwords during sessions'),
    '#default_value' => LDAPAUTH_FORGET_PASSWORDS,
    '#description' => t('<p>If you use the <strong>ldapdata</strong> module and want to allow users to modify their LDAP attributes, you have two options:</p><ul><li>Setup a special ldap manager DN that has (limited) permissions to edit the requisite LDAP records - using this method means Drupal\'s built in password reset will work;</li> <li>or allow this module to store the user\'s LDAP password, in clear text, during the session;</li></ul><p>Physically, these passwords are stored in the Drupal\'s session table in clear text. This is not ideal and is not the recomended configuration.</p><p>Unless you need to use the latter configuration, leave this checked.</p>'),
  );
  $form['security-options']['ldapauth_sync_passwords'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sync LDAP password with the Drupal password'),
    '#default_value' => LDAPAUTH_SYNC_PASSWORDS,
    '#description' => t('If checked, then LDAP and Drupal passwords will be syncronized. This might be useful if some other modules need to authenticate against the user password hash stored in Drupal and works only in Mixed mode. It might introduce security issues in the Mixed mode since after the deletion of the LDAP account, the Drupal user will still exist and may be able to login to Drupal with his password if ldapauth is disabled. If unsure, leave this unchecked.'),
  );
  $form['security-options']['ldapauth_create_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create new Drupal user if not present'),
    '#default_value' => variable_get('ldapauth_create_users', TRUE),
    '#description' => t('If checked, then LDAP will create a new Drupal user against the user information supplied by the user authenticated by LDAP. If not checked only the already available users will be authenticated.'),
  );

  $form['ldap-ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('LDAP UI Options'),
    '#description' => t('<p>Alters LDAP users\' interface only, though admin accounts can still access email and password fields of LDAP users regardless of selections. Does not effect non-LDAP authenticated accounts. </p>'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['ldap-ui']['ldapauth_alter_username_field'] = array(
    '#type' => 'radios',
    '#title' => t('Alter username field on user edit form'),
    '#description' => t('Remove or disable username field from user edit form for LDAP authenticated users, even admin users.'),
    '#default_value' => LDAPAUTH_ALTER_USERNAME_FIELD,
    '#options' => $options_username_field,
    '#required' => TRUE,
  );
  $form['ldap-ui']['ldapauth_disable_pass_change'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove password change fields from user edit form'),
    '#default_value' => LDAPAUTH_DISABLE_PASS_CHANGE,
    '#description' => t('If left unchecked, ldap users will receive warning that they may not request new password here.  <strong>NOTE:</strong> Request new password feature will be disabled for all users even for the user with uid 1.'),
  );
  $options_email_field = array(
    LDAPAUTH_EMAIL_FIELD_NO => t('Do nothing'),
    LDAPAUTH_EMAIL_FIELD_REMOVE => t('Remove email field from form'),
    LDAPAUTH_EMAIL_FIELD_DISABLE => t('Disable email field on form'),
  );
  $form['ldap-ui']['ldapauth_alter_email_field'] = array(
    '#type' => 'radios',
    '#title' => t('Alter email field on user edit form'),
    '#description' => t('Remove or disable email field from user edit form for LDAP authenticated users.'),
    '#default_value' => LDAPAUTH_ALTER_EMAIL_FIELD,
    '#options' => $options_email_field,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['reset'] = array(
    '#type'  => 'submit',
    '#value' => t('Reset to defaults'),
  );
  return $form;
}

/**
 * Submit hook for the settings form.
 */
function ldapauth_admin_settings_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  $values = $form_state['values'];
  switch ($op) {
    case t('Save configuration'):
      variable_set('ldapauth_login_process', $values['ldapauth_login_process']);
      variable_set('ldapauth_login_conflict', $values['ldapauth_login_conflict']);
      variable_set('ldapauth_forget_passwords', $values['ldapauth_forget_passwords']);
      variable_set('ldapauth_sync_passwords', $values['ldapauth_sync_passwords']);
      variable_set('ldapauth_disable_pass_change', $values['ldapauth_disable_pass_change']);
      variable_set('ldapauth_alter_email_field', $values['ldapauth_alter_email_field']);
      variable_set('ldapauth_create_users', $values['ldapauth_create_users']);
      variable_set('ldapauth_alter_username_field', $values['ldapauth_alter_username_field']);

      drupal_set_message(t('The configuration options have been saved.'));
      break;
    case t('Reset to defaults'):
      variable_del('ldapauth_login_process');
      variable_del('ldapauth_login_conflict');
      variable_del('ldapauth_forget_passwords');
      variable_del('ldapauth_sync_passwords');
      variable_del('ldapauth_disable_pass_change');
      variable_del('ldapauth_alter_email_field');
      variable_del('ldapauth_create_users');
      variable_del('ldapauth_alter_username_field');
      drupal_set_message(t('The configuration options have been reset to their default values.'));
      break;
  }

  // Rebuild the menu router.
  menu_rebuild();
}

/**
 * Implements the LDAP servers list.
 *
 * @return
 *   The HTML table with the servers list.
 */
function ldapauth_admin_list() {
  $form['list'] = array();
  $result = db_query("SELECT sid, name, status, weight FROM {ldapauth} ORDER BY weight");
  while ($row = db_fetch_object($result)) {
    $form['list'][$row->sid] = array(
      'name' => array('#value' => $row->name),
      'status' => array('#value' => $row->status),
      'weight' => array(
        '#type' => 'weight',
        '#name' => 'sid_'. $row->sid .'_weight',
        '#delta' => 10,
        '#default_value' => $row->weight,
      ),
    );
  }

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit hook for the servers list form.
 */
function ldapauth_admin_list_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  switch ($op) {
    case t('Save'):
      foreach ($form_state['clicked_button']['#post'] as $name => $val) {
        if (preg_match('/^sid_.*_weight/', $name)) {
          $sid = preg_replace(array('/^sid_/', '/_weight$/'), array('', ''), $name);
          db_query("UPDATE {ldapauth} SET weight = %d WHERE sid = %d", $val, $sid);
        }
      }
      break;
  }
}

/**
 * Implements the LDAP server edit page.
 *
 * @param $form_state
 *   A form state array.
 * @param $op
 *   An operatin - add or edit.
 * @param $sid
 *   A LDAP server ID.
 *
 * @return
 *   The form structure.
 */
function ldapauth_admin_form(&$form_state, $op = NULL, $sid = NULL) {
  drupal_add_js(drupal_get_path('module', 'ldapauth') .'/ldapauth.admin.js');

  if ($op == "edit" && $sid) {
    $edit = (array) ldapauth_server_load( $sid );
    $form['sid'] = array(
      '#type' => 'hidden',
      '#value' => $sid,
    );
    $form['original_server'] = array(
      '#type' => 'value',
      '#value' => ldapauth_server_load( $sid ),
    );
    $name_classes = "ldapauth-name-update";
  }
  else {
    $edit = array(
      'name' => '',
      'machine_name' => '',
      'server' => '',
      'port' => '389',
      'tls' => 0,
      'enc_type' => 0,
      'basedn' => '',
      'user_attr' => LDAPAUTH_DEFAULT_USER_ATTR,
      'mail_attr' => LDAPAUTH_DEFAULT_MAIL_ATTR,
      'puid_attr' => '',
      'binary_puid' => 0,
      'binddn' => '',
      'bindpw' => FALSE,
      'login_php' => '',
      'filter_php' => '',
    );
    $name_classes = "ldapauth-name";
  }

  $form['server-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Server settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['server-settings']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $edit['name'],
    '#description' => t('Choose a <em><strong>unique</strong></em> name for this server configuration.'),
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#attributes' => array('class' => $name_classes),
  );
  $form['server-settings']['machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine-readable name'),
    '#description' => t('Example: primary_domain_server') . '<br/>' . t('May only contain lowercase letters, numbers and underscores. <strong>Try to avoid conflicts with the names of existing Drupal projects.</strong>'),
    '#required' => TRUE,
    '#default_value' => $edit['machine_name'],
    '#attributes' => array('class' => 'ldapauth-machine-name'),
    '#element_validate' => array('ldapauth_admin_form_validate_field'),
  );

  $form['server-settings']['server'] = array(
    '#type' => 'textfield',
    '#title' => t('LDAP server'),
    '#default_value' => $edit['server'],
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('The domain name or IP address of your LDAP Server. Prefix the hostname or IP address with ldaps:// if the LDAP server connection uses SSL.'),
    '#required' => TRUE,
  );
  $form['server-settings']['port'] = array(
    '#type' => 'textfield',
    '#title' => t('LDAP port'),
    '#default_value' => $edit['port'],
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The TCP/IP port on the above server which accepts LDAP connections. Must be an integer. Standard ports are 389 and 636(SSL).'),
  );
  $form['server-settings']['tls'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Start-TLS'),
    '#default_value' => $edit['tls'],
    '#description' => t('Secure the connection between the Drupal and the LDAP servers using TLS.<br /><em>Note: To use START-TLS, you must set the LDAP Port to 389.</em>'),
  );
  $form['server-settings']['enc_type'] = array(
    '#type' => 'select',
    '#options' => valid_enc_types(),
    '#title' => t('LDAP password encryption type'),
    '#default_value' => $edit['enc_type'],
    '#description' => t('This lists which type of Standard LDAP encryption should be used. Use with care as some LDAP directories may do this automatically, what would cause login issues. If unsure, use cleartext.'),
  );

  $form['login-procedure'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login procedure'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['login-procedure']['basedn'] = array(
    '#type' => 'textarea',
    '#title' => t('Base DNs'),
    '#default_value' => $edit['basedn'],
    '#cols' => 50,
    '#rows' => 6,
    '#description' => t('Base DNs for users. Enter one per line in case you need several of them.'),
  );
  $form['login-procedure']['user_attr'] = array(
    '#type' => 'textfield',
    '#title' => t('UserName attribute'),
    '#default_value' => $edit['user_attr'],
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t('The attribute that holds the users\' login name. (eg. <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">cn</em> for eDir or <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">sAMAccountName</em> for Active Directory).'),
  );
  $form['login-procedure']['mail_attr'] = array(
    '#type' => 'textfield',
    '#title' => t('Email attribute'),
    '#default_value' => $edit['mail_attr'],
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t('The attribute that holds the users\' email address. (eg. <em style="font-style: normal; padding: 1px 3px; border: 1px solid #8888CC; background-color: #DDDDFF">mail</em>).'),
  );
  $form['login-procedure']['puid_attr'] = array(
    '#type' => 'textfield',
    '#title' => t('Persistent and Unique User Id attribute'),
    '#default_value' => $edit['puid_attr'],
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t("In some LDAPs, a user's DN, CN, or mail may change when a user's name changes or for other reasons. In order to avoid creation of multiple accounts and definitively map ldap entries to Drupal users, you can enter an attribute that will be persistent and unique across LDAP changes, e.g. employeeNumber, entryUUID, objectGUID, and the like. If no such attribute exists, just leave blank."),
  );
  $form['login-procedure']['binary_puid'] = array(
    '#type' => 'checkbox',
    '#title' => t('PUID is binary'),
    '#default_value' => $edit['binary_puid'],
    '#description' => t("Some attributes that can be used for PUIDs are binary and require special handing, e.g. objectGUID.  Check this if the puid attribute is binary."),
  );
  $form['login-procedure']['login_php'] = array(
    '#type' => 'textarea',
    '#title' => t('PHP to transform login name'),
    '#default_value' => $edit['login_php'],
    '#cols' => 25,
    '#rows' => 5,
    '#description' => check_plain(t('Enter PHP to transform login name before it is sent to LDAP for authentication. Careful, bad PHP code here will break your site. If left empty, no name transformation will be done. Change following example code to enable transformation:<br /><code>return $name;</code>')),
  );
  $form['login-procedure']['filter_php'] = array(
    '#type' => 'textarea',
    '#title' => t('PHP to filter users based on their LDAP data'),
    '#default_value' => $edit['filter_php'],
    '#cols' => 25,
    '#rows' => 5,
    '#description' => check_plain(t('Enter PHP to filter users which are allowed to login based on their LDAP data. Careful, bad PHP code here will break your site. If left empty, no filtering will be done. The code should return TRUE to allow authentication. Following example shows how to disallow users without their homeDirectory set:<br /><code>return isset($ldap[\'homeDirectory\']) && isset($ldap[\'homedirectory\'][0]);</code>')),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced configuration'),
    '#description' => t('<p>The process of authentication starts by establishing an anonymous connection to the LDAP directory and looking up for the user on it. Once this user is found, LDAP authentication is performed on them.</p><p>However, some LDAP configurations (specially common in <strong>Active Directory</strong> setups) restrict anonymous searches.</p><p>If your LDAP setup does not allow anonymous searches, or these are restricted in such a way that login names for users cannot be retrieved as a result of them, then you have to specify here a DN//password pair that will be used for these searches.</p><p>For security reasons, this pair should belong to an LDAP account with stripped down permissions.</p>'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  if (!$edit['bindpw']) {
    $form['advanced']['binddn'] =  array(
      '#type' => 'textfield',
      '#title' => t('DN for non-anonymous search'),
      '#default_value' => $edit['binddn'],
      '#size' => 50,
      '#maxlength' => 255,
    );
    $form['advanced']['bindpw'] = array(
      '#type' => 'password',
      '#title' => t('Password for non-anonymous search'),
      '#size' => 12,
      '#maxlength' => 255,
    );
  }
  else {
    $form['advanced']['binddn'] =  array(
      '#type' => 'item',
      '#title' => t('DN for non-anonymous search'),
      '#value' => $edit['binddn'],
    );
    // Give an option to clear the password.
    $form['advanced']['bindpw_clear'] = array(
      '#type' => 'checkbox',
      '#title' => t('Clear current password and change DN'),
      '#default_value' => FALSE,
    );
  }
  $form['advanced']['test'] = array(
    '#type'  => 'submit',
    '#value' => t('Test'),
    '#suffix' => '<div id="test-spinner" style="display: none;">'. theme_image(drupal_get_path('module', 'ldapauth') .'/images/spinner.gif') .'</div><div id="test-message" class="messages" style="display: none;"></div>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validate hook for the LDAP server form.
 */
function ldapauth_admin_form_validate($form, &$form_state) {
  $values = $form_state['values'];

  if (!isset($values['sid'])) {
    if (db_fetch_object(db_query("SELECT name FROM {ldapauth} WHERE name = '%s'", $values['name']))) {
      form_set_error('name', t('An LDAP config with the  name %name already exists.', array('%name' => $values['name'])));
    }
    if (db_fetch_object(db_query("SELECT machine_name FROM {ldapauth} WHERE machine_name = '%s'", $values['machine_name']))) {
      form_set_error('name', t('An LDAP config with the machine name %name already exists.', array('%name' => $values['machine_name'])));
    }
  }
  if (!is_numeric($values['port'])) {
    form_set_error('port', t('The TCP/IP port must be an integer.'));
  }
}

/**
 * Submit hook for the LDAP server form.
 */
function ldapauth_admin_form_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  $values = $form_state['values'];
  switch ($op) {
    case t('Save configuration'):
      $server = array(
        'name' => $values['name'],
        'machine_name' => $values['machine_name'],
        'status' => 1,
        'server' => $values['server'],
        'port' => $values['port'],
        'tls' => $values['tls'],
        'enc_type' => $values['enc_type'],
        'basedn' => $values['basedn'],
        'user_attr' => trim($values['user_attr']),
        'mail_attr' => trim($values['mail_attr']),
        'puid_attr' => trim($values['puid_attr']),
        'binary_puid' => trim($values['binary_puid']),
        'binddn' => $values['binddn'],
        'bindpw' => $values['bindpw'],
        'login_php' => trim($values['login_php']),
        'filter_php' => trim($values['filter_php']),
      );
      if ( isset($values['sid'])) {
        $old_server = $values['original_server'];
        $server['sid'] = $values['sid'];

        // If machine name has changed, update ldapauth_users values.
        if ( $old_server->machine_name != $server['machine_name'] ) {
          db_query("UPDATE {ldapauth_users SET machine_name='%s' WHERE sid = %d", $server['machine_name'], $server['sid']);
        }

        // If puid attr has changed, clear out old values.
        if ( $old_server->puid_attr != $server['puid_attr'] ) {
          ldapauth_userinfo_delete_by_sid($server['sid']);
          drupal_set_message(t("NOTICE: The PUID info for current users were cleared because PUID Attribute changed.  You can either let this information be rebuild as users log in or use ldapsync to rebuild."), 'warning');
        }
      }
      if ( ! empty($values['bindpw_clear'])) {
        $server['bindpw'] = '';
      }
      ldapauth_server_save($server, FALSE, TRUE);

      $form_state['redirect'] = 'admin/settings/ldap/ldapauth/list';
      break;
    case t('Test'):
      global $_ldapauth_ldap;
      if (isset($values['sid']) && _ldapauth_init($values['sid'])) {
        // Try to authenticate.
        $dn = $_ldapauth_ldap->getOption('binddn');
        $pass = $_ldapauth_ldap->getOption('bindpw');
        if (!$_ldapauth_ldap->connect($dn, $pass)) {
          drupal_set_message(t('Authentication with the LDAP server for the dn %dn and saved password failed.', array('%dn' => $dn)), 'error');
        }
        else {
          drupal_set_message(t('Authentication with the LDAP server for the dn %dn and saved password succeeded.', array('%dn' => $dn)));
        }
      }
      else {
        drupal_set_message(t('Cannot load server settings. Please save configuration first.'), 'error');
      }
      break;
  }
}

/**
 * De-activates the LDAP server.
 *
 * @param $form_State
 *   A form_state array.
 * @param $sid
 *   A LDAP server ID.
 *
 * @return
 *  Form array.
 */
function ldapauth_admin_deactivate(&$form_state, $sid) {
  if (is_numeric($sid) && ($name = db_result(db_query("SELECT name from {ldapauth} WHERE sid = %d", $sid)))) {
    $form['sid'] = array('#type' => 'hidden', '#value' => $sid);

    return confirm_form($form, t('Are you sure you want to de-activate the server %name?', array('%name' => $name)), 'admin/settings/ldap/ldapauth/list', '', t('De-activate'), t('Cancel'));
  }
  else {
    drupal_not_found();
    exit;
  }
}

/**
 * De-activates the LDAP server.
 *
 * @return
 */
function ldapauth_admin_deactivate_submit($form, &$form_state) {
  $sid = $form_state['values']['sid'];
  $result = db_query("SELECT name from {ldapauth} WHERE sid = %d", $sid);
  if ($row = db_fetch_object($result)) {
    db_query("UPDATE {ldapauth} SET status = '0' WHERE sid = %d", $sid);
    drupal_set_message(t('LDAP Configuration %name has been de-activated.', array('%name' => $row->name)));
    watchdog('ldapauth', 'LDAP server %name was de-activated.', array('%name' => $row->name));
  }
  drupal_goto('admin/settings/ldap/ldapauth/list');
}

/**
 * Activates the LDAP server.
 *
 * @param $form_State
 *   A form_state array.
 * @param $sid
 *   A LDAP server ID.
 *
 * @return
 *  Form array.
 */
function ldapauth_admin_activate(&$form_state, $sid) {
  if (is_numeric($sid) && ($name = db_result(db_query("SELECT name from {ldapauth} WHERE sid = %d", $sid)))) {
    $form['sid'] = array('#type' => 'hidden', '#value' => $sid);

    return confirm_form($form, t('Are you sure you want to activate the server %name?', array('%name' => $name)), 'admin/settings/ldap/ldapauth/list', '', t('Activate'), t('Cancel'));
  }
  else {
    drupal_not_found();
    exit;
  }
}

/**
 * Activates the LDAP server.
 *
 * @return
 */
function ldapauth_admin_activate_submit($form, &$form_state) {
  $sid = $form_state['values']['sid'];
  $result = db_query("SELECT name from {ldapauth} WHERE sid = %d", $sid);
  if ($row = db_fetch_object($result)) {
    db_query("UPDATE {ldapauth} SET status = '1' WHERE sid = %d", $sid);
    drupal_set_message(t('LDAP Configuration %name has been activated.', array('%name' => $row->name)));
    watchdog('ldapauth', 'LDAP server %name was activated.', array('%name' => $row->name));
  }
  drupal_goto('admin/settings/ldap/ldapauth/list');
}

/**
 * Implements the LDAP server delete page.
 *
 * @param $form_state
 *   A form state array.
 * @param $sid
 *   A LDAP server ID.
 *
 * @return
 *   The form structure.
 */
function ldapauth_admin_delete(&$form_state, $sid) {
  if (is_numeric($sid) && ($name = db_result(db_query("SELECT name from {ldapauth} WHERE sid = %d", $sid)))) {
    $form = array(
      'sid' => array('#type' => 'hidden', '#value' => $sid),
      'name' => array('#type' => 'hidden', '#value' => $name),
    );

    return confirm_form($form, t('Are you sure you want to delete the LDAP server named %name?', array('%name' => $name)), 'admin/settings/ldap/ldapauth/list', NULL, t('Delete'), t('Cancel'));
  }
  else {
    drupal_not_found();
    exit;
  }
}

/**
 * Submit hook for the LDAP server delete page.
 */
function ldapauth_admin_delete_submit($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['confirm'] && $values['sid']) {
    ldapauth_server_delete($values['sid']);
  }
  drupal_goto('admin/settings/ldap/ldapauth/list');
}

/**
 * Implements the LDAP admin  page.
 *
 * @return
 *   The themed HTML page.
 */
function ldapauth_admin_menu_block_page() {
  return theme('admin_block_content', system_admin_menu_block(menu_get_item()));
}

/**
 * Returns an array of valid encryption types.
 *
 *  *Most of the code here is from phpLDAPadmin.
 */
function valid_enc_types() {

  // Clear Text
  $valid_types[0] = t('Clear');

  // Crypt + Salted Crypt
  $valid_types[2] = t('Crypt');
  $valid_types[3] = t('Salted Crypt');

  // Extended DES
  if ( defined( 'CRYPT_EXT_DES' ) || CRYPT_EXT_DES == 1 )
    $valid_types[4] = t('Extended DES');

  // MD5Crypt
  if ( defined( 'CRYPT_MD5' ) || CRYPT_MD5 == 1 )
    $valid_types[5] = t('MD5Crypt');

  // Blowfish
  if ( defined( 'CRYPT_BLOWFISH' ) || CRYPT_BLOWFISH == 1 )
    $valid_types[6] = t('Blowfish');

  // MD5
  $valid_types[1] = t('MD5');

  // SMD5 + SHA +  SSHA
  if (function_exists( 'mhash' ) && function_exists( 'mhash_keygen_s2k' ) ) {
    $valid_types[7] = t('Salted MD5');
    $valid_types[8] = t('SHA');
    $valid_types[9] = t('Salted SHA');
  }

  return $valid_types;
}


/**
 * Implements the AJAX server test.
 *
 * @param $sid
 *   LDAP server ID.
 *
 * @return
 *   The JSON data.
 */
function _ldapauth_ajax_test($sid) {
  global $_ldapauth_ldap;

  if (!is_numeric($sid)) {
    return;
  }

  _ldapauth_init($sid);

  if ($_POST['bindpw_clear'] == 'undefined') {
    $binddn = $_POST['binddn'];
    $bindpw = $_POST['bindpw'];
  }
  else {
    $binddn = $_ldapauth_ldap->getOption('binddn');
    $bindpw = $_ldapauth_ldap->getOption('bindpw');
  }

  drupal_json($_ldapauth_ldap->connect($binddn, $bindpw) ? array('status' => 1, 'message' => t('Authentication with the LDAP server succeeded.')) : array('status' => 0, 'message' => t('Authentication with the LDAP server failed.')));
  exit;
}
/**
 * Export server settings form.
 *
 * @param $sid
 *   The server id.
 */
function ldapauth_admin_export_form($form_state, $sid) {
  drupal_set_title(t('Export setting for server %description',
    array('%description' => $sid->name)));

  // Get export code with Ctools.
  ctools_include('export');

  $export = ctools_export_object('ldapauth', $sid);
  //              $ldapserver->sid   =    ' 1  '    ;
//  preg_replace('/\$ldapserver->sid\s*=\s*\'\d+\'\s*\;\s*\n/', '', $export);
  $export = "<?php\n{$export}return serialize(\$ldapserver);\n?>";
  $lines = substr_count($export, "\n");;

  // Create the export code textarea.
  $form = array(
    'info' => array(
      '#type' => 'markup',
      '#value' => t('Copy the export text below and paste it into another ' .
        'ldapauth site using the import server tab.'),
    ),
    'export' => array(
      '#type' => 'textarea',
      '#title' => t('Server settings'),
      '#rows' => $lines,
      '#default_value' => $export,
    ),
  );
  return $form;
}
/**
 * Import server settings form .
 */
function ldapauth_admin_import_form($form_state) {
  $form = array(
    'info' => array(
      '#type' => 'markup',
      '#value' => '<p>' .
        t('Paste the text from the export a server option here ' .
          'to create a <b>new</b> server with the same options. ') .
        '</p><p>' .
        t('Notes:') .
        '<ul><li>' .
        t('The imported server name can not duplicate any existing server name') .
        '</li><li>' .
        t('If the ldapdata or ldapgroups modules were enabled on ' .
          'the source server, they will need to be enabled on this server.') .
        '</li><li>' .
        t('If this server config is replacing an existing server config, ' .
          'there may be user data issues. Users may be marked with the old ' .
          'database sid value rather than the imported value.') .
        '</li></ul></p>'
    ),
    'import' => array(
      '#type' => 'textarea',
      '#rows' => 20,
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Import')
    ),
  );
  return $form;
}
/**
 * Validate a server settings import.
 */
function ldapauth_admin_import_form_validate($form, &$form_state) {
  // Run the import code, which should return a serialized $preset object.
  $ldapserver =  unserialize(drupal_eval($form_state['values']['import']));
  if (empty($ldapserver) || !is_object($ldapserver) || empty($ldapserver->name)) {
    form_set_error('import', t('The submitted preset code could not be interperated.'));
  }
  elseif ( isset($ldapserver->sid) ) {
    form_set_error('import', t('Imported server can not have an sid field value,'));
  }
  elseif (ldapauth_server_load_by_name($ldapserver->name)) {
    form_set_error('import', t('A server with the name, @server already exists.',
      array('@server' => $ldapserver->name)));
  }
  elseif (ldapauth_server_load($ldapserver->machine_name)) {
    form_set_error('import', t('A server with the machine name, @server already exists.',
      array('@server' => $ldapserver->machine_name)));
  }
  else {
    // Pass the parsed object on to the submit handler.
    $form_state['values']['import_parsed'] = $ldapserver;
  }
}
/**
 * Submit handler to import server settings.
 */
function ldapauth_admin_import_form_submit($form, &$form_state) {
  $server = (array) $form_state['values']['import_parsed'];
  ldapauth_server_save($server);
  $form_state['redirect'] = 'admin/settings/ldap/ldapauth';
}
/**
 * Validation for machine name field.
 */
function ldapauth_admin_form_validate_field($element, &$form_state) {
  switch ($element['#name']) {
    case 'machine_name':
      if (!preg_match('!^[a-z0-9_]+$!', $element['#value'])) {
        form_error($element, t('The machine-readable name must contain only lowercase letters, numbers, and underscores.'));
      }
      // If user is filling out the feature name for the first time and uses
      // the name of an existing module throw an error.
      elseif (empty($element['#default_value']) && ldapauth_server_load($element['#value'])) {
        form_error($element, t('A server with the machine_name, @name, already exists on your site. Please choose a different name.', array('@name' => $element['#value'])));
      }
      break;
  }
}
/**
 * Page callback function to convert a user from an LDAP authenticated user to
 * a normal drupal user.
 *
 * @param unknown_type $account
 */
function ldapauth_user_to_local_user( $account ) {
  if ( $account->ldap_authentified ) {
    $data = array(
      'ldap_dn' => NULL,
      'ldap_config' => NULL,
      'ldap_name' => NULL,
      'ldap_authentified' => NULL,
    );
    $userinfo = ldapauth_userinfo_load_by_uid($account->uid);
    ldapauth_userinfo_delete($userinfo);
    db_query("DELETE FROM {authmap} WHERE uid = %d AND module = 'ldapauth'", $account->uid);
    user_save($account, $data);
    drupal_set_message(t('User, @name, converted from an LDAP authenticated user to a local Drupal user.', array('@name' => $account->name)));
    }
  drupal_goto( 'user/' . $account->uid );
}
