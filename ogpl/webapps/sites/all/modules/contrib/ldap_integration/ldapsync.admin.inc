<?php

/**
 * @file
 * Module admin page callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// ldapsync settings

/**
 * Implements the settings page.
 *
 * @return
 *   The form structure.
 */
function ldapsync_admin_settings() {

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('LDAPsync settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $options_time_interval = array(
    0 => t('As often as possible'),
    1*3600 => t('1 hour'),
    6*3600 => t('6 hours'),
    12*3600 => t('12 hours'),
    24*3600 => t('24 hours'),
    24*7*3600 => t('1 week'),
    -1 => t('never (only sync manually)')
  );
  $form['options']['ldapsync_time_interval'] = array(
    '#type' => 'select',
    '#title' => t('Sync time interval'),
    '#description' => t('The number of hours between each sync. A larger setting reduces server load for large LDAP directories.<br />You must have enabled cron, and ldapsync will not run more often than cron.'),
    '#default_value' => variable_get('ldapsync_time_interval', -1),
    '#options' => $options_time_interval,
  );
  $form['options']['ldapsync_existing_only'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sync existing users only.'),
    '#default_value' => variable_get('ldapsync_existing_only', 0),
    '#description' => t("If checked, only existing users will be synced with LDAP, no new users will be created.  Note, the ldapauth 'Create new Drupal user' option will also prevent new user create."),
  );
  $options_login_conflict = array(
    LDAPSYNC_CONFLICT_FOLLOW_LDAPAUTH => t('Follow LDAP Authentication setting'),
    LDAPAUTH_CONFLICT_LOG => t('Disallow login and log the conflict'),
    LDAPAUTH_CONFLICT_RESOLVE => t('Associate local account with the LDAP entry'),
  );

  $form['options']['ldapsync_login_conflict'] = array(
    '#type' => 'select',
    '#title' => t('Choose user conflict resolve procedure'),
    '#description' => t('Pick what should be done if the local Drupal account already exists with the same login name.'),
    '#default_value' => variable_get('ldapsync_login_conflict', LDAPSYNC_CONFLICT_FOLLOW_LDAPAUTH),
    '#options' => $options_login_conflict,
    '#required' => TRUE,
  );

  $form['options']['ldapsync_missing_users_action'] = array(
    '#type' => 'select',
    '#title' => t('Missing users action'),
    '#description' => t("What to do when LDAP-authentified Drupal users don't exist or are disabled in LDAP. Choose block to disable the user accounts in Drupal. Choose warn to only log a warning to the Drupal log."),
    '#default_value' => variable_get('ldapsync_missing_users_action', 'warn'),
    '#options' => array('warn' => t('warn'), 'block' => t('block')),
  );
  $form['options']['ldapsync_load_user_by'] = array(
    '#type' => 'select',
    '#title' => t('What to use for testing for existing users.'),
    '#description' => t("If you want to check for users by email, change this."),
    '#default_value' => variable_get('ldapsync_load_user_by', 'name'),
    '#options' => array('name' => t('User name'), 'email ' => t('E-mail')),
  );
  $form['options']['ldapsync_filter'] = array(
    '#type' => 'textarea',
    '#title' => t('Optional Search filters'),
    '#default_value' => variable_get('ldapsync_filter', ''),
    '#cols' => 50,
    '#rows' => 6,
    '#description' => t('The default filter looks for all entries that contain the user name attribute, e.g. (uid=*). This can return either unwanted or too many results. For instance, AD limits searchs to 1000 results. LDAP filters (Google "ldap search filter tutorial") can be entered on separate lines to refine/limit the users found.  Each server/basedn area will be searched for users using the filters defined below.<br/ >For example: (&(objectClass=person)(|(uid=*)(sAMAccountName=*)))'),
    '#required' => FALSE,
  );
  $form['options']['ldapsync_filter_append_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append default filter'),
    '#default_value' => variable_get('ldapsync_filter_append_default', 0),
    '#description' => t("If checked, the default filter will be 'and-ed' with the optional search filters above.  E.g. (&([optional filter]<u>(uid=*)</u>"),
  );

  $form['manual'] = array(
    '#type' => 'fieldset',
    '#title' => t('Manually sync users now'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['manual']['syncnow'] = array(
    '#type'  => 'submit',
    '#value' => t('Sync now'),
    '#submit' => array('ldapsync_admin_settings_sync_now'),
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Validate hook for the settings form.
 */
function ldapsync_admin_settings_validate($form, &$form_state) {
}

/**
 * Submit hook for the settings form.
 */
function ldapsync_admin_settings_submit($form, &$form_state) {
  $values = $form_state['values'];
  variable_set('ldapsync_time_interval', $values['ldapsync_time_interval']);
  variable_set('ldapsync_filter', trim($values['ldapsync_filter']));
  variable_set('ldapsync_missing_users_action', $values['ldapsync_missing_users_action']);
  variable_set('ldapsync_load_user_by', $values['ldapsync_load_user_by']);
  variable_set('ldapsync_filter_append_default', $values['ldapsync_filter_append_default']);
  variable_set('ldapsync_existing_only', $values['ldapsync_existing_only']);
  variable_set('ldapsync_login_conflict', $values['ldapsync_login_conflict']);

  drupal_set_message(t('Settings saved'));
}

/**
 * Syncs accounts.
 */
function ldapsync_admin_settings_sync_now() {
  $message = _ldapsync_sync();
  drupal_set_message(check_plain($message));
}
