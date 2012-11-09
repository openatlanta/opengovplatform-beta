<?php

/**
 * @file
 *   Admin callbacks for the Email Logging and Alerts module.
 */

/**
 * Returns admin settings form.
 */
function web_myservice_alert_admin_settings() {
  $severity_levels = watchdog_severity_levels();
  $form['service_alert'] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Serive Alert Email and SMS Settings'),
    '#description'    => t('Enter an email address and SMS nos'),
    '#collapsible'    => TRUE,
    '#collapsed'      => FALSE,
  );
  $form['service_alert']['service_alert_email'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Email Address'),
      '#default_value'  => variable_get('service_alert_email', variable_get('site_mail', 'nic-ndsap@nic.in')),
      '#description'    => t('Insert comma separated value of email addresses'),
  );
  $form['service_alert']['service_alert_sms'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Mobie Nos'),
      '#default_value'  => variable_get('service_alert_sms', NULL),
      '#description'    => t('Insert comma separated value of mobile nos'),
  );
  $form['#submit'][] = 'web_myservice_alert_admin_settings_submit';
  
  $form = system_settings_form($form);
  return $form;
}

/**
 * Saves additional debug info from submitted admin settings form.
 */
function web_myservice_alert_admin_settings_submit($form, &$form_state) {
}