<?php
// $Id: advanced_profile.admin.inc,v 1.1.2.5 2010/10/04 19:12:10 michellec Exp $

/**
 * @file
 * Administrative page callback for the Advanced Profile Kit module.
 */

function advanced_profile_settings_page() {
  $form['advanced_profile_redirect_from_node'] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect from profile node to user page'),
    '#default_value' => variable_get('advanced_profile_redirect_from_node', TRUE),
    '#description' => t('If checked, attempting to go to the profile node will redirect you to the user page. This only affects the full node page and not viewing the node elsewhere. This specifically works with the uprofile node type that ships with APK and will not work if you are using a different node type.'),
  );

  $form['advanced_profile_tab_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Text of user page view tab'),
    '#size' => 20,
    '#default_value' => variable_get('advanced_profile_tab_title', "View"),
    '#description' => t('Text to use for the tab on the user view page. By default, this is "View" but it can be changed to something more user friendly like "Profile". Whatever is entered here will be translated before use. Note that you must clear the cache before the change will take effect.'),
  );

  // *** Profile visitors settings ****
  $form['advanced_profile_visitors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile visitors'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Limit.
  $form['advanced_profile_visitors']['advanced_profile_visitors_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of entries'),
    '#size' => 5,
    '#default_value' => variable_get('advanced_profile_visitors_limit', 5),
    '#description' => t('Number of visitor entries to display.'),
  );


  // Distinct visitors.
  $form['advanced_profile_visitors']['advanced_profile_visitors_distinct'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show only the last visit from each user'),
    '#default_value' => variable_get('advanced_profile_visitors_distinct', FALSE),
  );

  // Interval granularity.
  $form['advanced_profile_visitors']['advanced_profile_visitors_interval_granularity'] = array(
    '#type' => 'textfield',
    '#title' => t('Granularity of time ago'),
    '#size' => 5,
    '#default_value' => variable_get('advanced_profile_visitors_interval_granularity', 2),
    '#description' => t('1 gives you "1 hour ago". 2 gives you "1 hour 4 minutes ago". 3 gives you "1 hour 4 minutes and 2 seconds ago"'),
  );

  // Role exclusion.
  $roles_options = user_roles(TRUE);
  $form['advanced_profile_visitors']['advanced_profile_visitors_excluded_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles to exclude'),
    '#options' => $roles_options,
    '#default_value' => variable_get('advanced_profile_visitors_excluded_roles', array()),
    '#description' => t('Check roles to exclude users in those roles from the listing. Warning: using this on highly populated roles could cause performance issues. It\'s meant for admins.')
  );

  // Send our form to Drupal to make a settings page.
  return system_settings_form($form);
}

function advanced_profile_settings_validate($form, &$form_state) {
  form_set_value($form['page_manager_user_view_disabled']['#value'], !$form['page_manager_user_view_disabled']['#value'], $form_state);
}

