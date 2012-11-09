<?php
/**
 * @file
 * wizard file for ldaphelp module
 *
 */
function ldaphelp_wizard_form(&$form_state = NULL) {


  $inputs = array(
    'server' => array( 'fieldset' => 'server-settings', 'step' => 1 , 'copy_input' => TRUE, 'default_value' => '' ),
    'port' => array( 'fieldset' => 'server-settings', 'step' => 1 , 'copy_input' => TRUE , 'default_value' => ''),
    'tls' => array( 'fieldset' => 'server-settings', 'step' => 1 , 'copy_input' => TRUE , 'default_value' => 0),

    'basedn' => array( 'fieldset' => 'login-procedure', 'step' => 2, 'copy_input' => FALSE),
    'user_attr' => array( 'fieldset' => 'login-procedure' , 'step' => 2, 'copy_input' => TRUE, 'default_value' => ""),
    'mail_attr' => array( 'fieldset' => 'login-procedure' , 'step' => 2, 'copy_input' => TRUE, 'default_value' => ""),
    'sample_user' => array( 'fieldset' => 'login-procedure' , 'step' => 2, 'copy_input' => FALSE, 'default_value' => ""),
    'binddn' => array( 'fieldset' => 'advanced' , 'step' => 2 , 'copy_input' => TRUE  ),
    'bindpw' => array( 'fieldset' => 'advanced' , 'step' => 2,  'copy_input' => TRUE, 'unstored' => TRUE),
  );

  if (! $form_state['storage']['step'] ) {
    $form_state['storage']['step'] = 1;
  }
  elseif ($form_state['clicked_button']['#value'] && $form_state['clicked_button']['#value'] == $form_state['values']['submit_server_settings']) {
    $form_state['storage']['step'] = 2;
  }
  $step = $form_state['storage']['step'];


  switch ($step) {
    case 1:

    $instructions = t('<em>Note: This wizard does not populate the server configuration.  Its
      just for testing the settings</em>. The goal of this form is to help configure an LDAP server for the LDAP auth module.
    It will help test and/or determine some of the values needed on the ') .
    l(t("Add Server form"), 'admin/settings/ldapauth/add/ad') . ' ' .
    t('If you are unsure about your LDAP, a simple email to your LDAP administrator will save you some time
    and frustration.')
    .'<br/>'. t('Step 1 is to try to bind to the root of an LDAP server.');

    $ldapauth_admin_form = ldapauth_admin_form($form_state, NULL, NULL);
    $form['step'] = array('#type' => 'hidden', '#default_value' => $step);
    $form['server-settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('1. Server settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => $instructions,
    );

    foreach ($inputs as $fieldname => $conf) {
      if ($conf['step'] == 1 && $conf['copy_input']) {
      $form[$conf['fieldset']][$fieldname] = $ldapauth_admin_form[$conf['fieldset']][$fieldname];
      }
    };

    if (! $form_state['clicked_button']['#post']) { // initial state, set defaults
      foreach ($inputs as $fieldname => $conf) {
        if ($conf['step'] == 1 && $conf['default_value']) {
          $form[$conf['fieldset']][$fieldname]['#default_value'] = $conf['default_value'];
        }
      }
    }
    else { // post from same form, no longer use default values

      $form_state['values']['tls'] = ($form_state['values']['tls']) ? 1 : 0;

      foreach ($inputs as $fieldname => $conf) {
        if ($conf['step'] == 1 && ( ! $conf['unstored']) ) {
          $form_state['storage'][$fieldname] = $form_state['values'][$fieldname];
          $form[$conf['fieldset']][$fieldname]['#default_value'] = $form_state['values'][$fieldname];
        }
      }

      if (! form_get_errors()) {
        $bind_form_values_success = ldaphelp_bindtrials($form_state['values']);  // try binding to ldap.
      }
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Test'),
    );
    if ($bind_form_values_success) {
      $form['submit_server_settings'] = array(
        '#type' => 'submit',
        '#value' => t('Next Step'),
      );
    }

    break;

    case 2:

      $instructions = t('Step 2 is to test of assist in finding Base DNs, Username Attributes, and Email Attributes. Enter as much of the information
      you know below.') ."<br/>".
        "server: " . $form_state['storage']['server'] .", port: ". $form_state['storage']['port'] .", tls: ". $form_state['storage']['tls'];

      $form['step'] = array('#type' => 'hidden', '#default_value' => $step);
      $ldapauth_admin_form = ldapauth_admin_form($form_state, NULL, NULL);

      $form['login-procedure'] = array(
        '#type' => 'fieldset',
        '#title' => t('2. Login procedure'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#description' => $instructions,
        );

      $form['login-procedure']['basedn'] = array(
          '#type' => 'textfield',
          '#title' => t('Single Base DN to test'),
          '#description' => t('Enter one base DN.  For the final configuration,
            you may search within several base DNs.  But you can only test one at a time here.'),
          '#size' => 60,
          '#maxlength' => 255,
          '#required' => TRUE,
        );

      foreach ($inputs as $fieldname => $conf) {
        if ($conf['step'] == 2 && $conf['copy_input']) {
        $form[$conf['fieldset']][$fieldname] = $ldapauth_admin_form[$conf['fieldset']][$fieldname];
        }
      };

      $form['login-procedure']['sample_user'] = array(
        '#type' => 'textfield',
        '#title' => t('Sample username'),
        '#description' => t('sample username for testing (e.g. jdoe)'),
        '#size' => 20,
        '#maxlength' => 255,
        '#required' => TRUE,
      );

      $form['advanced'] = $ldapauth_admin_form['advanced'];
      $form['advanced']['#collapsed'] = FALSE;
      $form['advanced']['bindpw']['#type'] = 'textfield';

      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Test'),
      );


      if ($form_state['clicked_button']['#value'] == 'Next Step') {  // coming from step 1, do nothing.  perhaps clear defaults

        foreach ($inputs as $fieldname => $conf) {
          if ($conf['step'] == 2 && isset($conf['default_value'])) {
            $form[$conf['fieldset']][$fieldname]['#default_value'] = $conf['default_value'];
          }
        }
        $form['login-procedure']['basedn']['#default_value'] = 'dc='. str_replace('.', ',dc=', $form_state['storage']['server']);
      }
      else {
        // staying in step 2.  form is submitting to itself over and over.

        $values = $form_state['values'];
        foreach ($inputs as $fieldname => $conf) {
          if ($conf['step'] == 2) {
            if (! $conf['unstored']) {
              $form_state['storage'][$fieldname] = $values[$fieldname];
            }
            $form[$conf['fieldset']][$fieldname]['#default_value'] = $form_state['values'][$fieldname];
          }
        }

        if (form_get_errors()) {
          break;
        }
        $ldapserver = array();
        $mappings = array('server', 'port', 'tls', 'binddn', 'basedn', 'user_attr', 'mail_attr', 'bindpw');
        foreach ($mappings as $key) {
          if ($inputs[$key]['unstored']) {
            $ldapserver[$key]  = $values[$key];
          }
          else {
            $ldapserver[$key] = $form_state['storage'][$key];
          }
        }
        global $_ldapauth_ldap;
        $result = _ldaphelp_bind_test($ldapserver);

        if ($result['bind_success'] != 1) {
          drupal_set_message(t('Failed to bind to LDAP server'), 'error');
          return $form;
        }

        $sample_user = $form_state['storage']['sample_user'];
        $mail_attrs = array();
        $user_attrs = array();
        global $_ldaphelp_ldaps;
        foreach ($_ldaphelp_ldaps as $ldapid => $ldaptype) {
          $mail_attr = $ldaptype['fields']['login-procedure']['mail_attr'];
          $user_attr = $ldaptype['fields']['login-procedure']['user_attr'];
          if (! in_array($mail_attr, $mail_attrs)) {
            $mail_attrs[] = $mail_attr;
          }
          if (! in_array($user_attr, $user_attrs)) {
            $user_attrs[] = $user_attr;
            $large_filter .= "(". $user_attr ."=". $sample_user .")";
          }
        }


    // 1. do a search of the ldap (with or without credentials) and see if it works.

        $user_attr = $form_state['storage']['user_attr'];

        $filter = ($user_attr) ? "$user_attr=$sample_user" : "(|$large_filter)";

        $result = $_ldapauth_ldap->search($ldapserver['basedn'], $filter);
        $basedn_data = array();
        $basedn_data['result']['error'] = ldap_error($_ldapauth_ldap->connection);
        $basedn_data['result']['errno'] = ldap_errno($_ldapauth_ldap->connection);
        $search_description = 'search where base dn = <code>'. $ldapserver['basedn'] .'</code> and filter =<code>'.  $filter ."</code>";

        $basedn_data['result']['count'] = $result['count'];
        $basedn_data['result']['sample0'] = $result[0];
        $basedn_data['result']['dnufn'] = ldap_dn2ufn($base_dn);


        $suggestions[0] = "... your sample username is wrong.";
        if (! $form_state['storage']['binddn']) {
          $suggestions[1] = "... you must bind non anonymously.";
        }
        $suggestions[2] = "... " . t("your base DN does not have accounts within it.");
        $suggestions[4] = "... " . t("your base DN is incorrect.");
        $suggestions[3] = "... " . t("you are using the wrong user attribute or haven't picked one. <br/>Maybe one of the following: <code>") . join(", ", $user_attrs) ."</code>";

        if ($basedn_data['result']['errno'] != 0 ) {
          drupal_set_message(t('Error encountered in') . ' ' . $search_description .".<br/>error name: ". $basedn_data['result']['error'] .', error number: '.
          $basedn_data['result']['errno'] .".  Perhaps:". ldaphelp_suggest($suggestions, array(1, 4)), 'error');
          break;
        }

        if (! $basedn_data['result']['count']) {
          drupal_set_message(t('Could not find any results with') . ' ' . $search_description .".  Perhaps:". ldaphelp_suggest($suggestions, array(0, 1, 2, 3)), 'error');
          break;
        }

        if (! $basedn_data['result']['count'] > 1) {
          drupal_set_message(t('More than one result was found with') . ' ' . $search_description ."  Perhaps:". ldaphelp_suggest($suggestions, array(3)), 'error');
          break;
        }

        $ldap_object = $basedn_data['result']['sample0'];
        $message = t("Found 1 user object with") . " " . $search_description .".  Search should return exactly one object.";
        $mail_attrs = ($form_state['storage']['mail_attr']) ? array($form_state['storage']['mail_attr']) : $mail_attrs;

        foreach ($mail_attrs as $mail_attr) {
          if ($ldap_object[$mail_attr] ) {
            $message .= "<br/>" . t("Email Attribute of") ." <code>$mail_attr</code> ". t("is present with a value of") . ' ' . $ldap_object[$mail_attr][0] ;
          }
          elseif (! $form_state['storage']['mail_attr'] ) {
            $message .= "<br/>" . t("Email Attribute of") ." <code>$mail_attr</code> ". t("<strong>not present</strong>.") ;
          }
        }
        drupal_set_message($message);
      }
    break;
  }  // end switch step 1 or 2
  return $form;
}

function ldaphelp_suggest($all_suggestions, $suggestions) {
  $ul = "<ul>\r\n";
  foreach ($suggestions as $suggestion) {
    if ($all_suggestions[$suggestion]) {
      $ul .= "<li>". $all_suggestions[$suggestion] ."</li>";
    }
  }
  $ul .= "</ul>\r\n";
  return $ul;
}

function ldaphelp_bindtrials($values) {


  // first try values in form if port is entered:
  $bind_success = FALSE;
  $bind_form_values_success = FALSE;

  if ($values['port']) {
    $trial = array( 'server' => $values['server'], 'port' => $values['port'], 'tls' => $values['tls']);
    $trial['results']  = _ldaphelp_bind_test($trial);
    if ($trial['results']['bind_success'] == 1) {
      drupal_set_message(t("Successfully bound to port @port with tls=@tls on server @server", array('@port' => $values['port'], '@tls' => $values['tls'], '@server' => $values['server'])));
      $bind_success = TRUE;
      $bind_form_values_success = TRUE;
    }
    else {
      drupal_set_message(check_plain(ldaphelp_bind_trial_message($trial)), 'error');
    }
    $trials['form_values'] = $trial;
  }

  if ( (! $values['port']) || $trials['form_values']['results']['bind_success'] != 1) {
    $trials['tls'] = array('port' => 389, 'tls' => 1, 'server' => $values['server']);
    $trials['encrypted'] = array('port' => 636, 'tls' => 0, 'server' => $values['server']);
    $trials['odd'] = array('port' => 636, 'tls' => 1, 'server' => $values['server']);
    foreach ($trials as $name => $trial) {
      $trial['results'] = _ldaphelp_bind_test($trial);
      if ($trial['results']['bind_success'] == 1) {
        drupal_set_message(t("Successfully bound to port @port with tls=@tls on server @server", array('@port' => $trial['port'], '@tls' => $trial['tls'], '@server' => $trial['server'])));
        $bind_success = TRUE;
      }
      else {
        drupal_set_message(check_plain(ldaphelp_bind_trial_message($trial)), 'error');
      }
    }
  }

  if (! $bind_success ) {
    drupal_set_message(t('Could not bind to ldap to server @server', array('@server' =>  $values['server'])) .
      ' ' . t('Perhaps you have the wrong hostname, its on a nonstandard port, ' .
        'or it doesn not allow anononymous binds.  Try pinging the server.'), 'error');
  }

  if ( $bind_success && ! $bind_form_values_success ) {
    drupal_set_message(t('Was able to bind to server @server with some ' .
      'configurations, but not the data you entered.  If one of the ' .
      'successful attempts looks correct, enter it in the form to go to next step.',
      array('@server' => $values['server'])), 'warn');
  }
  return $bind_form_values_success;
}

function ldaphelp_wizard_form_validate($form, &$form_state) {
  $values = $form_state['values'];

  switch ($form_state['storage']['step']) {

    case 1:
      if ($values['port'] && !is_numeric($values['port'])) {
        form_set_error('port', t('The TCP/IP port must be an integer.'));
      }

    case 2:

      return;
      if (! trim($form_state['values']['import_data_serialized'])) {
        $haserror = TRUE;
      }
      else {
        $import_data = unserialize(trim($form_state['values']['import_data_serialized']));
        if (! is_array($import_data)) {
          $haserror = TRUE;
          }
        elseif ( ! ($import_data['ldaps'] ||  $import_data['admin_settings'])) {
          $haserror = TRUE;
        }
      }

      if ($haserror) {
        drupal_set_message( t("Input not valid.  Input should be a ' .
          'serialized array from the export function. It should look ' .
          'something like: ") .'<code>a:1:{s:5:"ldaps";a:1:{i:1;a:1</code>...',
          'error');
        $form_state['storage']['step'] =  $form_state['storage']['step'] - 1;
        return FALSE;
      }
      break;
  }


}
