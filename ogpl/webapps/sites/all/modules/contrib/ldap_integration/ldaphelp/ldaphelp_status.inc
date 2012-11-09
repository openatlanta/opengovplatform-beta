<?php
/**
 * @file
 * status file for ldaphelp module
 *
 */

define('REQUIREMENT_INFO', -1);
define('REQUIREMENT_OK', 0);
define('REQUIREMENT_WARNING', 1);
define('REQUIREMENT_ERROR', 2);


function ldaphelp_status() {

  drupal_add_css(drupal_get_path('module', 'system') .'/system.css', 'module', 'all', FALSE);
  include_once(drupal_get_path('module', 'system') .'/system.admin.inc');

  // server and LDAP Module Data
  $heading = "Server and LDAP Module";
  $key = 'server';

  $phpinfo = ldaphelp_parsePHPModules();

  $status = ldaphelp_get_server($phpinfo, $info);

  $reporting_text .= _ldaphelp_parse_status_to_text($status, $heading);

  $content .=  "<h3>$heading</h3>" . theme_status_report($status);

  // overall ldapauth settings
  $heading = "LDAP Authentication Settings";
  $status = ldaphelp_get_ldapauth($info);
  $content .= "<h3>$heading</h3>". theme_status_report($status);
  $reportingtext .= _ldaphelp_parse_status_to_text($status, $heading);

  $conf_data = _ldaphelp_get_configuration(TRUE, NULL);
  $ldaps  = $conf_data['ldaps'];

  foreach ($ldaps as $sid => $ldap) {
    $heading =  $ldap['name'] .' LDAP (sid='. $ldap['sid'] .')';
    $edit_ldap = l(t('[edit]'), "admin/settings/ldap/ldapauth/edit/". $sid );
    $test_results = _ldaphelp_testldap($ldap, $sid);
    $status = ldaphelp_get_ldap_server($info, $sid, $ldap, $test_results, $edit_ldap);
    $content .= "<h3>$heading</h3>". theme_status_report($status);
    $reportingtext .= _ldaphelp_parse_status_to_text($status, $heading, array($edit_ldap => ""));
  }


  $reportingtext .= "ADMIN SETTINGS". ldaphelp_arraytotxt($conf_data['admin_settings']);
  foreach ($conf_data['ldaps'] as $sid => $ldap) {
    $reportingtext .= "\r\nLDAP sid=$sid\r\n". ldaphelp_arraytotxt($conf_data['ldaps'][$sid]);
  }
  $content .= '<h3>Bug and Support Reporting Info</h3><p>
  Cut and paste this into a text file and attach it to any bug or support requests.
  <strong><em>Remove or replace any data you feel should not be made public before sharing this data.</em></strong></p>
  <form><textarea cols="80" rows="20">'. $reportingtext .'</textarea></form>';

  return $content;
}
function ldaphelp_get_server($phpinfo, &$info) {

  $info['phpversion'] = phpversion();
  $info['ldaploaded'] = extension_loaded('ldap');
  $info['ldap'] = $phpinfo['ldap'];

  $text = "";
  foreach ($phpinfo['ldap'] as $key => $value) {
    $text .= "<br/>$key: ". $value[0];
  }
  $info['ldap']['text'] = $text;

  //$info['ldap']['text'] = ldaphelp_arraytohtml($phpinfo['ldap']);

  $modules = module_rebuild_cache();
  $ldapmodules = array('ldapauth', 'ldapgroups', 'ldapdata', 'ldaphelp');
  foreach ( $ldapmodules as $ldapmodule) {
    $data['status'] = $modules[$ldapmodule]->status;
    $data['schema_version'] = $modules[$ldapmodule]->schema_version;
    $data['version'] = $modules[$ldapmodule]->info['version'];
    $data['text'] = "status: ". $data['status']
      .", schema_version: " . $data['schema_version']
      .", v: " . $data['version'];

    $info[$ldapmodule] = $data;
  }

  // set status array to be converted into html table.
  if ($phpinfo['Apache Environment']) {
    $status[] = array(
      'title' => 'Apache',
      'value' => $phpinfo['Apache Environment']['SERVER_SOFTWARE']
    );
  }
  elseif ($_SERVER["SERVER_SOFTWARE"]) {
        $status[] = array(
      'title' => 'SERVER_SOFTWARE',
      'value' => $_SERVER["SERVER_SOFTWARE"]
    );

  }

  $status[] = array(
    'title' => 'PHP version',
    'value' => phpversion()
  );

  if (! $info['ldaploaded']) {
    $status[] = array( 'title' => 'PHP ldap extension not loaded',
    'value' => l(t('PHP LDAP extension'), 'http://us2.php.net/ldap') . ' ' . t('must be loaded for LDAP Integration to work.
    It comes compiled with most versions of PHP.')  ,
    'severity' => REQUIREMENT_ERROR);
  }
  else {
    $status[] = array( 'title' => 'PHP ldap extension data',
    'value' => $info['ldap']['text']  ,
    'severity' => 0);
  }

  $status[] = array('title' => 'Drupal', 'value' => VERSION , 'severity' => "0");

  foreach ( $ldapmodules as $ldapmodule) {
    $status[] =  array('title' => $ldapmodule, value => $info[$ldapmodule]['text'], 'severity' => "0");
  }
  return $status;
}

function ldaphelp_get_ldapauth(&$info) {
  $info['ldapauth']['login_process_text'] = (LDAPAUTH_LOGIN_PROCESS == LDAPAUTH_AUTH_EXCLUSIVED) ? "LDAP directory only" : "Mixed Mode";
  $info['ldapauth']['login_process_text'] .= " (". LDAPAUTH_LOGIN_PROCESS .')';
  $info['ldapauth']['login_conflict_text'] = (LDAPAUTH_LOGIN_CONFLICT == LDAPAUTH_CONFLICT_RESOLVE) ? "Associate local account with the ldap entry" : "Disallow login and log the conflict";
  $info['ldapauth']['login_conflict_text'] .= "  (". LDAPAUTH_LOGIN_CONFLICT .')';

  $status[] =  array(
    'title' => 'Authentication mode',
    value =>   $info['ldapauth']['login_process_text'] ,
  'severity' => "0");

  $status[] =  array(
    'title' => 'Conflict Resolve Feature',
    value =>   $info['ldapauth']['login_conflict_text'],
  'severity' => "0");

  $info['ldapauth']['ldapauth_disable_pass_change_text'] = (LDAPAUTH_FORGET_PASSWORDS == TRUE) ? "Do not " : "Do";
  $info['ldapauth']['ldapauth_disable_pass_change_text'] .= 'store users\' passwords during sessions.';

  $status[] =  array('title' => 'Security Options', value => $info['ldapauth']['ldapauth_disable_pass_change_text'], 'severity' => "0");

  $info['ldapauth']['ldapauth_disable_pass_change_text'] = (LDAPAUTH_DISABLE_PASS_CHANGE == TRUE) ? "R" : "Do not R";
  $info['ldapauth']['ldapauth_disable_pass_change_text'] .= 'emove password change fields from user edit form';

  $info['ldapauth']['ldapauth_alter_email_field_text'] = 'ldapauth_alter_email_field: '. LDAPAUTH_ALTER_EMAIL_FIELD ;

  $status[] =  array('title' => 'LDAP UI Options', value => $info['ldapauth']['ldapauth_disable_pass_change_text'] ."<br/>". $info['ldapauth']['ldapauth_alter_email_field_text'], 'severity' => "0");

  return $status;
}
function ldaphelp_get_ldap_server(&$info, $sid, &$ldap, &$test, $edit_ldap) {

  $description =  "server: ". $ldap['server'] .
    "<br/>port: " . $ldap['port'] .
    "<br/>tls: ". $ldap['tls'] .
    "<br/>encrypted: ". $ldap['encrypted'];
  $status[] = array( 'title' => 'Server Settings '. $edit_ldap, 'value' => $description , 'severity' => "0");

  // login procedure
  $description =  "user_attr:<code> ". $ldap['user_attr'] .
    "</code><br/>mail_attr: <code>". $ldap['mail_attr'] ."</code>";
  $status[] = array( 'title' => 'Login Procedure '. $edit_ldap, 'value' => $description , 'severity' => "0");

  // advanced configuration
  $description = "binddn: <code>". $ldap['binddn'] .
    "</code><br/>bindpw: ". $ldap['bindpw'];
  $status[] = array( 'title' => 'Advanced Configuration '. $edit_ldap, 'value' => $description , 'severity' => "0");


  // bind test
  $description =   "Bind Type: ". $test['bind_type'] .
    "<br/>Bind Result?: ". $test['bind_result_text'];
  if (! $test['bind_success']) {
    $description .=  ldaphelp_arraytohtml(
      array(
      'LDAP Error' => $test['bind_result_error'],
      'LDAP Error Number' => $test['bind_result_errno'],
      ));
  }
  // 49: invalid credentials.
  $severity = ($test['bind_success'] === TRUE) ? "0" : "2";
  $status[] = array( 'title' => 'Bind Test to <code>'. $ldap['server'] ."</code>", 'value' => $description , 'severity' => $severity);


  foreach ($test['basedns'] as  $basedn) {

    if (isset($basedn['result']['count'])) {
        $usersfound =  TRUE ;
        $usersfoundtext = "Yes";
        $severity = 0;
    }
    else {
      $usersfound =  FALSE ;
      $usersfoundtext = "No";
      $validbasedn = $basedn['basedn'];
      $severity = 2;

      $result = ldaphelp_baddn($basedn['basedn'], 'Base DN') ;

      if (!$result['boolean']) {
        $error['mal_formed_dn'] = $result['text'];
      }

      $error['bind_success_search_failed'] = "<br/>Successfully bound to server <code>". $ldap['server'] ."</code>, but found" .
      " no users in generic search (". $ldap['user_attr'] ."=*)  Suggestions: <ul>";

      if ($basedn['result']['no_user_attr_success'] && ! $data['result']['with_user_attr_success']) {
        $error['bind_success_search_failed'] .= "<li> User attribute name <code>" .  $ldap['user_attr'] .
        " </code> may be wrong. Found LDAP entries with search filter <code>CN=*</code>, ".
        " but not with search filter <code>". $ldap['user_attr'] ."=*</code>.  </li>";
      }
      elseif ($tests[$sid]['bind_type'] == 'non-anon') { // no results in either search and non anonymous search
        // you are not allowed to perform an anonymous search of your ldap
        // or you meant to perform a non-anonymouse search but left the password empty.
        $error['bind_success_search_failed'] .= "<li>Anonymous searches of your LDAP or the Base DN <code>".  $basedn['basedn'] .
        " </code> may not be allowed.  Perhaps you need to create or use a service account to query the ldap.</li>";
      }
      $error['bind_success_search_failed'] .= "<li>Perhaps Base DN is incorrect: <code>".  $basedn['basedn'] ."</code></li>";
      $error['bind_success_search_failed'] .= "</ul>";

    }

  $header = 'Base DN:<br/><code>'. $basedn['basedn'] .'</code>';
  $value =   "<br/>Found Users in search of base DN?: <strong>". $usersfoundtext ."</strong>".
    $error['bind_success_search_failed']
    . $error['mal_formed_dn'];
  $status[] = array( 'title' =>  $header .' '. $edit_ldap, 'value' => $value , 'severity' => $severity);
  }
  return $status;

}
function _ldaphelp_parse_status_to_text($status, $heading, $replacements = array()) {

  $var_del = "\r\n------------------------------------------------\r\n";
  $section_del = "\r\n\r\n================================================\r\n";
  $name_val_del = ":\r\n";
  $lr = "\r\n";

  $replacements = array_merge($replacements, array(
  '<br/>' => $lr,
  '<ul>' => $lr,
  '</ul>' => $lr,
  '<li>' => $lr,
  '</li>' => "",
  "<code>" => "",
  "</code>" => "",
  "<strong>" => "",
  "</strong>" => ""
  ));


  $content = drupal_strtoupper($heading) . $lr  ;
  foreach ($status as $item) {
  //  $item['value'] = str_replace(array('<br/>','<ul>','</ul>','<li>','</li>',"<code>","</code>"),
   // array("\r\n","\r\n","\r\n","\r\n","\r\n"),$item['value'] );
    $item['value'] = str_replace(array_keys($replacements), array_values($replacements), $item['value'] );
    $item['title'] = str_replace(array_keys($replacements), array_values($replacements), $item['title'] );
    $content .=   $item['title'] . $name_val_del . $item['value'] . $var_del;
  }
  return $content;
}

function _ldaphelp_testldap($ldap, $sid) {
  global $_ldapauth_ldap;

 // foreach ($ldaps as $sid => $ldap) {
    $test = array();
    // Initialize LDAP.
    _ldapauth_init($sid);

    if ($_ldapauth_ldap->getOption('binddn') && $_ldapauth_ldap->getOption('bindpw')) {
      $test['bind_result'] = $_ldapauth_ldap->connectAndBind($_ldapauth_ldap->getOption('binddn'), $_ldapauth_ldap->getOption('bindpw'));
      $test['bind_type'] = "non-anon";

    }
    else {
      $test['bind_result'] = $_ldapauth_ldap->connectAndBind();
      $test['bind_type'] = "anon";
    }

    if ($test['bind_result']) {
      $test['bind_result_text'] =  "Success";
      $test['bind_success'] = TRUE;
    }
    else {
      $test['bind_result_error'] = ldap_error($_ldapauth_ldap->connection);
      $test['bind_result_errno'] = ldap_errno($_ldapauth_ldap->connection);
      $test['bind_result_text'] =  "Fail";
      $test['bind_success'] = FALSE;
    }

    foreach (explode("\r\n", $_ldapauth_ldap->getOption('basedn')) as $base_dn) {
      $user_attr = $_ldapauth_ldap->getOption('user_attr') ? $_ldapauth_ldap->getOption('user_attr') : LDAPAUTH_DEFAULT_USER_ATTR;
      $filter = "$user_attr=*";
      $result = $_ldapauth_ldap->search($base_dn, $filter, array($user_attr), 0, 1, 1);
      $basedn_data = array();
      $basedn_data['result']['error'] = ldap_error($_ldapauth_ldap->connection);
      $basedn_data['basedn'] = $base_dn;
      $basedn_data['result']['count'] = $result['count'];
      $basedn_data['result']['sample0'] = $result[0];
      $basedn_data['result']['dnufn'] = ldap_dn2ufn($base_dn);

      if (! $basedn_data['result']['count']) {
          $basedn_data['result']['with_user_attr_success'] = FALSE;
        // try searching for any object to see if user_attr is wrong
          $filter = "CN=*";
          $result = $_ldapauth_ldap->search($base_dn, $filter, array($user_attr), 0, 1, 1);
          $basedn_data['result']['no_user_attr_success'] = ($result['count']) ? TRUE : FALSE;
        // bad attribute name
      }
      else {
        $basedn_data['result']['with_user_attr_success'] = TRUE;
      }
      $test['basedns'][] = $basedn_data;
    }
  return $test;
}

function ldaphelp_baddn($dn, $dn_name) {
  $result = array();
  $valid_attr_name = '[a-zA-Z\d\s]';
  $valid_attr_values = '[a-zA-Z\d\s]';
  $regex = '/^('. $valid_attr_name .'*\='. $valid_attr_values .'*[,]{1})*('. $valid_attr_name .'*\='. $valid_attr_values .'*){1}$/';
  // $target = "CN=Schema A1, CN2 =Configuration,DC=ad,DC=uiuc,DC=edu";
  // $target = "ou=education,dc=ad,dc=uiuc,dc=edu";
  $match = (preg_match($regex, $dn)) ? TRUE : FALSE;
  $result['boolean'] = $match;
  if (!$match) {
    $result['text'] = "Invalid format for:<br/> <code><strong>". htmlspecialchars($dn)
    ."</strong><code><br/> One cause may be editing $dn_name with a wysiwyg editor which leaves html.";

  }
  return $result;
}

/** parse php modules from phpinfo */
function ldaphelp_parsePHPModules() {
  ob_start();
  phpinfo();
  $s = ob_get_contents();
  ob_end_clean();

  $s = strip_tags($s, '<h2><th><td>');
  $s = preg_replace('/<th[^>]*>([^<]+)<\/th>/', "<info>\\1</info>", $s);
  $s = preg_replace('/<td[^>]*>([^<]+)<\/td>/', "<info>\\1</info>", $s);
  $vtmp = preg_split('/(<h2>[^<]+<\/h2>)/', $s, -1, PREG_SPLIT_DELIM_CAPTURE);
  $vmodules = array();
  for ($i=1; $i<count($vtmp); $i++) {
    if (preg_match('/<h2>([^<]+)<\/h2>/', $vtmp[$i], $vmat)) {
      $vname = trim($vmat[1]);
      $vtmp2 = explode("\n", $vtmp[$i+1]);
      foreach ($vtmp2 AS $vone) {
        $vpat = '<info>([^<]+)<\/info>';
        $vpat3 = "/$vPat\s*$vpat\s*$vpat/";
        $vpat2 = "/$vPat\s*$vpat/";
        if (preg_match($vpat3, $vone, $vmat)) { // 3cols
          $vmodules[$vname][trim($vmat[1])] = array(trim($vmat[2]), trim($vmat[3]));
        }
        elseif (preg_match($vpat2, $vone, $vmat)) { // 2cols
          $vmodules[$vname][trim($vmat[1])] = trim($vmat[2]);
        }
      }
    }
  }
  return $vmodules;
}
