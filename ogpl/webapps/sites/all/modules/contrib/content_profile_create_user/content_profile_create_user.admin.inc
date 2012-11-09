<?php

/**
 * @file admin.inc
 */

/**
 * Form for configuring module settings
 */
function content_profile_create_user_settings_form() {
  $form = array();
  
  // Batch Creation
  $form['batch_create'] = array(
    '#type' => 'fieldset',
    '#title' => t('Batch Create Users'),
    '#description' => t('Content Profile User Create can create a new user for each profile authored by the Anonymous user'),
  );
  
  $form['batch_create']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Create Users',
    '#submit' => array('content_profile_create_user_op_all'),
  );

  // Handle existing accounts
  $form['existing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Existing Account Handling'),
    '#description' => t('Specifiy how to handle existing user accounts'),
  );

  $form['existing'][CONTENT_PROFILE_CREATE_USER_MAP_EXISTING] = array(
    '#type' => 'checkbox',
    '#title' => t('Map nodes to existing users'),
    '#description' => t('When checked, an attempt will be made to assign the content profile to the existing user.'),
    '#default_value' => variable_get(CONTENT_PROFILE_CREATE_USER_MAP_EXISTING, CONTENT_PROFILE_CREATE_USER_MAP_EXISTING_DEFAULT),
  );
  
  // Message to send to newly created accounts
  $form['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('New Account Email Settings'),
    '#description' => t('Customize account creation e-mail message sent to new member accounts created from content profiles. Available variables are: !username, !uid, !site, !login_url, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri.'),
  );
  
  $form['email'][CONTENT_PROFILE_CREATE_USER_SEND_EMAIL] = array(
    '#title' => t('Send welcome email to created users'),
    '#type' => 'checkbox',
    '#default_value' => variable_get(CONTENT_PROFILE_CREATE_USER_SEND_EMAIL, CONTENT_PROFILE_CREATE_USER_SEND_EMAIL_DEFAULT),
  );
  
  $form['email'][CONTENT_PROFILE_CREATE_USER_EMAIL_SUBJECT] = array(
    '#title' => t('Email Subject'),
    '#type' => 'textfield',
    '#description' => t('Enter the subject of the email message'),
    '#default_value' => variable_get(CONTENT_PROFILE_CREATE_USER_EMAIL_SUBJECT, _content_profile_create_user_default_subject()),
  );
  
  $form['email'][CONTENT_PROFILE_CREATE_USER_EMAIL_BODY] = array(
    '#title' => t('Email Body'),
    '#type' => 'textarea',
    '#description' => t('Enter the body of the email message'),
    '#default_value' => variable_get(CONTENT_PROFILE_CREATE_USER_EMAIL_BODY, _content_profile_create_user_default_body()),
  );
  
  return system_settings_form($form);
}

/**
 * Submit function for content_profile_create_user_settings_form()
 */
function content_profile_create_user_settings_form_submit($form, &$form_state) {
  switch ($form_state['clicked_button']['#id']) {
    case 'edit-submit-1':
      variable_set(CONTENT_PROFILE_CREATE_USER_SEND_EMAIL, $form_state['values'][CONTENT_PROFILE_CREATE_USER_SEND_EMAIL]);
      variable_set(CONTENT_PROFILE_CREATE_USER_EMAIL_SUBJECT, $form_state['values'][CONTENT_PROFILE_CREATE_USER_EMAIL_SUBJECT]);
      variable_set(CONTENT_PROFILE_CREATE_USER_EMAIL_BODY, $form_state['values'][CONTENT_PROFILE_CREATE_USER_EMAIL_BODY]);
      break;
  }
}
