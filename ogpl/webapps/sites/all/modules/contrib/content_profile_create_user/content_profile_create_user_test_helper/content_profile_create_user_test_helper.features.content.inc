<?php

/**
 * Implementation of hook_content_default_fields().
 */
function content_profile_create_user_test_helper_content_default_fields() {
  $fields = array();

  // Exported field: field_a_email
  $fields['test_profile_a-field_a_email'] = array(
    'field_name' => 'field_a_email',
    'type_name' => 'test_profile_a',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'email',
    'required' => '0',
    'multiple' => '0',
    'module' => 'email',
    'active' => '1',
    'widget' => array(
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'email' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Email Address',
      'weight' => '31',
      'description' => '',
      'type' => 'email_textfield',
      'module' => 'email',
    ),
  );

  // Exported field: field_b_email
  $fields['test_profile_b-field_b_email'] = array(
    'field_name' => 'field_b_email',
    'type_name' => 'test_profile_b',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'email',
    'required' => '0',
    'multiple' => '0',
    'module' => 'email',
    'active' => '1',
    'widget' => array(
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'email' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Email Address',
      'weight' => '31',
      'description' => '',
      'type' => 'email_textfield',
      'module' => 'email',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Email Address');

  return $fields;
}
