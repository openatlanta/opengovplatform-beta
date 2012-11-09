<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function role_management_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function role_management_node_info() {
  $items = array(
    'create_contributor' => array(
      'name' => t('Contributor'),
      'module' => 'features',
      'description' => t('Create Contributor User'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
