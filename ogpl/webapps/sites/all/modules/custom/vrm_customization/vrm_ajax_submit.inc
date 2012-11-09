<?php 
function vrm_customization_node_edit_ajax($node) {
  module_load_include('inc', 'node', 'node.pages');

  // Invoke hook_nodapi and hook_node
  node_object_prepare($node);

  $output = drupal_get_js() . drupal_get_form('feedback_node_form', $node);
  
  print $output;
  die();
}
