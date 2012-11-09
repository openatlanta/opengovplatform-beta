<?php

/**
 * @file
 * Builds placeholder replacement tokens for RPX data.
 */

/**
 * Implements hook_token_list().
 */
function rpx_ui_token_list($type = 'all') {
  if ($type == 'rpx' || $type == 'all') {
    $tokens['rpx']['provider-machinename'] = t('The Janrain Engage identity provider\'s internal (machine) name.');
    $tokens['rpx']['provider-title'] = t('The Janrain Engage identity provider\'s title.');
    $tokens['rpx']['id'] = t('The Janrain Engage identifier.');
    return $tokens;
  }
}

/**
 * Implements hook_token_values().
 */
function rpx_ui_token_values($type, $object = NULL, $options = array()) {
  if ($type == 'rpx') {
    $provider = $_SESSION['rpx_last_provider_info'];
    $tokens['provider-machinename'] = check_plain($provider['name']);
    $tokens['provider-title'] = check_plain($provider['title']);
    $tokens['id'] = $provider['id'];
    return $tokens;
  }
}
