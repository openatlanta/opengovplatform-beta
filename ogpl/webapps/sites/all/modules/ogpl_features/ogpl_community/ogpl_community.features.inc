<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ogpl_community_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
  elseif ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function ogpl_community_imagecache_default_presets() {
  $items = array(
    'community_landing' => array(
      'presetname' => 'community_landing',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_resize',
          'data' => array(
            'width' => '290',
            'height' => '180',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function ogpl_community_node_info() {
  $items = array(
    'community' => array(
      'name' => t('Community'),
      'module' => 'features',
      'description' => t('Add community'),
      'has_title' => '1',
      'title_label' => t('Community Name'),
      'has_body' => '1',
      'body_label' => t('Community Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'community_featured' => array(
      'name' => t('Community Featured'),
      'module' => 'features',
      'description' => t('Community Featured Text and Image. Can be used as slide show'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'community_home' => array(
      'name' => t('Community Home'),
      'module' => 'features',
      'description' => t('Add Text to create the Community Home design'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'community_suggestion' => array(
      'name' => t('Community Suggestion'),
      'module' => 'features',
      'description' => t('Used to get suggestion about the community'),
      'has_title' => '1',
      'title_label' => t('Community Name'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
