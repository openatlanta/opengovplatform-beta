<?php
// $Id: views.inc,v 1.1.4.8 2010/04/05 03:34:58 michellec Exp $

/**
 * @file
 * Handles integration with the views module.
 */

function advanced_profile_views_api() {
  $module_path = drupal_get_path('module', 'advanced_profile');
  return array('api' => 2.0, 'path' => $module_path . '/includes/views');
}

/**
 * Loads the included views
 *
 * This function is used instead of views ability to autodiscover a views
 * export .inc because this allows us to put each view in its own file.
 * Thanks to Moshe and OG for the code.
 */
function advanced_profile_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'advanced_profile') . '/includes/views', '.view');
  foreach ($files as $absolute => $file) {
    require $absolute;
    if (isset($view)) {
      $views[substr($file->name, 4)] = $view;
    }
  }
  return $views;
}

function advanced_profile_friends_gallery_header() {
  $view = views_get_current_view();
  $account_id = $view->argument['requester_id']->argument;
  $account = user_load($account_id);
  $number_of_friends = $view->total_rows;
  return format_plural($number_of_friends, '@name has 1 friend', '@name has @count friends', array('@name' => $account->name));
}