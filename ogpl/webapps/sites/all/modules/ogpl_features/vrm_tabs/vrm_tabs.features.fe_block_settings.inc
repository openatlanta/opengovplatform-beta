<?php

/**
 * Implementation of hook_default_fe_block_settings().
 */
function vrm_tabs_default_fe_block_settings() {
  $export = array();

  // dms
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'dms',
    'status' => '1',
    'weight' => '-108',
    'region' => 'content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '89',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'dms',
    'status' => '1',
    'weight' => '-109',
    'region' => 'content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'dms',
    'status' => '1',
    'weight' => '-94',
    'region' => 'content',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => ' <none>',
    'cache' => '-1',
  );

  $export['dms'] = $theme;

  // ogpl_css2
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '-78',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '-77',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '-76',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '-75',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => ' <none>',
    'cache' => '-1',
  );

  $export['ogpl_css2'] = $theme;

  // ogpl_css3
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-84',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-83',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-82',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '<none>',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-81',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => ' <none>',
    'cache' => '-1',
  );

  $export['ogpl_css3'] = $theme;

  // rootcandy
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '9',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'rootcandy',
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

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '12',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'rootcandy',
    'status' => 0,
    'weight' => '13',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $export['rootcandy'] = $theme;

  // rootcandy_dark
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '10',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'rootcandy_dark',
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

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '12',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'rootcandy_dark',
    'status' => 0,
    'weight' => '13',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $export['rootcandy_dark'] = $theme;

  // rootcandy_fixed
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '10',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'rootcandy_fixed',
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

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '12',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'rootcandy_fixed',
    'status' => 0,
    'weight' => '13',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $export['rootcandy_fixed'] = $theme;

  // cube
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '10',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'cube',
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

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '12',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'cube',
    'status' => 0,
    'weight' => '13',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $export['cube'] = $theme;

  // rubik
  $theme = array();

  $theme['quicktabs-vrm_admin_tabs'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '62',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_admin_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_admin_tabs_list',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '63',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_pmo_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_pmo_tabs_list',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '64',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
    'title' => '',
    'cache' => '-1',
  );

  $theme['quicktabs-vrm_poc_tabs_list'] = array(
    'module' => 'quicktabs',
    'delta' => 'vrm_poc_tabs_list',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '65',
    'region' => '',
    'custom' => '0',
    'throttle' => '0',
    'visibility' => '1',
    'pages' => 'vrm_dashboard',
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
