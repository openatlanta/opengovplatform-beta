<?php

/**
 * Implementation of hook_jq().
 * http://drupal.org/project/jq
 */
function jquery_multiselect_jq($op, $plugin = NULL) {
  if ($op == 'info') {
    $path = drupal_get_path('module', 'jquery_multiselect');
    return array(
      'multiSelect' => array(
        'name' => t('Multi Select'),
        'description' => t('The jquery ui multiselect plugin'),
        'version' => '1.0',
        'url' => 'http://github.com/michael/multiselect',
        'files' => array(
          'js' => array(
            $path .'/jquery/js/jquery-ui-1.8.custom.min.js',        
            $path .'/jquery/js/ui.multiselect.js',            
          ),
          'css' => NULL,
        ),
        'invocation' => NULL,
      ),
    );
  }
}
