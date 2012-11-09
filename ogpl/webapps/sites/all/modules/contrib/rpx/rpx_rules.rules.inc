<?php

/**
 * @file
 * Hooks and callback functions for rules.module integration.
 */

/**
 * Implements hook_rules_action_info().
 *
 * @ingroup rules
 */
function rpx_rules_rules_action_info() {
  return array(
    'rpx_action_launch_social' => array(
      'label' => t('Launch social sharing widget'),
      'module' => 'Janrain Engage',
      'eval input' => array('label', 'comment', 'linktext', 'link', 'title', 'summary'),
    ),
  );
}

/**
 * Rules action form configuration - allow sharing widget options to be set.
 */
function rpx_action_launch_social_form($settings = array(), &$form) {
  $form['settings']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => isset($settings['label']) ? $settings['label'] : '',
    '#description' => t('This is a short string that appears at the top of the social sharing widget that is presented to the user. Required.'),
  );
  $form['settings']['comment'] = array(
    '#type' => 'textfield',
    '#title' => t('Comment'),
    '#default_value' => isset($settings['comment']) ? $settings['comment'] : '',
    '#description' => t('Any textual content the user made about this action. If this is provided, it overrides the link text for Yahoo!, Myspace, LinkedIn and Twitter. It is displayed in an independent location on Facebook.'),
  );
  $form['settings']['linktext'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text'),
    '#default_value' => isset($settings['linktext']) ? $settings['linktext'] : '',
    '#description' => t('A description of the action the user is sharing, as it should be displayed on the sites the user chooses to share it with. Required.'),
  );
  $form['settings']['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => isset($settings['link']) ? $settings['link'] : '',
    '#description' => t('Where people who see the user\'s update on social sites can visit for further information. Make sure this is a valid link, or the social widget will fail to launch.'),
  );
  $form['settings']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($settings['title']) ? $settings['title'] : '',
    '#description' => t('An optional title for this activity. This information is displayed by Yahoo!, Facebook and LinkedIn.'),
  );
  $form['settings']['summary'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#default_value' => isset($settings['summary']) ? $settings['summary'] : '',
    '#description' => t('An optional description of the activity. This information is displayed by Facebook and LinkedIn. '),
  );
}

/**
 * Rules action form configuration - validate user-provided sharing widget
 * options.
 */
function rpx_action_launch_social_validate($form, $form_state) {
  $values = $form_state['values']['settings'];

  if (!$values['label']) {
    form_set_error('settings][label', 'A label is required.');
  }
  if (!$values['linktext']) {
    form_set_error('settings][linktext', 'Link description is required.');
  }
  if (!$values['link']) {
    form_set_error('settings][link', 'A valid link is required.');
  }
}

/**
 * Rules action: arrange for the social sharing widget to launch on next page
 * load.
 */
function rpx_action_launch_social($social_args) {
  $_SESSION['rpx_action_launch_social_data'] = $social_args;
}

/**
 * Implementation of hook_rules_data_type_info().
 */
function rpx_rules_rules_data_type_info() {
  return array(
    'rpx' => array(
      'label' => t('rpx'),
      'class' => 'rules_data_type',
      'identifiable' => FALSE,
    ),
  );
}

/**
 * Implements hook_rules_event_info().
 *
 * @ingroup rules
 */
function rpx_rules_rules_event_info() {
  $account_arguments = array(
    'rpx' => array('type' => 'rpx', 'label' => t('linked account data')),
    'user' => array('type' => 'user', 'label' => t('linked account owner')),
  );

  return array(
    'rpx_account_add' => array(
      'label'  => t('Linked account was added'),
      'module' => t('Janrain Engage'),
      'arguments'   => $account_arguments,
    ),
    'rpx_account_delete' => array(
      'label'  => t('Linked account was deleted'),
      'module' => t('Janrain Engage'),
      'arguments'   => $account_arguments,
    ),
    'rpx_social_cookie_set_node' => array(
      'label'  => t('Social sharing cookie was set for shared content'),
      'module' => t('Janrain Engage'),
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('shared content')),
      ),
    ),
    'rpx_social_cookie_set_comment' => array(
      'label'  => t('Social sharing cookie was set for shared comment'),
      'module' => t('Janrain Engage'),
      'arguments' => array(
        'comment' => array('type' => 'comment', 'label' => t('shared comment')),
      ),
    ),
    'rpx_social_cookie_set_other' => array(
      'label'  => t('Social sharing cookie was set for other information'),
      'module' => t('Janrain Engage'),
      'arguments' => array(),
    ),
  );
}
