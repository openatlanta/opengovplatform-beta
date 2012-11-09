<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function ogpl_community_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_community_header
  $groups['community-group_community_header'] = array(
    'group_type' => 'standard',
    'type_name' => 'community',
    'group_name' => 'group_community_header',
    'label' => 'Community Header',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_community_image',
      '1' => 'field_community_thumb',
      '2' => 'field_community_featured',
      '3' => 'field_community_internal_header',
    ),
  );

  // Exported group: group_community_home
  $groups['community-group_community_home'] = array(
    'group_type' => 'standard',
    'type_name' => 'community',
    'group_name' => 'group_community_home',
    'label' => 'Community Home',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-1',
    'fields' => array(
      '0' => 'field_community_theme_color',
      '1' => 'field_com_home_column',
      '2' => 'field_community_home',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Community Header');
  t('Community Home');

  return $groups;
}
