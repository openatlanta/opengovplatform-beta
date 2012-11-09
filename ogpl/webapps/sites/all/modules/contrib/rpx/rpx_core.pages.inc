<?php

/**
 * @file
 * User page callbacks for the rpx_core module.
 */

/**
 * The Engage Sign-in transaction end point. Engage redirects the user to this
 * URL upon successful authentication by a 3rd party.
 *
 * See @link https://rpxnow.com/docs#flow Janrain Engage Flow @endlink for a
 * detailed decription of this process.
 */
function rpx_token_handler() {
  global $user;

  // Are we completing an Engage sign-in transaction?
  $token = isset($_REQUEST['token']) ? $_REQUEST['token'] : '';
  $add_to_account = isset($_REQUEST['add_to_account']) ? TRUE : FALSE;

  if ($token) {
    $rpx_data = RPX::auth_info($token, variable_get('rpx_apikey', ''), variable_get('rpx_extended_authinfo', FALSE));
    if (!$rpx_data) {
      drupal_goto();
    }
    // auth_info() stat should be ok.
    if ($rpx_data['stat'] != 'ok') {
      drupal_set_message(t('We were unable to complete your request.'), 'error');
      watchdog('rpx_core', 'Failed to obtain a 3rd party identifier for user ID %id: auth_info() returned error: %err', array('%id' => $user->uid, '%err' => $rpx_data['err']['msg']), WATCHDOG_ERROR);
      drupal_goto();
    }

    rpx_core_save_rpx_session($rpx_data);

    // Possible leftover from previous attempt to sign in.
    if (isset($_SESSION['rpx_signup_failed'])) {
      unset($_SESSION['rpx_signup_failed']);
    }

    $rpx_id = $rpx_data['profile']['identifier'];
    $provider_title = $rpx_data['profile']['providerName'];

    // Save provider info (for token replacement and account linking).
    $_SESSION['rpx_last_provider_info'] = array(
      'name' => _rpx_get_provider_machine_name($provider_title),
      'title' => $provider_title,
      'id' => $rpx_id,
    );

    // Are we adding a new identity to an existing account?
    if ($add_to_account) {
      if (user_is_logged_in()) {
        // the identifier returned by auth_info() should not be already
        // mapped to an existing account
        if (user_get_authmaps($rpx_id)) {
          drupal_set_message(t('We were unable to complete your request.  That account ID is already linked to a user on our site.'), 'error');
        }
        else {
          // Can't use user_set_authmaps() here, since it doesn't support
          // multiple authnames per user via same module
          db_query("INSERT INTO {authmap} (uid, authname, module) VALUES (%d, '%s', 'rpx_core')", $user->uid, $rpx_id);
          $aid = db_last_insert_id('authmap', 'aid');

          // rpx_linked_account table is created by the rpx_ui module.
          if (module_exists('rpx_ui')) {
            db_query("INSERT INTO {rpx_linked_account} (aid, uid, provider_name, provider_title) VALUES (%d, %d, '%s', '%s')", $aid, $user->uid, $_SESSION['rpx_last_provider_info']['name'], $_SESSION['rpx_last_provider_info']['title']);
          }

          drupal_set_message(t('We have successfully linked your %provider account.', array('%provider' => $provider_title)), 'status');

          // Let other modules (e.g. rpx_rules) know that a linked account has been
          // added.
          $account = array(
            'user' => $user,
            'id' => $rpx_id,
            'provider_machinename' => $_SESSION['rpx_last_provider_info']['name'],
            'provider_title' => $_SESSION['rpx_last_provider_info']['title'],
          );
          module_invoke_all('rpx_linked_account', 'added', $account);
          _rpx_import_user_data($user);
          _rpx_update_engage_mapping($user->uid);
        }
        rpx_core_delete_rpx_session();
      }
      else {
        drupal_set_message(t('Please sign in before linking additional accounts.'), 'error');
        rpx_core_delete_rpx_session();
        return MENU_ACCESS_DENIED;
      }
    }

    $account = user_external_load($rpx_id);

    // Is this a registered user?
    if (isset($account->uid)) {
      if (!variable_get('user_email_verification', TRUE) ||
          $account->login ||
          !empty($account->rpx_data['profile']['verifiedEmail']) &&
          strtolower($account->rpx_data['profile']['verifiedEmail']) == strtolower($account->mail)) {
        // IF settings do not require email verification
        // OR
        // it's not the first login for the user (which means the email has
        // already been verified)
        // OR
        // they are using an email the ID provider has already verified
        //
        // then we can skip the email verification process

        _rpx_import_user_data($account);
        _rpx_update_engage_mapping($account->uid);
        rpx_core_delete_rpx_session();
        user_external_login($account);
      }
      else {
        rpx_core_delete_rpx_session();
        drupal_set_message(t('You must validate your email address for this account before logging in with it.'), 'error');
      }
      drupal_goto();
    }
    // New user.
    else {
      // Check that users are allowed to register on their own.
      if (variable_get('user_register', 1)) {
        if (!variable_get('rpx_force_registration_form', FALSE)) {
          $form_state['values'] = array();
          $form_state['values']['op'] = t('Create new account');
          $form_state['values']['name'] = $rpx_data['profile']['email'];
          $form_state['values']['mail'] = $rpx_data['profile']['email'];
          $password = user_password();
          $form_state['values']['pass']['pass1'] = $password;
          $form_state['values']['pass']['pass2'] = $password;
          drupal_execute('user_register', $form_state);
          // See if the user was successfully registered.
          if (!empty($form_state['user'])) {
            // Let other modules (e.g. rpx_rules) know that a linked account has been
            // added.
            $account = array(
              'user' => $user,
              'id' => $rpx_id,
              'provider_machinename' => $_SESSION['rpx_last_provider_info']['name'],
              'provider_title' => $_SESSION['rpx_last_provider_info']['title'],
            );
            module_invoke_all('rpx_linked_account', 'added', $account);
            // Nothing more to do.
            drupal_goto();
          }
          // get the error messages and clear the messages queue
          $messages = drupal_get_messages('error');

          if (empty($form_state['values']['mail'])) {
            // If the identity provider did not provide an email address, ask
            // the user to complete (and submit) the form manually instead of
            // showing the error messages about the missing values generated by
            // FAPI.
            drupal_set_message(t('Although we have verified your account, @provider did not provide us with your e-mail address.  Please enter one below to complete your registration.  (If you\'ve previously registered with us, please <a href="@login">log in</a> and add your @provider account under "Linked accounts.")', array('@provider' => $_SESSION['rpx_last_provider_info']['title'], '@login' => url('user/login'))), 'warning');
          }
          else {
            drupal_set_message(t('Although we have verified your account, registration using the information provided by @provider failed due to the reasons listed below. Please complete the registration by filling out the form below. (If you\'ve previously registered with us, please <a href="@login">log in</a> and add your @provider account under "Linked accounts.")', array('@provider' => $_SESSION['rpx_last_provider_info']['title'], '@login' => url('user/login'))), 'warning');
            // Append form validation errors below the above warning.
            foreach ($messages['error'] as $message) {
              drupal_set_message($message, 'error');
            }
          }
        }
        else {
          drupal_set_message(t('Please complete the registration by filling out the form below.  (If you\'ve previously registered with us, please <a href="@login">log in</a> and add your @provider account under "Linked accounts.")', array('@provider' => $_SESSION['rpx_last_provider_info']['title'], '@login' => url('user/login'))), 'warning');
        }

        // Redirect to the normal registration page and prefill with the values
        // we received from Engage (@see rpx_core_form_alter()).
        // Signal our registration form alter function that automatic user
        // registration failed and we want to keep the captcha (if any) this
        // time around.
        $_SESSION['rpx_signup_failed'] = TRUE;
        $dest = drupal_get_destination();
        unset($_REQUEST['destination']);
        drupal_goto('user/register', $dest);
      }
      else {
        drupal_set_message(t('Only site administrators can create new user accounts.'), 'error');
        rpx_core_delete_rpx_session();
        drupal_goto();
      }
    }
  }
  else {
    drupal_set_message(t('You need a token to be here!'), 'error');
    return MENU_ACCESS_DENIED;
  }
}

/**
 * Menu callback; confirm email for Engage registrations that require it.
 *
 * @see user_pass_reset()
 * @see rpx_core_mail()
 * @see _rpx_mail_text()
 */
function rpx_email_confirm(&$form_state, $uid, $timestamp, $hashed_pass) {
  global $user;

  // Make sure that a user isn't already logged in.
  if ($user->uid) {
    // The user is already logged in
    if ($user->uid == $uid) {
      drupal_set_message(t('You have already used this email confirmation link and you are already logged in.'));
      drupal_goto();
    }
    // A different user is already logged in on the computer.
    else {
      $reset_link_account = user_load($uid);
      if (!empty($reset_link_account)) {
        drupal_set_message(t('Another user (%other_user) is already logged into the site on this computer, but you tried to use a one-time link for user %resetting_user. Please <a href="!logout">logout</a> and try using the link again.',
          array('%other_user' => $user->name, '%resetting_user' => $reset_link_account->name, '!logout' => url('logout'))));
      } else {
        // Invalid one-time link specifies an unknown user.
        drupal_set_message(t('The one-time login link you clicked is invalid.'));
      }
    }
    drupal_goto();
  }
  else {
    // Time out, in seconds, until login URL expires. 24 hours = 86400 seconds.
    $timeout = 86400;
    $current = time();
    // Some redundant checks for extra security?
    if ($timestamp < $current && $account = user_load(array('uid' => $uid, 'status' => 1)) ) {
      // Deny one-time login to blocked accounts.
      if (drupal_is_denied('user', $account->name) || drupal_is_denied('mail', $account->mail)) {
        drupal_set_message(t('You have tried to use a one-time login for an account which has been blocked.'), 'error');
        drupal_goto();
      }

      // No time out for first time login.
      if ($account->login && $current - $timestamp > $timeout) {
        drupal_set_message(t('You have tried to use a one-time login link that has expired. Please request a new one using the form below.'));
        drupal_goto('user/password');
      }
      else if ($account->uid && $timestamp > $account->login && $timestamp < $current && $hashed_pass == user_pass_rehash($account->pass, $timestamp, $account->login)) {
        $form['message'] = array('#value' => t('<p>This is a one-time login for %user_name and will expire on %expiration_date.</p><p>Click on this button to login to the site. You can change your password if you like, but once you login for the first time, you\'ll be able to login using your linked account(s).</p>', array('%user_name' => $account->name, '%expiration_date' => format_date($timestamp + $timeout))));
        $form['help'] = array('#value' => '<p>'. t('This login can be used only once.') .'</p>');
        $form['submit'] = array('#type' => 'submit', '#value' => t('Log in'));
        $form['#action'] = url("user/reset/$uid/$timestamp/$hashed_pass/login");
        return $form;
      }
      else {
        drupal_set_message(t('You have tried to use a one-time login link which has either been used or is no longer valid. Please request a new one using the form below.'));
        drupal_goto('user/password');
      }
    }
    else {
      // Deny access, no more clues.
      // Everything will be in the watchdog's URL for the administrator to check.
      drupal_access_denied();
    }
  }
}
