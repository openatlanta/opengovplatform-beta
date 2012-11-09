<?php

/**
 * Implementation of hook_strongarm().
 */
function role_management_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_create_contributor';
  $strongarm->value = '0';
  $export['comment_anonymous_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_create_contributor';
  $strongarm->value = '3';
  $export['comment_controls_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_create_contributor';
  $strongarm->value = '2';
  $export['comment_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_create_contributor';
  $strongarm->value = '4';
  $export['comment_default_mode_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_create_contributor';
  $strongarm->value = '1';
  $export['comment_default_order_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_create_contributor';
  $strongarm->value = '50';
  $export['comment_default_per_page_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_create_contributor';
  $strongarm->value = '0';
  $export['comment_form_location_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_create_contributor';
  $strongarm->value = '1';
  $export['comment_preview_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_create_contributor';
  $strongarm->value = '1';
  $export['comment_subject_field_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_create_contributor';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '7',
    'author' => '6',
    'options' => '8',
    'comment_settings' => '12',
    'menu' => '3',
    'path' => '11',
    'custom_breadcrumbs' => '10',
    'workflow' => '5',
    'print' => '9',
    'nodewords' => '4',
  );
  $export['content_extra_weights_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_create_contributor';
  $strongarm->value = '0';
  $export['language_content_type_create_contributor'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_create_contributor';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_create_contributor'] = $strongarm;

  return $export;
}
