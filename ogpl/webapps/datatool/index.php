<?php
//error_reporting(E_ALL);
set_time_limit(0);
/** Include path **/
set_include_path(get_include_path() . PATH_SEPARATOR . 'Classes/');
include 'remoteFileLoad.php';
$message = RemoteFileLoad::validate_querystring($_GET);
if (!$message['error'] || empty($_GET)) {
  extract($_GET);
  if(empty($workbook_count)) {
    if (empty($format)) $format = 'jsonp';
    if (empty($callback)) $callback = 'callback';
    if (empty($url)) $url = 'http://localhost/datatool/earthquakes.csv';
    if (empty($worksheet)) $worksheet = 0;
    $result = RemoteFileLoad::createDataset($url, $format, $callback, $worksheet);
  }
  else {
    if (empty($url)) $url = 'http://localhost/datatool/earthquakes.csv';
    echo RemoteFileLoad::getWorkbooks($url);
  }
}
else
{
  echo $message['Message'];
}
?>