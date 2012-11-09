<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function ogpl_community_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer forums
  $permissions['administer forums'] = array(
    'name' => 'administer forums',
    'roles' => array(),
  );

  // Exported permission: administer meta tags
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(),
  );

  // Exported permission: administer nodequeue
  $permissions['administer nodequeue'] = array(
    'name' => 'administer nodequeue',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: create community content
  $permissions['create community content'] = array(
    'name' => 'create community content',
    'roles' => array(),
  );

  // Exported permission: create community_featured content
  $permissions['create community_featured content'] = array(
    'name' => 'create community_featured content',
    'roles' => array(),
  );

  // Exported permission: create community_home content
  $permissions['create community_home content'] = array(
    'name' => 'create community_home content',
    'roles' => array(),
  );

  // Exported permission: create community_suggestion content
  $permissions['create community_suggestion content'] = array(
    'name' => 'create community_suggestion content',
    'roles' => array(
      '0' => 'Contributor',
    ),
  );

  // Exported permission: create forum topics
  $permissions['create forum topics'] = array(
    'name' => 'create forum topics',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: delete any community content
  $permissions['delete any community content'] = array(
    'name' => 'delete any community content',
    'roles' => array(),
  );

  // Exported permission: delete any community_featured content
  $permissions['delete any community_featured content'] = array(
    'name' => 'delete any community_featured content',
    'roles' => array(),
  );

  // Exported permission: delete any community_home content
  $permissions['delete any community_home content'] = array(
    'name' => 'delete any community_home content',
    'roles' => array(),
  );

  // Exported permission: delete any community_suggestion content
  $permissions['delete any community_suggestion content'] = array(
    'name' => 'delete any community_suggestion content',
    'roles' => array(),
  );

  // Exported permission: delete any forum topic
  $permissions['delete any forum topic'] = array(
    'name' => 'delete any forum topic',
    'roles' => array(),
  );

  // Exported permission: delete own community content
  $permissions['delete own community content'] = array(
    'name' => 'delete own community content',
    'roles' => array(),
  );

  // Exported permission: delete own community_featured content
  $permissions['delete own community_featured content'] = array(
    'name' => 'delete own community_featured content',
    'roles' => array(),
  );

  // Exported permission: delete own community_home content
  $permissions['delete own community_home content'] = array(
    'name' => 'delete own community_home content',
    'roles' => array(),
  );

  // Exported permission: delete own community_suggestion content
  $permissions['delete own community_suggestion content'] = array(
    'name' => 'delete own community_suggestion content',
    'roles' => array(),
  );

  // Exported permission: delete own forum topics
  $permissions['delete own forum topics'] = array(
    'name' => 'delete own forum topics',
    'roles' => array(),
  );

  // Exported permission: edit any blog content
  $permissions['edit any blog content'] = array(
    'name' => 'edit any blog content',
    'roles' => array(),
  );

  // Exported permission: edit any community content
  $permissions['edit any community content'] = array(
    'name' => 'edit any community content',
    'roles' => array(),
  );

  // Exported permission: edit any community_featured content
  $permissions['edit any community_featured content'] = array(
    'name' => 'edit any community_featured content',
    'roles' => array(),
  );

  // Exported permission: edit any community_home content
  $permissions['edit any community_home content'] = array(
    'name' => 'edit any community_home content',
    'roles' => array(),
  );

  // Exported permission: edit any community_suggestion content
  $permissions['edit any community_suggestion content'] = array(
    'name' => 'edit any community_suggestion content',
    'roles' => array(
      '0' => 'Contributor',
    ),
  );

  // Exported permission: edit any forum topic
  $permissions['edit any forum topic'] = array(
    'name' => 'edit any forum topic',
    'roles' => array(),
  );

  // Exported permission: edit field_com_home_column
  $permissions['edit field_com_home_column'] = array(
    'name' => 'edit field_com_home_column',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: edit field_community_featured
  $permissions['edit field_community_featured'] = array(
    'name' => 'edit field_community_featured',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: edit field_community_featured_image
  $permissions['edit field_community_featured_image'] = array(
    'name' => 'edit field_community_featured_image',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: edit field_community_featured_text
  $permissions['edit field_community_featured_text'] = array(
    'name' => 'edit field_community_featured_text',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: edit field_community_home
  $permissions['edit field_community_home'] = array(
    'name' => 'edit field_community_home',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
    ),
  );

  // Exported permission: edit field_community_home_image
  $permissions['edit field_community_home_image'] = array(
    'name' => 'edit field_community_home_image',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
    ),
  );

  // Exported permission: edit field_community_home_text
  $permissions['edit field_community_home_text'] = array(
    'name' => 'edit field_community_home_text',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
    ),
  );

  // Exported permission: edit field_community_home_title
  $permissions['edit field_community_home_title'] = array(
    'name' => 'edit field_community_home_title',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
    ),
  );

  // Exported permission: edit field_community_image
  $permissions['edit field_community_image'] = array(
    'name' => 'edit field_community_image',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
    ),
  );

  // Exported permission: edit field_community_internal_header
  $permissions['edit field_community_internal_header'] = array(
    'name' => 'edit field_community_internal_header',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: edit field_community_theme_color
  $permissions['edit field_community_theme_color'] = array(
    'name' => 'edit field_community_theme_color',
    'roles' => array(
      '0' => 'Administrator',
    ),
  );

  // Exported permission: edit field_community_thumb
  $permissions['edit field_community_thumb'] = array(
    'name' => 'edit field_community_thumb',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
    ),
  );

  // Exported permission: edit own blog content
  $permissions['edit own blog content'] = array(
    'name' => 'edit own blog content',
    'roles' => array(),
  );

  // Exported permission: edit own community content
  $permissions['edit own community content'] = array(
    'name' => 'edit own community content',
    'roles' => array(),
  );

  // Exported permission: edit own community_featured content
  $permissions['edit own community_featured content'] = array(
    'name' => 'edit own community_featured content',
    'roles' => array(),
  );

  // Exported permission: edit own community_home content
  $permissions['edit own community_home content'] = array(
    'name' => 'edit own community_home content',
    'roles' => array(),
  );

  // Exported permission: edit own community_suggestion content
  $permissions['edit own community_suggestion content'] = array(
    'name' => 'edit own community_suggestion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own forum topics
  $permissions['edit own forum topics'] = array(
    'name' => 'edit own forum topics',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: manipulate all queues
  $permissions['manipulate all queues'] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
      '2' => 'Moderator',
      '3' => 'PMO',
      '4' => 'Validator/Approver (Data Controller)',
    ),
  );

  // Exported permission: manipulate queues
  $permissions['manipulate queues'] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      '0' => 'Administrator',
      '1' => 'CMS Administrator',
      '2' => 'Moderator',
      '3' => 'PMO',
      '4' => 'Validator/Approver (Data Controller)',
    ),
  );

  // Exported permission: view field_com_home_column
  $permissions['view field_com_home_column'] = array(
    'name' => 'view field_com_home_column',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_featured
  $permissions['view field_community_featured'] = array(
    'name' => 'view field_community_featured',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_featured_image
  $permissions['view field_community_featured_image'] = array(
    'name' => 'view field_community_featured_image',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_featured_text
  $permissions['view field_community_featured_text'] = array(
    'name' => 'view field_community_featured_text',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_home
  $permissions['view field_community_home'] = array(
    'name' => 'view field_community_home',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_home_image
  $permissions['view field_community_home_image'] = array(
    'name' => 'view field_community_home_image',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_home_text
  $permissions['view field_community_home_text'] = array(
    'name' => 'view field_community_home_text',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_home_title
  $permissions['view field_community_home_title'] = array(
    'name' => 'view field_community_home_title',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_image
  $permissions['view field_community_image'] = array(
    'name' => 'view field_community_image',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_internal_header
  $permissions['view field_community_internal_header'] = array(
    'name' => 'view field_community_internal_header',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_theme_color
  $permissions['view field_community_theme_color'] = array(
    'name' => 'view field_community_theme_color',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: view field_community_thumb
  $permissions['view field_community_thumb'] = array(
    'name' => 'view field_community_thumb',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache community_landing
  $permissions['view imagecache community_landing'] = array(
    'name' => 'view imagecache community_landing',
    'roles' => array(
      '0' => 'Non Verified User',
      '1' => 'Portal User',
      '2' => 'anonymous user',
      '3' => 'authenticated user',
    ),
  );

  return $permissions;
}
