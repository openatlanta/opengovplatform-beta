<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function footermenus_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-footermenu:sitemap
  $menu_links['menu-footermenu:sitemap'] = array(
    'menu_name' => 'menu-footermenu',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Site Map',
    'options' => array(
      'attributes' => array(
        'title' => 'Sitemap',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '1',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Site Map');


  return $menu_links;
}
