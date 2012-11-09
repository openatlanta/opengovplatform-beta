<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function role_management_user_default_permissions() {
  $permissions = array();

  // Exported permission: create create_contributor content
  $permissions['create create_contributor content'] = array(
    'name' => 'create create_contributor content',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: delete any create_contributor content
  $permissions['delete any create_contributor content'] = array(
    'name' => 'delete any create_contributor content',
    'roles' => array(),
  );

  // Exported permission: delete own create_contributor content
  $permissions['delete own create_contributor content'] = array(
    'name' => 'delete own create_contributor content',
    'roles' => array(),
  );

  // Exported permission: edit any create_contributor content
  $permissions['edit any create_contributor content'] = array(
    'name' => 'edit any create_contributor content',
    'roles' => array(),
  );

  // Exported permission: edit field_cc_designation
  $permissions['edit field_cc_designation'] = array(
    'name' => 'edit field_cc_designation',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit field_cc_email
  $permissions['edit field_cc_email'] = array(
    'name' => 'edit field_cc_email',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit field_cc_first_name
  $permissions['edit field_cc_first_name'] = array(
    'name' => 'edit field_cc_first_name',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit field_cc_last_name
  $permissions['edit field_cc_last_name'] = array(
    'name' => 'edit field_cc_last_name',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit field_cc_mobile
  $permissions['edit field_cc_mobile'] = array(
    'name' => 'edit field_cc_mobile',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit field_cc_phone
  $permissions['edit field_cc_phone'] = array(
    'name' => 'edit field_cc_phone',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit field_cc_user_type
  $permissions['edit field_cc_user_type'] = array(
    'name' => 'edit field_cc_user_type',
    'roles' => array(
      '0' => 'Validator/Approver',
    ),
  );

  // Exported permission: edit own create_contributor content
  $permissions['edit own create_contributor content'] = array(
    'name' => 'edit own create_contributor content',
    'roles' => array(),
  );

  // Exported permission: view field_cc_designation
  $permissions['view field_cc_designation'] = array(
    'name' => 'view field_cc_designation',
    'roles' => array(),
  );

  // Exported permission: view field_cc_email
  $permissions['view field_cc_email'] = array(
    'name' => 'view field_cc_email',
    'roles' => array(),
  );

  // Exported permission: view field_cc_first_name
  $permissions['view field_cc_first_name'] = array(
    'name' => 'view field_cc_first_name',
    'roles' => array(),
  );

  // Exported permission: view field_cc_last_name
  $permissions['view field_cc_last_name'] = array(
    'name' => 'view field_cc_last_name',
    'roles' => array(),
  );

  // Exported permission: view field_cc_mobile
  $permissions['view field_cc_mobile'] = array(
    'name' => 'view field_cc_mobile',
    'roles' => array(),
  );

  // Exported permission: view field_cc_phone
  $permissions['view field_cc_phone'] = array(
    'name' => 'view field_cc_phone',
    'roles' => array(),
  );

  // Exported permission: view field_cc_user_type
  $permissions['view field_cc_user_type'] = array(
    'name' => 'view field_cc_user_type',
    'roles' => array(),
  );

  return $permissions;
}
