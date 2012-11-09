<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function content_profile_create_user_test_helper_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function content_profile_create_user_test_helper_node_info() {
  $items = array(
    'test_profile_a' => array(
      'name' => t('Test Profile A'),
      'module' => 'features',
      'description' => t('This is a content type for testing Content Profile Create User.  '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'test_profile_b' => array(
      'name' => t('Test Profile B'),
      'module' => 'features',
      'description' => t('This is a content type for testing Content Profile Create User.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
