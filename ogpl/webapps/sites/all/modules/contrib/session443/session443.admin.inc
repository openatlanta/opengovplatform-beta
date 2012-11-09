<?php

/**
 * @file
 * Admin pages for Session 443 module.
 */

/**
 * Admin settings form.
 * 
 * @todo For D7 use states to hide/show fields.
 *
 * @see session443_settings_form_submit()
 *
 * @ingroup forms
 */
function session443_settings_form(&$form_state) {

  $form['session443_enable'] = array(
    '#type' => 'radios',
    '#title' => t('Enable Redirects'),
    '#default_value' => _session443_test_https() ? variable_get('session443_enable', SESSION443_DISABLED) : SESSION443_DISABLED,
    '#options' => array(
      SESSION443_DISABLED => t('Disabled - No redirection will be performed.'),
      SESSION443_ENABLED => t('Enabled - Redirection may happen according to the rules below.'),
      SESSION443_ALL => t('Force all - Redirect all pages to HTTPS regardless of the rules below.'),
    ),
    '#disabled' => !_session443_test_https(),
    '#description' => t('This setting can only be changed if the web server has been properly configured for HTTPS. If this test has failed then you may attempt to override it <a href="!url">here</a>. If your site becomes unusable after enabling, please read the README.txt file.', array('!url' => _session443_modify_url_scheme(url($_GET['q'], array('absolute' => TRUE))))),
  );

  // User-based rules.
  $form['session443_user_rules'] = array(
    '#type' => 'fieldset',
    '#title' => t('User-based rules'),
  );
  $form['session443_user_rules']['session443_user_state_rule'] = array(
    '#type' => 'radios',
    '#title' => t('User state'),
    '#default_value' => variable_get('session443_user_state_rule', SESSION443_USER_MODE_FORCE_HTTPS_AND_HTTP),
    '#options' => array(
      SESSION443_USER_MODE_NONE => t('Do not redirect to HTTP or HTTPS based on user state.'),
      SESSION443_USER_MODE_FORCE_HTTPS => t('Redirect authenticated users to HTTPS and redirect anonymous users on login/registration pages to HTTPS. Anonymous users visiting other pages may use HTTP or HTTPS.'),
      SESSION443_USER_MODE_FORCE_HTTPS_AND_HTTP => t('Redirect authenticated users to HTTPS and redirect anonymous users to HTTP (with the exception of login/registration pages).'),
    ),
    '#description' => t('A potential issue in using split HTTP/HTTPS is session hijacking. This can happen when an authenticated user\'s session cookie is sent unencrypted and in the clear. A potential attacker can steal this cookie and masquerade as the authenticated user (for example with a tool such as <a href="http://en.wikipedia.org/wiki/Firesheep">Firesheep</a>). To prevent this scenario authenticated users must be redirected to HTTPS. Keeping only authenticated users on HTTPS is often used to balance performance and security as HTTP pages offer much faster response times.'),
  );
  $form['session443_user_rules']['session443_login_block'] = array(
    '#type' => 'radios',
    '#title' => t('Login block'),
    '#default_value' => variable_get('session443_login_block', SESSION443_LOGIN_BLOCK_FORCE_HTTPS),
    '#options' => array(
      SESSION443_LOGIN_BLOCK_FORCE_HTTPS => t('Force all pages with the login block to use HTTPS.'),
      SESSION443_LOGIN_BLOCK_CHANGE_FORM_ACTION => t('Only change the URL that the form is submitted to to use HTTPS.  There will be no browser lock icon on pages with the login block.  <a href="http://drupal.org/node/812572#comment-3897304">More information</a>.'),
      SESSION443_LOGIN_BLOCK_NONE => t("Don't do any manipulations of the login block. Passwords will not be transmitted securely."),
    ),
    '#description' => t('By default 443 Session forces all pages that have a login form to use HTTPS. If you use the login block on every page this may add unreasonable load to your server (HTTPS requires more server resources). This setting is only important if the login block is in use and authenticated users are redirected to HTTPS.'),
  );

  // Path-based rules.
  $form['session443_path_rules'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path-based rules'),
  );
  $form['session443_path_rules']['session443_additional_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional pages to make secure'),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
    '#wysiwyg' => FALSE,
    '#default_value' => variable_get('session443_additional_pages', "cart*\ndonat*"),
  );

  $form['session443_path_rules']['session443_ignore_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Ignore pages'),
    '#description' => t("The pages listed here will be ignored and no redirection will be performed. Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page. 404s are always ignored.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
    '#wysiwyg' => FALSE,
    '#default_value' => variable_get('session443_ignore_pages', "*/autocomplete/*\n*/ajax/*\n*/ahah/*"),
  );

  $form['#submit'][] = 'session443_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Admin settings form submit handler.
 *
 * @see session443_settings_form()
 *
 * @todo These messages need to be tested.
 *
 * @ingroup forms
 */
function session443_settings_form_submit($form, &$form_state) {
  $user_state_rule = $form_state['values']['session443_user_state_rule'];
  $user_state_rule_previous = $form['session443_user_rules']['session443_user_state_rule']['#default_value'];
  $enabled = $form_state['values']['session443_enable'];
  $enabled_previous = $form['session443_enable']['#default_value'];

  $insecure_authenticated_previous = ($enabled_previous == SESSION443_DISABLED || $user_state_rule_previous == SESSION443_USER_MODE_NONE);
  $secure_authenticated_previous = !$insecure_authenticated_previous;

  $insecure_authenticated = ($enabled == SESSION443_DISABLED || $user_state_rule == SESSION443_USER_MODE_NONE);
  $secure_authenticated = !$insecure_authenticated;

  // If the user-state setting changed from none to another option,
  // or if redirection is being enabled, then notify the user that they must
  // re-log-in.
  if ($insecure_authenticated_previous && $secure_authenticated) {
    drupal_set_message(t('You have changed the rules for authenticated users.  Currently logged in users will not have secure sessions until they log out and log-in again.'), 'error');
  }

  if ($insecure_authenticated_previous && $secure_authenticated || $secure_authenticated_previous && $insecure_authenticated) {
    drupal_set_message(t('You have changed the rules for authenticated users.  You may need to <a href="!status">change your settings.php file</a>.', array('!status' => url('admin/reports/status'))), 'error');
  }
  
  // The enabled state may change automatically (if the HTTPS test failed), so
  // notify the user of the selection.
  drupal_set_message($form['session443_enable'][$form_state['values']['session443_enable']]['#title']);
}

// vim: set filetype=php expandtab tabstop=2 shiftwidth=2 autoindent smartindent:
