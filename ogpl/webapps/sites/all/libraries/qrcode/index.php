<?php 
include('phpqrcode.php');

function form_validation_validate_url($text){
  return preg_match('|^http(s)?://[a-z0-9-]+(.[a-z0-9-]+)*(:[0-9]+)?(/.*)?$|i', $text);
}

$input = $_GET['q'];
$allow_host = array('demodata.nic.in', 'www.demodata.nic.in', 'data.gov.in', 'www.data.gov.in' );

if(form_validation_validate_url($input)) {
    $input_array = parse_url($input);
    if(in_array($input_array['host'], $allow_host)) {
      QRcode::png($input);
      die();
    } 
}
QRcode::png('Not Available');