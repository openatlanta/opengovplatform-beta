<?php

/**
 * @file
 * User page callback file for the rpx_ui module.
 */

/**
 * Menu callback; manage Engage 3rd party identities for the specified user.
 */
function rpx_user_identities($account) {
  drupal_set_title(check_plain($account->name));

  $header = array(t('Account type'), t('Account ID'), t('Operations'));
  $rows = array();

  $query = db_query("SELECT am.aid, authname, provider_name, provider_title FROM {authmap} am INNER JOIN {rpx_linked_account} la ON am.aid = la.aid WHERE module = 'rpx_core' AND la.uid = %d", $account->uid);

  while ($identity = db_fetch_object($query)) {
    $rows[] = array(
      theme('rpx_icon', $identity->provider_name, 'small', 'rpx-icon-inline') . '<span' . drupal_attributes(array('class' => 'rpx-provider-title')) . '>' . $identity->provider_title .  '</span>',
      check_plain($identity->authname),
      l(t('Delete'), 'user/' . $account->uid . '/rpx/delete/' . $identity->aid),
    );
  }

  rpx_js(TRUE);

  $realm = variable_get('rpx_realm', '');
  $realm_scheme = variable_get('rpx_realm_scheme', 'http');
  $sign_in_url = "$realm_scheme://$realm/openid/v2/signin";
  $token_url = _rpx_token_url(array('add_to_account' => 'true'));

  $link_options = array(
    'attributes' => array('class' => 'rpxnow', 'onclick' => 'return false;'),
    'query' => array('token_url' => $token_url),
  );

  $output = theme('table', $header, $rows);
  $output .= l(t('Add linked account'), $sign_in_url, $link_options);

  return $output;
}

/**
 * Menu callback; Delete the specified Engage identity from the system.
 */
function rpx_user_delete_form($form_state, $account, $aid = NULL) {
  if (!$aid) {
    drupal_not_found();
    return;
  }

  $provider_title = db_result(db_query("SELECT provider_title FROM {authmap} am INNER JOIN {rpx_linked_account} la ON am.aid = la.aid WHERE la.uid = %d AND am.aid = %d AND module = 'rpx_core'", $account->uid, $aid));

  if (!$provider_title) {
    drupal_not_found();
    return;
  }

  $form = array();

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  $form['aid'] = array(
    '#type' => 'value',
    '#value' => $aid,
  );

  $username = check_plain($account->name);

  // If we were called from somethere else (e.g. a view), we want to return there
  // on Cancel.
  $dest = drupal_get_destination();
  $dest = isset($_REQUEST['destination']) ?  substr($dest, 12) : 'user/' . $account->uid . '/rpx';
  return confirm_form($form, t('Are you sure you want to remove this linked %provider account for %user?', array('%provider' => $provider_title, '%user' => $username)), $dest, '');
}

/**
 * Handle identity deletion by removing {authmap} and {rpx_linked_account}
 * entries.
 */
function rpx_user_delete_form_submit($form, &$form_state) {
  $uid = $form_state['values']['uid'];
  $aid = $form_state['values']['aid'];

  $linked_account = db_fetch_object(db_query("SELECT authname, provider_name, provider_title FROM {authmap} am INNER JOIN {rpx_linked_account} la ON am.aid = la.aid WHERE la.uid = %d AND am.aid = %d AND module = 'rpx_core'", $uid, $aid));

  // Linked account data has to be deleted from two tables.
  db_query("DELETE FROM {authmap} WHERE uid = %d AND aid = %d AND module = 'rpx_core'", $uid, $aid);
  db_query("DELETE FROM {rpx_linked_account} WHERE aid = %d", $aid);

  drupal_set_message(t('The linked %provider account has been successfully removed.', array('%provider' => $linked_account->provider_title)));

  // Save provider info for token replacement.
  $_SESSION['rpx_last_provider_info'] = array(
    'name' => $linked_account->provider_name,
    'title' => $linked_account->provider_title,
    'id' => $linked_account->authname,
  );

  // Let other modules (e.g. rpx_rules) know that a linked account has been
  // removed.
  $account = array(
    'user' => user_load($uid),
    'id' => $linked_account->authname,
    'provider_machinename' => $linked_account->provider_name,
    'provider_title' => $linked_account->provider_title,
  );
  _rpx_delete_engage_mapping($linked_account->authname, $uid);
  module_invoke_all('rpx_linked_account', 'deleted', $account);

  $form_state['redirect'] = 'user/' . $uid . '/rpx';
}
