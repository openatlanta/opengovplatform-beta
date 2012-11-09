<?php
// $Id: profile_visitors.inc,v 1.1.2.4 2009/05/04 01:59:07 michellec Exp $

/**
 * @file
 * Provides a CTools content type containing visitors to the profile page.
 */


/**
 * Callback function to supply a list of content types.
 */
function advanced_profile_profile_visitors_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('Profile visitors'),
    'icon' => 'icon_user.png',
    'description' => t('List of visitors to a profile page.'),
    'required context' => new ctools_context_required(t('User'), 'user'),
    'category' => t('Advanced Profile Kit'),
  );
}

/**
 * Output function for the 'profile visitors' content type.
 */
function advanced_profile_profile_visitors_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? drupal_clone($context->data) : NULL;
  $block = new stdClass();
  $block->title = "Profile visitors";

  if ($account) {
    $block->content = theme('advanced_profile_visitors', $account);
  }
  else {
    $block->content = t("User information not available");
  }

  return $block;
}

function advanced_profile_profile_visitors_content_type_edit_form(&$form, &$form_state) {
}

function advanced_profile_profile_visitors_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" profile visitors', array('@s' => $context->identifier));
}
