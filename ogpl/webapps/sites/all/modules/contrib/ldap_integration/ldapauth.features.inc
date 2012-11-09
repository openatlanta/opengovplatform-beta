<?php
/**
 * @file
 * Feature related functions.
 */


//////////////////////////////////////////////////////////////////////////////
// Code for feature component: ldap_servers
/**
 * Implementation of hook_features_export_options. [component_hook]
 *
 * This hook will alert features of which specific items of this component may
 * be exported. Using ctools export info here.
 *
 * @return array
 *   A keyed array of items, suitable for use with a FormAPI select or
 *   checkboxes element.
 */
function ldap_servers_features_export_options() {
  module_load_include('inc', 'ldapauth', 'includes/ldap.core');
  $options = array();
  $servers = ldapauth_server_load_all();
  foreach ( $servers as $server ) {
    $options[$server->machine_name] = $server->name;
  }
  return $options;
}

/**
 * Implementation of hook_features_export [component hook]
 *
 * This defines the component dependencies and ldap server records to export.
 *
 * @param array $data
 * @param array &$export
 * @param string $module_name
 * @return array
 */
function ldap_servers_features_export($data, &$export, $module_name = "") {
  module_load_include('inc', 'ldapauth', 'includes/ldap.core');
  $export['dependencies']['ldapauth'] = 'ldapauth';
  $submodules = ldapauth_submodules('ldap_servers');
  foreach ( $submodules as $submodule ) {
    if ( module_exists($submodule ) ) {
      $export['dependencies'][$submodule] = $submodule;
    }
  }
  foreach ( $data as $component ) {
    $export['features']['ldap_servers'][$component] = $component;
  }
  return array();
}

/**
 * Implementation of hook_features_export_render. [component hook]
 *
 * Creates code to export ldapauth DB tabel server records.
 *
 * @param string $module_name
 * @param array $data
 * @param array $export
 * @return array
 */
function ldap_servers_features_export_render($module, $data, $export) {
  module_load_include('inc', 'ldapauth', 'includes/ldap.core');
  $code = array();
  $code[] = '  $servers = array();';
  // If this is an override check, export all current servers
  if ( is_null($export) ) {
    $servers = ldapauth_server_load_all(TRUE);
    foreach ($servers as $server) {
      unset($server->sid);
      $server = (array) $server;
      ksort($server);  // Sort because updated tables don't match, new tables
      $code[] = "  \$servers['{$server['machine_name']}'] = " . features_var_export($server, '  ') . ";";
    }
  }
  else {
    foreach ($data as $name) {
      $server = ldapauth_server_load($name);
      unset($server->sid);
      $server = (array) $server;
      ksort($server);
      $code[] = "  \$servers['{$name}'] = " . features_var_export($server, '  ') . ";";
    }
  }
  $code[] = '  return $servers;';
  $code = implode("\n", $code);
  return array('default_ldap_servers' => $code );
}

/**
 * Implementation of hook_features_revert(). [component_hook]
 *
 * This is called when a feature is "reverted" via the UI.  It will
 * delete all existing servers not defined by the feature, update
 * existing servers to match the feature defaults, and add in
 * any server defined in the feature that don't exist.
 */
function ldap_servers_features_revert($module) {
  module_load_include('inc', 'ldapauth', 'includes/ldap.core');
  $default_servers = module_invoke($module, 'default_ldap_servers');
  $servers = ldapauth_server_load_all(TRUE);
  $existing_servers = array();

  // Update any existing servers in feature and delete those not in the feature.
  foreach ( $servers as $server ) {
    $machine_name = $server->machine_name;
    $existing_servers[$machine_name] = $machine_name;
    if ( isset($default_servers[$machine_name]) ) { // Update servers
      $default_servers[$machine_name]['sid'] = $server->sid;
      ldapauth_server_save($default_servers[$machine_name], TRUE);
    }
    else {  // Delete server
      ldapauth_server_delete($server, TRUE);
    }
  }
  // Add any servers in the feature that don't exist.
  foreach ( $default_servers as $server ) {
    if ( ! isset($existing_servers[$server['machine_name']]) ) { // Add in default server not in DB
      unset($server['sid']);
      ldapauth_server_save($server, TRUE);
    }
  }
}

/**
 * Implementation of hook_features_rebuild(). [component_hook]
 *
 * This is called the first time a feature is installed.  It will
 * add any non-existing servers to the site.
 */
function ldap_servers_features_rebuild($module) {
  module_load_include('inc', 'ldapauth', 'includes/ldap.core');
  $servers = module_invoke($module, 'default_ldap_servers');
  foreach ($servers as $server) {
    $existing_server = ldapauth_server_load($server['machine_name']);
    if ( empty($existing_server) ) {
      ldapauth_server_save($server);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////
// Code for feature component: ldap_settings
/**
 * Implementation of hook_features_export_options. [component_hook]
 *
 * @return array
 *   A keyed array of items, suitable for use with a FormAPI select or
 *   checkboxes element.
 */
function ldap_settings_features_export_options() {
  $info = array(
    'ldapauth_login_process' => t('Authentication') . ': ' . t('Authentication mode'),
    'ldapauth_login_conflict' => t('Authentication') . ': ' . t('User conflict resolve process'),
    'ldapauth_forget_passwords' => t('Authentication') . ': ' . t('Store user passwords'),
    'ldapauth_sync_passwords' => t('Authentication') . ': ' . t('Sync passwords'),
    'ldapauth_create_users' => t('Authentication') . ': ' . t('Create new users'),
    'ldapauth_alter_username_field'  => t('Authentication') . ': ' . t('Alter user name field'),
    'ldapauth_disable_pass_change' => t('Authentication') . ': ' . t('Remove password fields'),
    'ldapauth_alter_email_field' => t('Authentication') . ': ' . t('Alter email field'),
  );
  ldapauth_submodules("ldap_settings", $info);
  return $info;
}

/**
 * Implementation of hook_features_export [component hook]
 *
 * @param array $data
 *   this is the machine name for the component in question
 * @param array &$export
 *   array of all components to be exported
 * @param string $module_name
 *   The name of the feature module to be generated.
 * @return array
 *   The pipe array of further processors that should be called
 */
function ldap_settings_features_export($data, &$export, $module_name = "") {
  $export['dependencies']['ldapauth'] = 'ldapauth';
  $submodules = ldapauth_submodules('ldap_settings');
  foreach ( $submodules as $submodule ) {
    if ( module_exists($submodule ) ) {
      $export['dependencies'][$submodule] = $submodule;
    }
  }
  return variable_features_export($data, $export, $module_name);
}

/**
 * Implementation of hook_features_export_render() [component_hook]
 * These are not really called since StrongArm is handling this.
 */
function ldap_settings_features_export_render($module, $data) {
  return variable_features_export_render($module, $data);
}

/**
 * Implementation of hook_features_revert(). [component_hook]
 * These are not really called since StrongArm is handling this.
 */
function ldap_settings_features_revert($module) {
  variable_features_revert($module);
}

/**
 * Implementation of hook_features_rebuild(). [component_hook]
 */
function ldap_settings_features_rebuild($module) {
  variable_features_rebuild($module);
}

/**
 * Get ldap "submodules" info that effects the feature components.
 *
 * TODO: should use a hook(s) to get these rather than hardcoding them.
 *
 * @param String $component
 * @param Array info
 */
function ldapauth_submodules( $component, &$info=NULL ) {
  switch ($component) {
    case 'ldap_servers':
      if ( $info ) {
        return; // Hmmm should not be here
      }
      return array( 'ldapdata', 'ldapgroups'); // sync has no server settings
    case 'ldap_settings':
      if ( $info ) {
        if ( module_exists('ldapdata') ) {
          $info['ldapdata_disable_picture_change'] = t('Data') . ': ' . t('Remove picture fields');
          $info['ldapdata_sync'] = t('Data') . ': ' . t('Synchronize LDAP data with Drupal profiles');
        }
        if ( module_exists('ldapsync') ) {
          $info['ldapsync_time_interval'] = t('Synchronization') . ': ' . t('Sync time interval');
          $info['ldapsync_existing_only'] = t('Synchronization') . ': ' . t('Sync existing users only');
          $info['ldapsync_login_conflict'] = t('Synchronization') . ': ' . t('User conflict resolution');
          $info['ldapsync_missing_users_action'] = t('Synchronization') . ': ' . t('Missing users action');
          $info['ldapsync_load_user_by'] = t('Synchronization') . ': ' . t('Existing users test');
          $info['ldapsync_filter'] = t('Synchronization') . ': ' . t('LDAP Sync filter');
          $info['ldapsync_filter_append_default'] = t('Synchronization') . ': ' . t('Append default filter');
        }
        return;
      }
      return array( 'ldapdata', 'ldapsync'); // groups has no global settings
    default:
      return;
  }
}
