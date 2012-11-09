<?php

/**
 * Implementation of hook_default_fe_block_settings().
 */
function catalog_home_tabs_default_fe_block_settings() {
  $export = array();

  // dms
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '105',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Most Popular Catalog',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '106',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Most Popular Catalog',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '107',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Most Popular Catalog',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '108',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Most Recent Catalog',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '109',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Most Recent Catalog',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '110',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Most Recent Catalog',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '-106',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '-16',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '-15',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['dms'] = $theme;

  // ogpl_css2
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '-123',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css2',
    'status' => '1',
    'weight' => '-70',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css2',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css2',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css2',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css2',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css2',
    'status' => '1',
    'weight' => '26',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '11',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '12',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['ogpl_css2'] = $theme;

  // ogpl_css3
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-125',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css3',
    'status' => '1',
    'weight' => '-70',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css3',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css3',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css3',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css3',
    'status' => '1',
    'weight' => '-71',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'ogpl_css3',
    'status' => '1',
    'weight' => '26',
    'region' => 'hidden_content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-27',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-26',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['ogpl_css3'] = $theme;

  // rootcandy
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-55',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-120',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-99',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-100',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-101',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-102',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-107',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '-83',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['rootcandy'] = $theme;

  // rootcandy_dark
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-55',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-102',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-98',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-99',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-100',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-101',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-107',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '-82',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['rootcandy_dark'] = $theme;

  // rootcandy_fixed
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-56',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-104',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-100',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-101',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-102',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-103',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-109',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '-84',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['rootcandy_fixed'] = $theme;

  // cube
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-55',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-105',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-101',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-102',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-103',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-104',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-112',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '-83',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['cube'] = $theme;

  // rubik
  $theme = array();

  $theme['aggregator-feed-1'] = array(
    'module' => 'aggregator',
    'delta' => 'feed-1',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-99',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '1',
  );

  $theme['block-popular_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_apps_catalog',
  );

  $theme['block-popular_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_dataset_catalog',
  );

  $theme['block-popular_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'popular_document_catalog',
  );

  $theme['block-recent_apps_catalog'] = array(
    'module' => 'block',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_apps_catalog',
  );

  $theme['block-recent_dataset_catalog'] = array(
    'module' => 'block',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_dataset_catalog',
  );

  $theme['block-recent_document_catalog'] = array(
    'module' => 'block',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-128',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
    'machine_name' => 'recent_document_catalog',
  );

  $theme['quicktabs-catalog_tab'] = array(
    'module' => 'quicktabs',
    'delta' => 'catalog_tab',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-126',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Popular_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Popular_Catalog-block_1',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-22',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-Most_Recent_Catalog-block_1'] = array(
    'module' => 'views',
    'delta' => 'Most_Recent_Catalog-block_1',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '-21',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['rubik'] = $theme;

  $theme_default = variable_get('theme_default', 'garland');
  $themes = list_themes();
  foreach ($export as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export[$theme_key]);
    }
  }
  return $export;
}
