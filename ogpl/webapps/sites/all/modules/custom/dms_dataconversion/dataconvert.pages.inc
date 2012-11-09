<?php 
/**
 * Menu callback -- 
 */
function show_dataset($nid, $format) {
  /*  validate the inputs */
  if (form_validate_integer($nid)) {
    drupal_set_message('Invalid argument','error');
    drupal_not_found();
    exit();
  }
  if (form_validation_validate_input($format)) {
    drupal_set_message('Invalid argument','error');
    drupal_not_found();
    exit();
  }
  /*  validate the inputs finished*/
  
  $node = node_load($nid);
  $filepath = $node->field_dsat_downloadable[0]['value']['field_dam_datafile'][0]['filepath'];
  // echo "<pre>" . print_r($node->field_dsat_downloadable, TRUE) . "</pre>";
  $filepath = parse_file($filepath);
  $url = "http://data.gov.in/".$filepath;
  print $url;
  $json = read_source_dataproxy($url);
  switch($format) {
    case 'json':
      $output = $json;
      break;
    case 'jsonp':
      $json = read_source_dataproxy($url, $format);
      $output = $json;
      break;
    case 'xml':
      $output = document_parser($json, 'xml');
      break;
    case 'xls':
      break;
  }
  print $output;
}

function parse_file($filepath){
  if(variable_get('file_downloads', FILE_DOWNLOADS_PUBLIC) == FILE_DOWNLOADS_PRIVATE){
    $path = str_replace(file_directory_path(), 'system/files', $filepath);
  } else {
    $path = $_SERVER['DOCUMENT_ROOT'] . base_path() . $filepath;
  }
  return $path;
}