<?php 
/**
 * Menu callback -- ask for confirmation of node Approve
 */
function role_approve_confirm(&$form_state, $node) {
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );
  $_role = _role_approve_role_name_by_role_id($node->field_rr_dms_role['0']['value']);
  if(empty($_role)) $_role = 'permissible';
  return confirm_form($form,
    t('Are you sure you want to approve %title for %role role?', array('%title' => $node->title, '%role'=>$_role)),
    isset($_GET['destination']) ? $_GET['destination'] : 'node/'. $node->nid,
    t('This action cannot be undone.'),
    t('Approve'),
    t('Cancel')
  );
}

/**
 * Menu callback -- ask for confirmation of node Decline
 */
function role_decline_confirm(&$form_state, $node) {
  $form['nid'] = array(
      '#type' => 'value',
      '#value' => $node->nid,
  );
  $_role = _role_approve_role_name_by_role_id($node->field_rr_dms_role['0']['value']);
  if(empty($_role)) $_role = 'permissible';
  return confirm_form($form,
      t('Are you sure you want to reject %title for %role role?', array('%title' => $node->title, '%role'=>$_role)),
      isset($_GET['destination']) ? $_GET['destination'] : 'node/'. $node->nid,
      t('This action cannot be undone.'),
      t('Decline'),
      t('Cancel')
  );
}

/**
 * Execute node Approve
 */
function role_approve_confirm_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['confirm']) {
    $nid = $form_state['values']['nid'];
    $node=node_load($nid);
    $uid=$node->uid;
    
    //get the user to grant the action
    if($grant_user = user_load($uid)) {
      $dms_role=$node->field_rr_dms_role[0][value];
      $adv_roles = $node->field_rr_adv_roles;
      if (!empty($dms_role) && $dms_role != 0) {
        $new_role[2] = 'authenticated user';
        $new_role[$dms_role]=_role_approve_role_name_by_role_id($dms_role);
        user_save($grant_user, array('roles' => $new_role));
        cache_clear_all(NULL, 'cache_menu', TRUE);
		menu_rebuild();
      }
      else if(count($adv_roles) == 1) {
        $advrole = $adv_roles[0]['value'];
        $new_role[$advrole] = _role_approve_role_name_by_role_id($advrole);
        user_save($grant_user, array('roles' => $new_role));
        cache_clear_all(NULL, 'cache_menu', TRUE);
		menu_rebuild();
      }
      else {
        foreach ($adv_roles as $value) {
          $advrole = $value['value'];
          $new_role[$advrole]=_role_approve_role_name_by_role_id($advrole);
          cache_clear_all(NULL, 'cache_menu', TRUE);
		  menu_rebuild();
        }
        global $current_rid;
        if(module_exists('Role Selector')) {
          // Reload user roles if provided. Code to be used if role selector is enabled
          if (isset($new_role) && is_array($new_role)) {
            db_query('DELETE FROM {role_selector_users_roles} WHERE uid = %d', $uid);
            foreach ($new_role as $key => $rid) {
              db_query('INSERT INTO {role_selector_users_roles} (uid, rid) VALUES (%d, %d)', $uid, $key);
            }
            db_query('DELETE FROM {users_roles} WHERE uid = %d', $uid);
            if(in_array($current_rid, $new_role)) {
              db_query('INSERT INTO {users_roles} (uid, rid) VALUES (%d, %d)', $uid, $current_rid);
            } else {
              reset($new_role);
              db_query('INSERT INTO {users_roles} (uid, rid) VALUES (%d, %d)', $uid, 20);
              db_query('DELETE FROM {sessions} WHERE uid = %d', $uid);
            }
          }
        }
        else {
          user_save($grant_user, array('roles' => $new_role));
          cache_clear_all(NULL, 'cache_menu', TRUE);
		  menu_rebuild();
        }
      }
      
      db_query('UPDATE {role_approvals} SET status = %d, timestamp = %d WHERE uid = %d',1, time(), $uid);
      
      user_unblock_user_action($grant_user);
      
      $message  = drupal_mail('web_ldap_role_management', 'roleapproved', $grant_user->mail, user_preferred_language($grant_user), $params);
      drupal_set_message(t('Role Successfully Granted.'));
    } 
    else {
      drupal_set_message(t('Role operation failed.'));
    }
  } 
  
  $form_state['redirect'] = '<front>';
}


/**
 * Execute node decline
 */
function role_decline_confirm_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['confirm']) {
    
    $nid = $form_state['values']['nid'];
    
    $node=node_load($nid);
    
    $uid=$node->uid;
    
    //get the user to grant the action
    if($grant_user = user_load($uid)) {
      user_block_user_action($grant_user);
      
      $sql = 'UPDATE {role_approvals} SET status = 2, timestamp = ' . time() . '  WHERE uid = ' .$uid;
      db_query($sql);
      
      $message  = drupal_mail('web_ldap_role_management', 'roledeclined', $grant_user->mail, user_preferred_language($grant_user), $params);
      drupal_set_message(t('Role Successfully Declined.'));
    } 
    else {
      drupal_set_message(t('Role operation failed.'));
    }
  }
  
  $form_state['redirect'] = '<front>';
}

function _role_approve_role_name_by_role_id($roleid){
  $role_result = db_result(db_query('SELECT name FROM {role} WHERE rid = %d', $roleid));
  if($role_result)
    return $role_result;

  return FALSE;
}

