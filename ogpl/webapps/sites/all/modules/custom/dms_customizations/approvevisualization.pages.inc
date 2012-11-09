<?php 
/**
 * Menu callback -- ask for confirmation of node Approve
 */
function approve_visualization(&$form_state, $node) {
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );
  return confirm_form($form,
    t('Are you sure you want to approve %title for visualization?', array('%title' => $node->title)),
    isset($_GET['destination']) ? $_GET['destination'] : 'node/'. $node->nid,
    t(''),
    t('Approve'),
    t('Cancel')
  );
}

/**
 * Menu callback -- ask for confirmation of node Disapprove
 */
function disapprove_visualization(&$form_state, $node) {
  $form['nid'] = array(
      '#type' => 'value',
      '#value' => $node->nid,
  );
  return confirm_form($form,
      t('Are you sure you want to Disapprove %title for visualization?', array('%title' => $node->title)),
      isset($_GET['destination']) ? $_GET['destination'] : 'node/'. $node->nid,
      t(''),
      t('Disapprove'),
      t('Cancel')
  );
}


/**
 * Execute visualization Approve
 */
function approve_visualization_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $nid = $form_state['values']['nid'];
    $node=node_load($nid);
    $node->field_ds_is_visual[0]['value'] = '1' ;
    node_save($node);
  }
  $form_state['redirect'] = drupal_get_destination();
}

/**
 * Execute visualization Disapprove
 */
function Disapprove_visualization_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $nid = $form_state['values']['nid'];
    $node=node_load($nid);
    $node->field_ds_is_visual[0]['value'] = 0 ;
    node_save($node);
  }
  $form_state['redirect'] = drupal_get_destination();
}

