<?php

/**
 * Implementation of hook_strongarm().
 */
function rotating_panel_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_rotating_panel';
  $strongarm->value = '0';
  $export['comment_anonymous_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_rotating_panel';
  $strongarm->value = '3';
  $export['comment_controls_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_rotating_panel';
  $strongarm->value = '4';
  $export['comment_default_mode_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_rotating_panel';
  $strongarm->value = '1';
  $export['comment_default_order_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_rotating_panel';
  $strongarm->value = '50';
  $export['comment_default_per_page_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_rotating_panel';
  $strongarm->value = '0';
  $export['comment_form_location_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_rotating_panel';
  $strongarm->value = '1';
  $export['comment_preview_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_rotating_panel';
  $strongarm->value = '0';
  $export['comment_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_rotating_panel';
  $strongarm->value = '1';
  $export['comment_subject_field_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_rotating_panel';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '3',
    'revision_information' => '6',
    'author' => '5',
    'options' => '7',
    'comment_settings' => '9',
    'menu' => '2',
    'path' => '8',
    'custom_breadcrumbs' => '16',
    'workflow' => '4',
    'print' => '15',
    'nodewords' => '10',
  );
  $export['content_extra_weights_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_rotating_panel';
  $strongarm->value = '0';
  $export['language_content_type_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_rotating_panel';
  $strongarm->value = array(
    0 => 'revision',
    1 => 'revision_moderation',
  );
  $export['node_options_rotating_panel'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_rotating_panel';
  $strongarm->value = '1';
  $export['upload_rotating_panel'] = $strongarm;

  return $export;
}
