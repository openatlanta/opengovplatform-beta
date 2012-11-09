<?php

/**
 * Implementation of hook_default_fe_block_settings().
 */
function rotating_panel_half_default_fe_block_settings() {
  $export = array();

  // dms
  $theme = array();

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
    'theme' => 'dms',
    'status' => 0,
    'weight' => '5',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
    'theme' => 'ogpl_css2',
    'status' => 0,
    'weight' => '20',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
    'theme' => 'ogpl_css3',
    'status' => 0,
    'weight' => '-128',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
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

  $theme['views-Rotating_Panel_Half-block_1'] = array(
    'module' => 'views',
    'delta' => 'Rotating_Panel_Half-block_1',
    'theme' => 'rubik',
    'status' => 0,
    'weight' => '25',
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
