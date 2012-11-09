<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function ogpl_community_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-menulinks:communities
  $menu_links['menu-menulinks:communities'] = array(
    'menu_name' => 'menu-menulinks',
    'link_path' => 'communities',
    'router_path' => 'communities',
    'link_title' => 'Communities',
    'options' => array(
      'attributes' => array(
        'title' => 'Communities',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Communities');


  return $menu_links;
}
