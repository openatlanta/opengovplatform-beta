<?php

/**
 * @file
 * Admin page callback file for the rpx_ui module.
 */

/**
 * Menu callback: Generate a form to configure Engage settings.
 *
 * @ingroup forms
 * @see rpx_admin_settings_validate()
 * @see rpx_admin_settings_submit()
 */
function rpx_admin_settings(&$form_state) {
  $group = 'setup';
  $get_engage = '';
  if (!variable_get('rpx_apikey', FALSE)) {
    $get_engage = t('To create a Janrain Engage account, visit <a href="@get_engage" target="_blank">Get Janrain Engage</a>.  ', array('@get_engage' => 'http://www.janrain.com/products/engage/get-janrain-engage'));
  }
  $form[$group] = array(
    '#type' => 'fieldset',
    '#title' => t('SETUP'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => $get_engage . t('To make changes to your existing Janrain Engage account and integration with this site visit <a href="@account_link" target="_blank">@account_link</a>.',  array('@account_link' => 'https://rpxnow.com/account')),
  );
  $form[$group]['rpx_apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#default_value' => variable_get('rpx_apikey', ''),
    '#description' => t('If you don\'t have a key, please visit <a href="@get_engage" target="_blank">Get Janrain Engage</a> to get one.', array('@get_engage' => 'http://www.janrain.com/products/engage/get-janrain-engage')),
  );
  $form[$group]['rpx_realm'] = array(
    '#type' => 'item',
    '#title' => t('Engage Realm'),
    '#value' => variable_get('rpx_realm', ''),
    '#description' => t('The Engage realm for this site (set automatically based on your API Key).'),
  );
  $form[$group]['rpx_admin_url_hidden'] = array(
    '#type' => 'item',
    '#title' => t('Engage Admin URL'),
    '#value' => t('<a href="@account_stats" target="_blank">@account_stats</a>', array('@account_stats' => variable_get('rpx_admin_url', ''))),
    '#description' => t('The Engage admin URL (Set automatically based on your API Key).'),
    '#attributes' => array('disabled' => 'disabled')
  );
  $form[$group]['rpx_signin_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Engage Signin Label'),
    '#default_value' => variable_get('rpx_signin_string', RPX_SIGNIN_STRING),
    '#description' => t('The text that will appear above the icons on the login page.'),
  );
  $form[$group]['rpx_accounts_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Engage Identities tab name'),
    '#default_value' => variable_get('rpx_accounts_string', RPX_ACCOUNTS_STRING),
    '#description' => t('The name of the tab in the user profile where users can manage their 3rd party identities.'),
  );
  $form[$group]['rpx_user_help_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Engage Identities tab help text'),
      '#default_value' => _rpx_user_help_text(),
    '#description' => t('The text in the Engage Identities tab that explains Janrain Engage to users.'),
    '#rows' => 10,
  );

  $providers = rpx_get_enabled_provider_array();
  if (count($providers)) {
    $group = 'providers';
    $setup_url = variable_get('rpx_admin_url', '');
    $setup_url = $setup_url ? $setup_url . '/setup_providers' : 'https://rpxnow.com/account';
    $form[$group] = array(
      '#type' => 'fieldset',
      '#title' => t('IDENTITY PROVIDERS'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('<a href="@setup_url" target="_blank">Configure/add providers here</a>. Don\'t forget to save this settings page afterwards to update your list of enabled providers from the Engage servers.', array('@setup_url' => $setup_url)),
    );
    $form[$group]['list'] = array(
      '#type' => 'item',
      '#value' => theme('item_list', $providers)
    );
  }

  $group = 'authentication';
  $form[$group] = array(
    '#type' => 'fieldset',
    '#title' => t('AUTHENTICATION'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form[$group]['rpx_attach_login_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Janrain Engage sign-in on login forms'),
    '#default_value' => variable_get('rpx_attach_login_form', 0) ? 1 : 0,
    '#description' => t('Display provider links and icons in the \'User login\' block and on the user login page.'),
  );

  $form[$group]['indent'] = array(
    '#type' => 'fieldset',
    '#states' => array(
      'invisible' => array(
        'input[name="rpx_attach_login_form"]' => array('checked' => FALSE),
      )
    ),
  );
  $form[$group]['indent']['rpx_login_icons_size'] = array(
    '#type' => 'radios',
    '#default_value' => variable_get('rpx_login_icons_size', 'small'),
    '#title' => t('Icon size'),
    '#options' => array(
      'small' => t('Small (default)'),
      'medium' => t('Medium'),
    ),
    '#description' => t('Choose the size of icons to use in the \'User login\' block and on the user login page.'),
  );
  $form[$group]['indent']['rpx_login_links_weight'] = array(
    '#type' => 'weight',
    '#delta' => 150,
    '#title' => t('Icon positioning'),
    '#default_value' => variable_get('rpx_login_links_weight', 150),
    '#description' => t('Choose a weight for provider links and icons. Choosing a higher weight will display the links and icons lower down in the \'User login\' block and on the user login page.'),
  );

  $form[$group]['rpx_force_registration_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force registration form'),
    '#default_value' => variable_get('rpx_force_registration_form', 0) ? 1 : 0,
    '#description' => t('Always show registration form on Engage login, in case there are additional required fields to be captured'),
  );

  $form[$group]['rpx_extended_authinfo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Request extended profile data.'),
    '#default_value' => variable_get('rpx_extended_authinfo', 0) ? 1 : 0,
    '#description' => t('If checked, extended profile data will be requested from Engage at each user signin. This feature is available to <a href="@get_engage" target="_blank">Plus</a> and <a href="@get_engage" target="_blank">Pro</a> Janrain customers, and ignored for Basic accounts.', array('@get_engage' => url('http://www.janrain.com/products/engage/get-janrain-engage'))),
  );

  $form[$group]['rpx_import_profile_photo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import Profile Picture'),
    '#default_value' => variable_get('rpx_import_profile_photo', 0) ? 1 : 0,
    '#description' => t('If checked, the user\'s profile picture will be automatically imported as their Drupal profile picture.'),
  );

  // is this needed in Drupal 7?
  $form[$group]['rpx_javascript_global'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force Engage javascript on every page'),
    '#default_value' => variable_get('rpx_javascript_global', 0) ? 1 : 0,
    '#description' => t('Certain caching setups may cause some Engage login links not to work. If that is the case, try checking this option to resolve the issue. You may also need to clear the cache on the <a href="!performance_link">Performance</a> page.', array('!performance_link' => url('admin/settings/performance'))),
  );
  if (module_exists('openid')) {
    $form[$group]['rpx_openid_override'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow Engage to override OpenID'),
      '#default_value' => variable_get('rpx_openid_override', 0) ? 1 : 0,
      '#description' => t('Allow the Engage login link to replace the core OpenID module login link.'),
    );
  }

  $group = 'social';
  $rpx_admin_url = variable_get('rpx_admin_url', '');
  $form[$group] = array(
    '#type' => 'fieldset',
    '#title' => t('SOCIAL SHARING'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('To configure social sharing providers visit <a href="@social_link" target="_blank">Janrain\'s rpxnow site</a>.', array('@social_link' => $rpx_admin_url ? $rpx_admin_url . '/social_publishing_2' : 'https://rpxnow.com')),
  );
  $form[$group]['rpx_social_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable social sharing.'),
    '#default_value' => variable_get('rpx_social_enabled', 0),
    '#description' => t('Enable social sharing for the site. Don\'t forget to edit the social sharing settings for individual <a href="!content_types_link" target="_blank">content types</a>.', array('!content_types_link' => url('admin/content/types/'))),
  );

  $form[$group]['content_title'] = array(
    '#title' => t('Content title'),
    '#value' => t('<strong>CONTENT</strong>'),
  );
  $form[$group]['node_sharing_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social sharing settings for content'),
  );
  $form[$group]['node_sharing_settings']['rpx_default_label_nodes'] = array(
    '#type' => 'textfield',
    '#title' => t('Default label for shared content'),
    '#default_value' => variable_get('rpx_default_label_nodes', RPX_DEFAULT_LABEL_NODES_STRING),
    '#description' => t('Specify the default short string (including tokens) that will appear at the top of the social sharing widget. This setting can be overridden on the content type edit page.')
  );
  $form[$group]['node_sharing_settings']['rpx_default_message_nodes'] = array(
    '#type' => 'textfield',
    '#title' => t('Default message for shared content'),
    '#default_value' => variable_get('rpx_default_message_nodes', RPX_DEFAULT_MESSAGE_NODES_STRING),
    '#description' => t('Specify the default message text (including tokens) to be used when sharing content. This setting can be overridden on the content type edit page.')
  );
  $form[$group]['node_sharing_settings']['rpx_default_linktext_nodes'] = array(
    '#type' => 'textfield',
    '#title' => t('Default link text for shared content'),
    '#default_value' => variable_get('rpx_default_linktext_nodes', RPX_DEFAULT_LINKTEXT_NODES_STRING),
    '#description' => t('Specify the default action description (including tokens) to be used when sharing content.  This setting can be overridden on the content type edit page.')
  );
  $form[$group]['node_sharing_settings']['rpx_default_title_nodes'] = array(
    '#type' => 'textfield',
    '#title' => t('Default title for shared content'),
    '#default_value' => variable_get('rpx_default_title_nodes', RPX_DEFAULT_TITLE_NODES_STRING),
    '#description' => t('Specify the default title (including tokens) to be used when sharing content. This setting can be overridden on the content type edit page.')
  );
  $form[$group]['node_sharing_settings']['rpx_default_summary_nodes'] = array(
    '#type' => 'textfield',
    '#title' => t('Default description for shared content'),
    '#default_value' => variable_get('rpx_default_summary_nodes', RPX_DEFAULT_SUMMARY_NODES_STRING),
    '#description' => t('Specify the default description (including tokens) to be used when sharing content. This setting can be overridden on the content type edit page.')
  );

  $form[$group]['comments_title'] = array(
    '#title' => t('Content title'),
    '#value' => t('<strong>COMMENTS</strong>'),
  );
  $form[$group]['comments_sharing_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social sharing settings for comments'),
  );
  $form[$group]['comments_sharing_settings']['rpx_default_label_comments'] = array(
    '#type' => 'textfield',
    '#title' => t('Default label for shared comments'),
    '#default_value' => variable_get('rpx_default_label_comments', RPX_DEFAULT_LABEL_COMMENTS_STRING),
    '#description' => t('Specify the default short string (including tokens) that will appear at the top of the social sharing widget. This setting can be overridden on the content type edit page.')
  );
  $form[$group]['comments_sharing_settings']['rpx_default_message_comments'] = array(
    '#type' => 'textfield',
    '#title' => t('Default message for shared comments'),
    '#default_value' => variable_get('rpx_default_message_comments', RPX_DEFAULT_MESSAGE_COMMENTS_STRING),
    '#description' => t('Specify the default message text (including tokens) to be used when sharing comments. This setting can be overridden on the content type edit page.')
  );
  $form[$group]['comments_sharing_settings']['rpx_default_linktext_comments'] = array(
    '#type' => 'textfield',
    '#title' => t('Default link text for shared comments'),
    '#default_value' => variable_get('rpx_default_linktext_comments', RPX_DEFAULT_LINKTEXT_COMMENTS_STRING),
    '#description' => t('Specify the default action description (including tokens) to be used when sharing comments.  This setting can be overridden on the content type edit page.')
  );
  $form[$group]['comments_sharing_settings']['rpx_default_title_comments'] = array(
    '#type' => 'textfield',
    '#title' => t('Default title for shared comments'),
    '#default_value' => variable_get('rpx_default_title_comments', RPX_DEFAULT_TITLE_COMMENTS_STRING),
    '#description' => t('Specify the default title (including tokens) to be used when sharing comments. This setting can be overridden on the content type edit page.')
  );
  $form[$group]['comments_sharing_settings']['rpx_default_summary_comments'] = array(
    '#type' => 'textfield',
    '#title' => t('Default description for shared comments'),
    '#default_value' => variable_get('rpx_default_summary_comments', RPX_DEFAULT_SUMMARY_COMMENTS_STRING),
    '#description' => t('Specify the default description (including tokens) to be used when sharing comments. This setting can be overridden on the content type edit page.')
  );

  $form[$group]['token_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Token help'),
  );

  // Add the token tree UI.
  $prepend_text = '<p>' . t('Note: since the Token module does not provide a [node-body] token, you can use the [rpx-node-body] pseudo-token instead.') . '</p>';
  if (module_exists('token')) {
    $form[$group]['token_help']['token_browser'] = array(
      '#value' => $prepend_text . theme('token_tree', array('comment', 'global', 'node', 'user')),
    );
  }
  else {
    $form[$group]['token_help']['token_browser'] = array(
      '#value' => $prepend_text . t('<a href="@token_module_link" target="_blank">Token</a> module is not enabled. Enable it if you want to use the token browser here.', array('@token_module_link' => 'http://drupal.org/project/token'))
    );
  }

  $group = 'email';
  $form[$group] = array(
    '#type' => 'fieldset',
    '#title' => t('VERIFICATION E-MAIL'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $email_token_help = t('Available variables are: !username, !site, !password, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !login_url. ');
  if (!module_exists('token')) {
    $email_token_help .= t('You can also install and enable the <a href="@token_module_link" target="_blank">Token</a> module, if you want to use the token browser to customize the email message.', array('@token_module_link' => 'http://drupal.org/project/token'));
  }
  else {
    $email_token_help .= t('You can also use the token browser below to customize the email message.');
  }
  $form[$group]['verify_rpx'] = array(
    '#type' => 'fieldset',
    '#title' => t('Verification Email'),
    '#description' => '<p>' . t('Some Engage providers do not provide verified email addresses. If your <a href="@user_settings">user settings</a> require emails be verified, an email will be dispatched to these users in order to verify their email address before they can login.', array('@user_settings' => url('admin/user/settings'))) . ' ' . $email_token_help . '</p>',
  );
  $form[$group]['verify_rpx']['rpx_bypass_email_verification'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bypass email verification for Engage registration'),
    '#default_value' => variable_get('rpx_bypass_email_verification', 0) ? 1 : 0,
    '#description' => t('If checked, users who register using Engage will not be required verify their email address even if their provider does not provide a verified email.'),
  );
  $form[$group]['verify_rpx']['rpx_mail_rpx_confirm_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => _rpx_mail_text('rpx_confirm_email_subject', NULL, array(), FALSE),
    '#maxlength' => 180,
  );
  $form[$group]['verify_rpx']['rpx_mail_rpx_confirm_email_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => _rpx_mail_text('rpx_confirm_email_body', NULL, array(), FALSE),
    '#rows' => 15,
  );

  // Add the token tree UI.
  if (module_exists('token')) {
    $form[$group]['token_help'] = array(
      '#value' => theme('token_tree', array('global', 'rpx')),
    );
  }

  $form['#submit'][] = 'rpx_admin_settings_submit';

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['buttons']['reset'] = array(
    '#value' => l(t('Reset to defaults'), 'admin/user/rpx/settings/reset'),
  );

  return $form;
}

/**
 * Validate rpx_admin_settings submissions.
 */
function rpx_admin_settings_validate($form, &$form_state) {
  $api_key = $form_state['values']['rpx_apikey'];

  $lookup = RPX::lookup($api_key, 'apiKey');

  if (!$lookup) {
    form_set_error('', t('Error contacting Engage.  Please verify your internet connection and try again.'));
    return;
  }
  if ($lookup == 'No RP found') {
    form_set_error('rpx_apikey', t('Looks like your API key was incorrect.  Please verify the key and try again.'));
    return;
  }
  // pass the lookup results to rpx_admin_settings_submit()
  variable_set('rpx_lookup_results', $lookup);
}

/**
 * Submit handler to update Engage settings.
 *
 * @see rpx_admin_settings_form()
 * @see rpx_admin_settings_validate()
 */
function rpx_admin_settings_submit($form, &$form_state) {
  // Delete all lookup sourced variables.
  variable_del('rpx_realm');
  variable_del('rpx_realm_scheme');
  variable_del('rpx_enabled_providers');
  variable_del('rpx_app_id');
  variable_del('rpx_social_pub');
  variable_del('rpx_admin_url');
  variable_del('rpx_mapping_api');

  $lookup = variable_get('rpx_lookup_results', '');
  variable_del('rpx_lookup_results');

  variable_set('rpx_apikey', $lookup['apiKey']);
  variable_set('rpx_realm', $lookup['realm']);
  variable_set('rpx_realm_scheme', $lookup['realmScheme']);
  variable_set('rpx_app_id', $lookup['appId']);
  variable_set('rpx_social_pub', $lookup['socialPub']);
  variable_set('rpx_admin_url', $lookup['adminUrl']);

  $use_mapping_api = strpos($lookup['capabilities'], 'mapping_api');
  variable_set('rpx_mapping_api', ($use_mapping_api === FALSE) ? 0 : 1);

  $providers = RPX::get_enabled_providers($lookup['realm'], $lookup['realmScheme']);
  variable_set('rpx_enabled_providers', $providers);

  // Exclude unnecessary elements.
  unset($form_state['values']['submit'], $form_state['values']['reset'], $form_state['values']['form_id'], $form_state['values']['op'], $form_state['values']['form_token'], $form_state['values']['form_build_id']);

  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }

  drupal_set_message(t('The configuration options have been saved.'));

  // Clear the cached pages and blocks.
  cache_clear_all();
  // Rebuild menu to show/hide the "Janrain Engage Identities" depending on the
  // API key settings.
  menu_rebuild();
}

/**
 * Menu callback; reset Engage module settings.
 */
function rpx_admin_reset_confirm(&$form_state) {
  return confirm_form(array(), t('Are you sure you want to reset the Janrain Engage configuration options to their default values?'), 'admin/user/rpx/settings/', t('Any customizations will be lost. This action cannot be undone.'), t('Reset'));
}

/**
 * Process settings reset form submissions.
 */
function rpx_admin_reset_confirm_submit($form, &$form_state) {
  variable_del('rpx_attach_login_form');
  variable_del('rpx_bypass_email_verification');
  variable_del('rpx_extended_authinfo');
  variable_del('rpx_mapping_api');
  variable_del('rpx_force_registration_form');
  variable_del('rpx_import_profile_photo');
  variable_del('rpx_javascript_global');
  variable_del('rpx_openid_override');
  variable_del('rpx_signin_string');
  variable_del('rpx_accounts_string');
  variable_del('rpx_user_help_text');
  variable_del('rpx_social_enabled');
  variable_del('rpx_mail_rpx_confirm_email_body');
  variable_del('rpx_mail_rpx_confirm_email_subject');
  variable_del('rpx_default_label_nodes');
  variable_del('rpx_default_message_nodes');
  variable_del('rpx_default_linktext_nodes');
  variable_del('rpx_default_title_nodes');
  variable_del('rpx_default_summary_nodes');
  variable_del('rpx_default_label_comments');
  variable_del('rpx_default_message_comments');
  variable_del('rpx_default_linktext_comments');
  variable_del('rpx_default_title_comments');
  variable_del('rpx_default_summary_comments');
  variable_del('rpx_login_icons_size');
  variable_del('rpx_login_links_weight');

  drupal_set_message(t('The configuration options have been reset to their default values.'));
  $form_state['redirect'] = 'admin/user/rpx/settings/';
}

/**
 * Menu callback: Generate a form to configure Drupal profile to Engage mappings
 * used to pre-fill Profile fields with Engage data at signup and import Engage
 * profile data when a 3rd party account is linked.
 *
 * @ingroup forms
 * @see rpx_mapping_settings_form_submit()
 */
function rpx_mapping_settings_form() {
  $catalog = _rpx_drupal_field_catalog();
  $map = variable_get('rpx_profile_fields_map', array());
  // Add empty mapping to the end of list
  $map[] = array();

  // Get a list of all available Engage fields.
  $query = db_query("SELECT fid, path FROM {rpx_profile_field}");
  $rpx_fields = array();
  while ($field = db_fetch_object($query)) {
    $rpx_fields[$field->fid] = array(
      'fid' => $field->fid,
      'path' => $field->path,
    );
  }

  foreach ($map as $mid => $mapping) {
    $form[$mid] = array(
      'fid' => array(
        '#type' => 'select',
        '#options' => _rpx_engage_field_options(),
        '#description' => t('Data path.'),
        '#attributes' => array('class' => 'rpx-field-select mid-' . $mid),
      ),
      'separator' => array(
        '#value' => '=>'
      ),
      'field' => array(
        '#type' => 'select',
        '#options' => $catalog,
        '#default_value' => $mapping['field'],
        '#description' => t('Field.'),
        '#attributes' => array('class' => 'field-select mid-' . $mid),
      ),
      'edit' => array(
        '#value' => isset($mapping['fid']) ? l(t('edit'), "admin/user/rpx/mapping/edit/$mid") : '&nbsp;',
      ),
    );
  }

  if (count($form)) {
    $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  }

  drupal_add_js(drupal_get_path('module', 'rpx_ui') . '/rpx_ui.js');

  $settings = array('map' => $map, 'rpx_fields' => $rpx_fields);
  drupal_add_js($settings, 'setting');

  $form['#tree'] = TRUE;

  return $form;
}

/**
 * Submit handler to update changed Drupal to Engage data mapping.
 *
 * @see rpx_mapping_settings_form()
 */
function rpx_mapping_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $old_map = variable_get('rpx_profile_fields_map', array());
  $map = array();

  foreach (element_children($values) as $mid) {
    if (is_numeric($mid)) {
      // All field mappings should include a fid.
      if(!empty($values[$mid]['fid'])) {
        $map[$mid] = array(
          'fid' => $values[$mid]['fid'],
          'field' =>  $values[$mid]['field'],
          'update' => isset($old_map[$mid]['update']) ? $old_map[$mid]['update'] : RPX_UPDATE_NONE,
        );
        if (isset($old_map[$mid]['providers'])) {
          $map[$mid]['providers'] = $old_map[$mid]['providers'];
        }
      }
      // The mapping is dropped; we need to delete its records from the
      // rpx_mapping_provider table.
      else {
        db_query("DELETE FROM {rpx_mapping_provider} WHERE mid = %d", $mid);
      }
    }
  }

  variable_set('rpx_profile_fields_map', $map);
  drupal_set_message(t('Profile to Engage data mapping has been updated.'));
}

/**
 * Menu callback; deletes a Engage field from the Drupal to Engage mapping
 * configuration.
 */
function rpx_profile_field_delete(&$form_state, $fid = NULL) {
  $field = db_result(db_query("SELECT title FROM {rpx_profile_field} WHERE fid = %d", $fid));
  if (!$field) {
    drupal_not_found();
    drupal_exit();
  }
  $form['fid'] = array('#type' => 'value', '#value' => $fid);
  $form['title'] = array('#type' => 'value', '#value' => $field);

  return confirm_form($form,
    t('Are you sure you want to delete the Engage field %field?', array('%field' => $field)), 'admin/user/rpx/fields',
    t('This action cannot be undone. The Drupal to Engage data mappings using this field will be deleted as well.'),
    t('Delete'), t('Cancel'));
}

/**
 * Process an Engage field delete form submission.
 */
function rpx_profile_field_delete_submit($form, &$form_state) {
  db_query("DELETE FROM {rpx_profile_field} WHERE fid = %d", $form_state['values']['fid']);

  // Remove the mappings (if any) that use the field, also deleting their
  // records from the rpx_mapping_provider table.
  $map = variable_get('rpx_profile_fields_map', array());
  foreach ($map as $mid => $mapping) {
    if ($mapping['fid'] == $form_state['values']['fid']) {
      unset($map[$mid]);
      db_query("DELETE FROM {rpx_mapping_provider} WHERE mid = %d", $mid);
    }
  }
  variable_set('rpx_profile_fields_map', $map);

  cache_clear_all();

  drupal_set_message(t('The Engage field %field has been deleted.', array('%field' => $form_state['values']['title'])));
  watchdog('rpx_ui', 'Engage field %field deleted.', array('%field' => $form_state['values']['title']), WATCHDOG_NOTICE, l(t('view'), 'admin/user/rpx/fields'));

  $form_state['redirect'] = 'admin/user/rpx/fields';
  return;
}

/**
 * Menu callback: Generate a form to manage Engage profile fields.
 *
 * @ingroup forms
 * @see rpx_profile_field_overview_validate()
 * @see rpx_profile_field_overview_submit()
 */
function rpx_profile_field_overview_form() {
  $fields = db_query("SELECT fid, title, path FROM {rpx_profile_field}");
  while ($field = db_fetch_object($fields)) {
    $admin_field_path = 'admin/user/rpx/fields/';
    $form[$field->fid] = array (
      'title' => array(
        '#value' => $field->title,
      ),
      'path' => array(
        '#value' => $field->path,
      ),
      'edit' => array(
        '#value' => l(t('edit'), $admin_field_path . 'edit/' . $field->fid),
      ),
      'delete' => array(
        '#value' => l(t('delete'), $admin_field_path . 'delete/' . $field->fid),
      ),
    );
  }

  // Additional row: add new field.
  $form['_edit_field'] = array(
    'title' => array(
      '#type' => 'textfield',
      '#size' => 15,
      '#attributes' => array('class' => 'rpx-field-title-input'),
      '#description' => t('Title'),
      '#prefix' => '<div class="add-new-placeholder">' . t('Add new field') .'</div>',
    ),
    'path' => array(
      '#type' => 'textfield',
      '#size' => 30,
      '#attributes' => array('class' => 'rpx-path-input'),
      '#description' => t('Engage data path'),
      '#prefix' => '<div class="add-new-placeholder">&nbsp;</div>',
    ),
  );

  $path_help = '<dl>';
  if (module_exists('token')) {
    $path_help .= '<dt>' . t('You can choose the path here. Please note that not all providers return all of the data below, and some of the data is only available to <a href="@get_engage" target="_blank">Plus</a> and <a href="@get_engage" target="_blank">Pro</a> Janrain customers. You must enable extended profile data in the <a href="@settings" target="_blank">settings</a> if you want that data to be requested from Engage at user sign-in. For complete information about the user data returned by Engage see <a href="@auth_info_help" target="_blank">this</a>.', array('@get_engage' => url('http://www.janrain.com/products/engage/get-janrain-engage'), '@settings' => url('admin/user/rpx'), '@auth_info_help' => 'https://rpxnow.com/docs#api_auth_info')) . '</dt>';
    $path_help .= '<dd>' . theme('rpx_path_tree') . '</dd>';
  }
  $path_help .= '</dl>';

  $form['path_help'] = array(
    '#value' => $path_help,
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save new field'),
  );
  $form['buttons']['reset'] = array(
     '#value' => l(t('Reset to defaults'), 'admin/user/rpx/fields/reset'),
  );

  $form['#tree'] = TRUE;
  $form['#validate'][] = '_rpx_profile_field_forms_validate';
  $form['#submit'][] = '_rpx_profile_field_forms_submit';

  return $form;
}

/**
 * Menu callback; confirmation form.
 */
function rpx_profile_field_reset_confirm(&$form_state) {
  return confirm_form($form, t('Are you sure you want to revert to the default Janrain Engage profile fields?'), 'admin/user/rpx/fields/', t('Any new fields that you have created will be lost. Any existing mappings will be deleted as well. This action cannot be undone.'), t('Reset'));
}

/**
 * Inserts default values to rpx_profile_field.
 */
function _rpx_profile_field_insert_defaults() {
  $fields = array(
    array('First Name', "['profile']['name']['givenName']"),
    array('Last Name', "['profile']['name']['familyName']"),
    array('Display Name', "['profile']['displayName']"),
    array('Gender', "['profile']['gender']"),
    array('Birthday', "['profile']['birthday']"),
    array('Phone Number', "['profile']['phoneNumber']"),
    array('Street Address', "['profile']['address']['streetAddress']"),
    array('City', "['profile']['address']['locality']"),
    array('State/Province', "['profile']['address']['region']"),
    array('Zipcode/Postal Code', "['profile']['address']['postalCode']"),
    array('Country', "['profile']['address']['country']"),
  );
  foreach ($fields as $field) {
    db_query("INSERT INTO {rpx_profile_field} (title, path, parsed_path) VALUES ('%s','%s','%s')", $field[0], $field[1], serialize(_rpx_parse_path($field[1])));
  }
}

/**
 * Process fields reset form submissions.
 *
 * Reset Engage fields by deleting all existing fields and creating default ones
 * (those that are created at module installation). As fid's are going to
 * change, also delete mappings and their records in the rpx_mapping_provider
 * table.
 */
function rpx_profile_field_reset_confirm_submit($form, &$form_state) {
  db_query("DELETE FROM {rpx_profile_field}");

  _rpx_profile_field_insert_defaults();

  // Delete field map.
  variable_set('rpx_profile_fields_map', array());

  // Delete data provider records.
  db_query("DELETE FROM {rpx_mapping_provider}");

  drupal_set_message(t('The Janrain Engage profile fields have been reverted to the defaults.'));
  $form_state['redirect'] = 'admin/user/rpx/fields/';
}

/**
 * Menu callback: Generate a form to edit an Engage profile field.
 *
 * @ingroup forms
 * @see rpx_profile_field_edit_form_validate()
 * @see rpx_profile_field_edit_form_submit()
 */
function rpx_profile_field_edit_form(&$form_state, $arg = NULL) {
  if (is_numeric($arg)) {
    $fid = $arg;

    $field = db_fetch_array(db_query('SELECT fid, title, path FROM {rpx_profile_field} WHERE fid = %d', $fid));

    if (!$field) {
      drupal_not_found();
      drupal_exit();
    }
    drupal_set_title(t('Edit %title Engage field', array('%title' => $field['title'])));
    $form['_edit_field']['fid'] = array(
      '#type' => 'value',
      '#value' => $fid,
    );
  }
  else {
    drupal_not_found();
    drupal_exit();
  }

  $form['_edit_field']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $field['title'],
    '#attributes' => array('class' => 'rpx-field-title-input'),
    '#description' => t('The title of the field. The title is shown in the mapping form next to the data path. An example title is "Verified email". '),
  );
  $form['_edit_field']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Engage data path'),
    '#default_value' => $field['path'],
    '#attributes' => array('class' => 'rpx-path-input'),
    '#description' => t("The path to the data within the Engage authentication dataset, in a PHP-like array referencing notation.
An example path is <code>['profile']['verifiedEmail']</code> or <code>['merged_poco']['emails'][0]['value']</code>. You can use the <a href=\"@provider-configuration\" target=\"_blank\">provider configuration</a> and <a href=\"@signin-test\" target=\"_blank\">sign-in test</a> tools to configure the data to be returned by providers, and to see it in action.", array('@provider-configuration' => variable_get('rpx_admin_url', '') . '/providers', '@signin-test' => variable_get('rpx_admin_url', '') . '/test')),
  );

  $path_help = '<dl>';
  if (module_exists('token')) {
    $path_help .= '<dt>' . t('You can choose the path here. Please note that not all providers return all of the data below, and some of the data is only available to <a href="@get_engage" target="_blank">Plus</a> and <a href="@get_engage" target="_blank">Pro</a> Janrain customers. You must enable extended profile data in the <a href="@settings" target="_blank">settings</a> if you want that data to be requested from Engage at user sign-in. For complete information about the user data returned by Engage see <a href="@auth_info_help" target="_blank">this</a>.', array('@get_engage' => url('http://www.janrain.com/products/engage/get-janrain-engage'), '@settings' => url('/admin/user/rpx'), '@auth_info_help' => 'https://rpxnow.com/docs#api_auth_info')) . '</dt>';
    $path_help .= '<dd>' . theme('rpx_path_tree') . '</dd>';
  }
  else {
    $path_help .= '<dt>' . t('Please note: the <a href="@token_module_link" target="_blank">Token</a> module is not required for the data mapping to work, but you might want to install and enable it in order to see a list of all available paths here.', array('@token_module_link' => 'http://drupal.org/project/token')) . '</dt>';
  }
  $path_help .= '</dl>';
  $form['path_help'] = array(
    '#value' => $path_help,
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save field'),
  );

  $form['#tree'] = TRUE;

  $form['#validate'][] = '_rpx_profile_field_forms_validate';
  $form['#submit'][] = '_rpx_profile_field_forms_submit';

  return $form;
}

function _rpx_profile_path_validate_error() {
  form_set_error('_edit_field][path', t('The specified path is not valid. Please check that it does not contain spaces or any other special characters except brackets ([]) and apostrophe (\'), and it would make a valid PHP array reference if appended to an array variable.'));
}

/**
 * Extract path components.
 *
 * @param string $path
 * @return array
 */
function _rpx_parse_path($path) {
  $path = trim($path, '[]');
  $parts = explode('][', $path);
  if (!empty($parts)) {
    $parsed = array();
    foreach ($parts as $part) {
      if (is_numeric($part)) {
        $parsed[] = intval($part);
      }
      elseif (preg_match("/^\'([a-z0-9_]+)\'$/i", $part, $matches)) {
        $parsed[] = $matches[1];
      }
      else {
        return NULL;
      }
    }
    return $parsed;
  }
  else {
    return NULL;
  }
}

/**
 * Validate rpx_profile_field_overview_form and rpx_profile_field_edit_form submissions.
 */
function _rpx_profile_field_forms_validate($form, &$form_state) {
  $field = $form_state['values']['_edit_field'];

  // Missing title.
  if (!$field['title']) {
    form_set_error('_edit_field][title', t('You need to provide a title.'));
  }
  // Missing data path.
  if (!$field['path']) {
    form_set_error('_edit_field][path', t('You need to provide a data path.'));
  }

  // Validate the data path by parsing it, also save parsed path to values.
  $parsed_path = _rpx_parse_path($field['path']);
  if ($parsed_path) {
    $form_state['values']['_edit_field']['parsed_path'] = $parsed_path;
  }
  else {
    _rpx_profile_path_validate_error();
  }

  //
  // Now check that no existing fields have the desired name and/or path.
  //
  $fid = isset($field['fid']) ? $field['fid'] : -1;

  $title = db_result(db_query("SELECT title FROM {rpx_profile_field} WHERE fid <> %d AND title = '%s'", $fid, $field['title']));
  if ($title) {
    form_set_error('_edit_field][title', t('The specified title is already in use.'));
  }

  $path = db_result(db_query("SELECT path FROM {rpx_profile_field} WHERE fid <> %d AND path = '%s'", $fid, $field['path']));
  if ($path) {
    form_set_error('_edit_field][path', t('The specified path is already in use.'));
  }
}

/**
 * Process rpx_profile_field_overview and rpx_profile_field_form submissions.
 */
function _rpx_profile_field_forms_submit($form, &$form_state) {
  $field = $form_state['values']['_edit_field'];

  // Remove all elements that are not rpx_profile_field columns.
  $values = array_intersect_key($field, array_flip(array('title', 'path', 'parsed_path')));
  if (!isset($field['fid'])) {
    db_query("INSERT INTO {rpx_profile_field} (title, path, parsed_path) VALUES ('%s','%s','%s')", $values['title'], $values['path'], serialize($values['parsed_path']));
    drupal_set_message(t('The field has been created.'));
    watchdog('rpx_ui', 'Engage profile field %field added with path %path.', array('%field' => $field['title'], '%path' => $field['path']), WATCHDOG_NOTICE, l(t('view'), 'admin/user/rpx/fields'));
  }
  else {
    db_query("UPDATE {rpx_profile_field} SET title = '%s', path = '%s', parsed_path = '%s' WHERE fid = %d", $values['title'], $values['path'], serialize($values['parsed_path']), $field['fid']);
    drupal_set_message(t('The field has been updated.'));
  }
  cache_clear_all();
  menu_rebuild();

  $form_state['redirect'] = 'admin/user/rpx/fields';
  return;
}

/*
 * Helper function: creates a provider weight table within the form.
 */
function _rpx_provider_table_generate(&$form, $providers) {
  $entire_list = TRUE;
  $provider_data = _rpx_providers($entire_list);
  // Build a provider array starting with the selected providers.
  $providers_all = array_merge($providers, array_diff(array_keys($provider_data), $providers));

  $order = -10;
  foreach ($providers_all as $provider) {
    $form['field_update']['providers'][$provider]['title'] = array(
      '#type' => 'item',
      '#value' =>  theme('rpx_icon', $provider, 'small', 'rpx-icon-inline') . '<span' . drupal_attributes(array('class' => 'rpx-provider-title')) . '>' . $provider_data[$provider] .  '</span>',
    );
    $form['field_update']['providers'][$provider]['select'] = array(
      '#type' => 'checkbox',
      '#default_value' => in_array($provider, $providers),
    );
    $form['field_update']['providers'][$provider]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $order,
    );
    $order++;
  }
}

/*
 * Helper function: returns an array of providers sorted according to their
 * weight in the provider weight table.
 */
function _rpx_get_sorted_providers($providers) {
  foreach($providers as $k => $v) {
    if(!$providers[$k]['select']) {
      unset($providers[$k]);
    }
    else {
      $providers[$k] = $providers[$k]['weight'];
    }
  }
  asort($providers);
  return array_keys($providers);
}

/**
 * Menu callback: Generate a form to edit an Engage to Drupal mapping.
 *
 * @ingroup forms
 * @see rpx_profile_mapping_edit_form_submit()
 */
function rpx_profile_mapping_edit_form(&$form_state, $arg = NULL) {
  $map = variable_get('rpx_profile_fields_map', array());
  if (is_numeric($arg)) {
    $mid = $arg;

    if (!isset($map[$mid]['fid'])) {
      drupal_not_found();
      drupal_exit();
    }

    // Set title for the edit form.
    $field = db_fetch_object(db_query("SELECT title, path FROM {rpx_profile_field} WHERE fid = %d", $map[$mid]['fid']));
    drupal_set_title(t('Edit mapping for field %title (%path)', array('%title' => $field->title, '%path' => $field->path)));

    $form['mid'] = array(
      '#type' => 'value',
      '#value' => $mid,
    );
  }
  else {
    drupal_not_found();
    drupal_exit();
  }

  $form['field_update'] = array(
   '#type' => 'fieldset',
   '#title' => t('Field update options for the mapping'),
  );
  $form['field_update']['options'] = array(
    '#type' => 'radios',
    '#title' => t('Data mapping logic for 3rd party accounts'),
    '#default_value' => isset($map[$mid]['update']) ? $map[$mid]['update'] : RPX_UPDATE_NONE,
    '#options' => array(
      RPX_UPDATE_NONE => t('Do not update the data field upon user login or when a linked account is added (default)'),
      RPX_UPDATE_EMPTY => t('Only update the data field if it is empty at user login or when a linked account is added'),
      RPX_UPDATE_ALWAYS => t('Update the data field (including overwriting existing data) at user login or when any
 linked account is added'),
      RPX_UPDATE_ADD => t('Update the data field as an additional value (but do not overwrite existing data) at user login or when a linked account is added (this will only work for fields that allow multiple values)'),
      RPX_UPDATE_MAYBE => t('Update the data field (including overwriting existing data) only when a higher priority provider account is linked or used to login (use the table below to set priorities)'),
    ),
  );
  $form['field_update']['providers'] = array(
    '#theme' => 'rpx_provider_weight_table',
  );

  $providers = isset($map[$mid]['providers']) ? $map[$mid]['providers'] : variable_get('rpx_default_provider_weight', array_keys(_rpx_providers(TRUE)));

  _rpx_provider_table_generate($form, $providers);

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#tree'] = TRUE;

  return $form;
}

/**
 * Submit handler to update Engage to Drupal mapping.
 *
 * @see rpx_profile_mapping_edit_form()
 */
function rpx_profile_mapping_edit_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $map = variable_get('rpx_profile_fields_map', array());
  $mapping = &$map[$values['mid']];

  $update = $values['field_update']['options'];
  $mapping['update'] = $update;

  if ($update == RPX_UPDATE_MAYBE) {
    $mapping['providers'] = _rpx_get_sorted_providers($values['field_update']['providers']);
  }

  variable_set('rpx_profile_fields_map', $map);

  // Warn user if he tries to configure the mapping to append new data to a
  // single value field.
  if ($update == RPX_UPDATE_ADD) {
    drupal_set_message(t('The field cannot accept multiple values.'), 'warning');
  }

  // Get title and path for the field that is being mapped, so that we can
  // print a friendlier message.
  $field = db_fetch_object(db_query("SELECT title, path FROM {rpx_profile_field} WHERE fid = %d", $mapping['fid']));
  drupal_set_message(t('Mapping options for field %title (%path) have been updated.', array('%title' => $field->title, '%path' => $field->path)));
  $form_state['redirect'] = 'admin/user/rpx/mapping';
}

/**
 * Menu callback: Generate a form to edit the default Engage to Drupal mapping
 * options.
 *
 * @ingroup forms
 * @see rpx_profile_mapping_default_submit()
 */
function rpx_profile_mapping_default(&$form_state) {
  $map = variable_get('rpx_profile_fields_map', array());

  $form['field_update'] = array(
   '#type' => 'fieldset',
   '#title' => t('Default field update options for new mappings'),
  );

  $form['field_update']['providers'] = array(
    '#theme' => 'rpx_provider_weight_table',
  );

  $providers = variable_get('rpx_default_provider_weight', array_keys(_rpx_providers(TRUE)));
  _rpx_provider_table_generate($form, $providers);

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#tree'] = TRUE;

  return $form;
}

/**
 * Submit handler to update default Engage to Drupal mapping options.
 *
 * @see rpx_profile_mapping_default()
 */
function rpx_profile_mapping_default_submit($form, &$form_state) {
  $provider_weight = _rpx_get_sorted_providers($form_state['values']['field_update']['providers']);
  variable_set('rpx_default_provider_weight', $provider_weight);
  drupal_set_message(t('Default mapping settings have been updated.'));
  $form_state['redirect'] = 'admin/user/rpx/mapping';
}

/**
 * Theme Engage field mapping form.
 *
 * @ingroup themeable
 */
function theme_rpx_mapping_settings_form($form) {
  $rows = array();
  foreach (element_children($form) as $key) {
    // Skip form control elements.
    if (array_key_exists('separator', $form[$key])) {
      $field = &$form[$key];

      // Add the row
      $row = array();
      $row[] = drupal_render($field['fid']);
      $row[] = drupal_render($field['separator']);
      $row[] = drupal_render($field['field']);
      $row[] = drupal_render($field['edit']);
      $rows[] = array('data' => $row);
    }
  }
  $header = array(t('Engage Data Field'), '', t('Drupal Profile Field'), t('Operations'));

  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Theme a tree table.
 * Based on code from the Token module.
 *
 * @ingroup themeable
 */
function theme_rpx_path_tree_table($table_options) {
  foreach ($table_options['rows'] as &$row) {
    $row += array('class' => '');
    if (!empty($row['parent'])) {
      $row['class'] .= ' child-of-' . $row['parent'];
      unset($row['parent']);
    }
  }

  drupal_add_js(drupal_get_path('module', 'token') . '/jquery.treeTable.js');
  drupal_add_css(drupal_get_path('module', 'token') . '/jquery.treeTable.css');
  drupal_add_js(drupal_get_path('module', 'rpx_ui') . '/rpx_ui.js');
  drupal_add_css(drupal_get_path('module', 'rpx_ui') . '/rpx_ui.css');

  return theme('table', $table_options['header'], $table_options['rows'], $table_options['attributes'], $table_options['caption']);
}

/**
 * Provide a 'tree' display of RPX data paths.
 * Based on code from the Token module.
 *
 * @ingroup themeable
 */
function theme_rpx_path_tree() {
  module_load_include('inc', 'rpx_ui', 'rpx_ui.paths');

  $header = array(
    t('Name'),
    t('Path'),
    t('Description'),
  );

  $rows = _rpx_paths();

  $table_options = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('class' => 'rpx-path-tree'),
    'empty' => t('No paths available.'),
  );
  $table_options['caption'] = t('Navigate to the path you want and click on it to insert it into the path field.');
  $table_options['attributes']['class'] .= ' rpx-path-click-insert';

  return theme('rpx_path_tree_table', $table_options);
}

/**
 * Returns HTML for the Engage fields overview page.
 *
 * @ingroup themeable
 */
function theme_rpx_profile_field_overview_form($form) {
  drupal_add_css(drupal_get_path('module', 'rpx_ui') . '/rpx_ui.css');

  $rows = array();
  foreach (element_children($form) as $key) {
    // Skip form control elements.
    if (array_key_exists('path', $form[$key])) {
      $field = &$form[$key];

      // Add the row
      $row = array();
      $row[] = drupal_render($field['title']);
      $row[] = drupal_render($field['path']);
      $row[] = drupal_render($field['edit']);
      $row[] = drupal_render($field['delete']);
      $rows[] = array('data' => $row);
    }
  }

  $header = array(t('Title'), t('Path'));
  $header[] = array('data' => t('Operations'), 'colspan' => 2);

  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Returns HTML for the provider weight table.
 *
 * @ingroup themeable
 */
function theme_rpx_provider_weight_table($providers) {
  $rows = array();
  foreach (element_children($providers) as $provider) {
    $providers[$provider]['weight']['#attributes']['class'] = 'rpx-mapping-provider-weight';
    $row = array();
    $row[] = drupal_render($providers[$provider]['title']);
    $row[] = drupal_render($providers[$provider]['select']);
    $row[] = drupal_render($providers[$provider]['weight']);
    $rows[] = array(
      'data' => $row,
      'class' => 'draggable',
    );
  }
  $header = array(t('Provider'), t('Select'), t('Weight'));
  drupal_add_tabledrag('rpx-mapping-providers', 'order', 'sibling', 'rpx-mapping-provider-weight');
  return theme('table', $header, $rows, array('id' => 'rpx-mapping-providers'), t('Weight table: for the data mapping, select 3rd party account providers and arrange them from highest priority (top) to lowest priority (bottom).  Selected providers with higher priority have data that takes precedence over those with lower priority.'));
}
