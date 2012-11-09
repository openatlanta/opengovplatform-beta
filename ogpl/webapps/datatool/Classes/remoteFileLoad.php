<?php
class RemoteFileLoad {
  public function loadRemoteFile($url) {
    if (self::validate_file_info($url)) {
      $url_parse = parse_url($url);
      $file_name = explode('/',$url_parse['path']);
      $count = count($file_name);
      $path = 'file/'.$file_name[$count-1];
       
      $fp = fopen($path, 'w');
       
      $ch = curl_init($url);
      curl_setopt($ch, CURLOPT_FILE, $fp);
       
      $data = curl_exec($ch);
       
      curl_close($ch);
      fclose($fp);
       
      return $path;
    }
    else {
      return array('error'=> TRUE, 'Message'=> 'Invalid File Type');
    }
  }
  
  public function load_xml($url) {
    if (self::validate_file_info($url)) {
      $ch = curl_init($url);
      curl_setopt($ch, CURLOPT_FILE, $fp);
      $data = curl_exec($ch);
      curl_close($ch);
      return $data;
    }
    else {
      return array('error'=> TRUE, 'Message'=> 'Invalid File Type');
    }
  }
  function _get_file_mime($file_ext) {
    $key = self::form_validation_validate_input_replace($file_ext);
    $allowed_ext = array( 'csv' => 'text/plain', 
                          'xls' => 'application/vnd.ms-excel',
                          'xlsx'=> 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet',
                          'csv' => 'text/csv', 
                          'xml' => 'text/xml', 
                          'atom' => 'application/atom+xml'
                        );
    if (array_key_exists($key, $allowed_ext)) {
      return $allowed_ext[$key];
    }
    else {
      return FALSE;
    }
  }
  public function validate_file_info($url, $return = FALSE){
    $allowed_ext = array('text/plain', 'application/vnd.ms-excel', 'text/csv', 'text/xml', 'application/atom+xml','application/xml');
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_exec($ch);

    # get the content type
    $data = curl_getinfo($ch, CURLINFO_CONTENT_TYPE);
    $file_info = explode(";", $data);
    $file_ext = $file_info[0];
    if ($return) {
      return $file_ext;
    }
    else
    {
      if (in_array($file_ext, $allowed_ext)) {
        return TRUE;
      }
      else
      {
        return FALSE;
      }
    }
  }

  public function validate_querystring($_GET) {
    foreach($_GET as $key=>$req){
      switch($key) {
        case 'url':
         if(!self::form_validation_validate_url(urldecode($req))){
            $_GET['url']='';
            return array('error'=> TRUE, 'Message'=> 'Invalid URL');
          }
          break;
        case 'workbook':
          if (self::form_validate_integer($req)) {
            return array('error'=> TRUE, 'Message'=> 'Invalid Argument');
          }
          break;
        default:
          if(self::_check_blacklist($req)){
            return array('error'=> TRUE, 'Message'=> 'Invalid Argument');
          }
          break;
      }
    }
  }
  
  public function form_validate_integer($value){
    if ($value !== '' && (!is_numeric($value) || intval($value) != $value || $value < 0)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
  
  public function form_validation_validate_input($text){
    return preg_match("/[^a-zA-Z0-9 _-]+\/+/", $text);

  }
  public function form_validation_validate_url($text){
    return preg_match('|^http(s)?://[a-z0-9-]+(.[a-z0-9-]+)*(:[0-9]+)?(/.*)?$|i', $text);
  }
  
  public function form_validation_validate_input_replace($text){
    return preg_replace("/[^a-zA-Z0-9 _-]+\/+/", '', $text);
  }
  public function _check_blacklist($str) {
    $badch = array(
        '>">',
        '--',
        '-->',
        'DELETE',
        '#',
        "'",
        '/*',
        '<script>',
        '<ScRiPt>',
        '</ScRiPt>',
        ';',
        '"">',
        'alert()+',
        '>">',
        '00"',
        'img+src',
        '/**/',
        'javascript:alert()',
        '<script>',
        '</textarea>',
        '<script/xss+src=',
        '<iframe/+/onload',
        '%',
        "'>",
        '=',
        'onmouseover',
        'alert()'
    );
    if (is_null($str) || trim($str) == "") {
      return FALSE;
    }
    foreach ($badch as $bad) {
      if (strpos($str, $bad) !== FALSE) {
        return TRUE;
      }
    }
    return FALSE;
  }
  /**
   * @param array $array the array to be converted
   * @param string? $rootElement if specified will be taken as root element, otherwise defaults to
   *                <root>
   * @param SimpleXMLElement? if specified content will be appended, used for recursion
   * @return string XML version of $array
   */
  function arrayToXml($array, $rootElement = null, $xml = null) {
    $_xml = $xml;
    if ($_xml === null) {
      $_xml = new SimpleXMLElement($rootElement !== null ? $rootElement : '<DATASET/>');
    }
     
    foreach ($array as $k => $v) {
      if (is_array($v)) { //nested array
        self::arrayToXml($v, strtoupper($k), $_xml->addChild($k));
      } else {
        $_xml->addChild(self::xmlsafe(strtoupper($k)), self::xmlsafe($v,1));
      }
    }
     
    return $_xml->asXML();
  }
  function xmlsafe($s,$intoQuotes=0) {
    if ($intoQuotes)
      return str_replace(array('&','>','<','"','-',','), array('&amp;','&gt;','&lt;','&quot;', '',''), $s);
    // SAME AS htmlspecialchars($s)
    else
      return str_replace(array('&','>','<',')','(',' ','%','/',','), array('&amp;','&gt;','&lt;','','','_','percent','','_'), $s);
    // SAME AS htmlspecialchars($s,ENT_NOQUOTES)
  }

  function array_to_csv($array, $header_row = true, $col_sep = ",", $row_sep = "\n", $qut = '"')
  {
    if (!is_array($array) or !is_array($array[0])) return false;
    $output ='';
    //Header row.
    if ($header_row)
    {
      foreach ($array[0] as $key => $val)
      {
        //Escaping quotes.
        $key = str_replace($qut, "$qut$qut", $key);
        $output .= "$col_sep$qut$key$qut";
      }
      $output = substr($output, 1)."\n";
    }
    //Data rows.
    foreach ($array as $key => $val)
    {
      $tmp = '';
      foreach ($val as $cell_key => $cell_val)
      {
        //Escaping quotes.
        $cell_val = str_replace($qut, "$qut$qut", $cell_val);
        $tmp .= "$col_sep$qut$cell_val$qut";
      }
      $output .= substr($tmp, 1).$row_sep;
    }
     
    return $output;
  }
  public function getColLetter ($i) {
    $COLS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $ct = ($i > 25) ? floor($i / 26) : 0;
    $ret = $COLS[$i % 26];
    while ($ct--)
      $ret .= $ret;
      return $ret;
  }
  
  public function getWorkbooks($url, $type = 'auto') {
    include 'PHPExcel/IOFactory.php';
    $inputFileName = self::loadRemoteFile($url);
    if (!is_array($inputFileName)) {
      ($type == 'auto') ? $type = self::validate_file_info($url, TRUE): $type = self::_get_file_mime($type);
      if ( in_array($type, array('application/vnd.ms-excel', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'))) {
        $objPHPExcel = PHPExcel_IOFactory::load($inputFileName);
        $loadedSheetNames = $objPHPExcel->getSheetNames();
        $json_obj = new stdClass();
        $html = "<ul>";
        foreach($loadedSheetNames as $sheetIndex => $loadedSheetName) {
        $sheetData = $objPHPExcel->getSheet($sheetIndex)->toArray(null,true,true,true);
        if(count($sheetData) > 1){
          $base_url = $_SERVER['REQUEST_URI'];
          
          
          $param_url = $_GET['url'];
          $param_backend = $_GET['backend'];
          
          
          
          $html .= '<li><a href="?url=' . $param_url . '&backend=' . $param_backend . '&worksheet=' . $sheetIndex . '">' . $loadedSheetName . '</a></li>';
        }
        }
        $html .= "</ul>";
        $json_obj->msg = $html;
        return $html;
      }
      else{
        $json_obj = new stdClass();
        $json_obj->msg = "No worksheet";
        $html = "No worksheet";
        return $html;
      }
    }
    else {
      return $inputFileName['Message'];
    }
  }
  public function createDataset($url, $format = 'jsonp', $callback = 'callback', $worksheet = 0, $type = 'auto') {
    include 'PHPExcel/IOFactory.php';
    $inputFileName = self::loadRemoteFile($url);
    if (!is_array($inputFileName)) {
      ($type == 'auto') ? $type = self::validate_file_info($url, TRUE): $type = self::_get_file_mime($type);
      if ( in_array($type, array('text/plain', 'application/vnd.ms-excel', 'text/csv','application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'))) {
        $objPHPExcel = PHPExcel_IOFactory::load($inputFileName);
        $objPHPExcel->setActiveSheetIndex($worksheet);
        $sheetData = $objPHPExcel->getActiveSheet()->toArray(null,true,true,true);
        $fields_array = array_slice($sheetData, 0, 1);
        $data_array = array_slice($sheetData, 1);
        if ($format == 'json' || $format =='jsonp') {
          foreach($fields_array as $value){
            foreach($value as $field) {
              $fields[] = $field;
            }
          }
          foreach($data_array as $value){
            if(!empty($data_temp)) $datas[] = $data_temp;
            $data_temp =array();
            foreach($value as $data) {
              $data_temp[] = $data;
            }
          }
        }
        else if ($format == 'xml') {
          foreach($fields_array as $value){
            foreach($value as $field) {
              $fields[] = $field;
            }
          }
          $row_no = 0;
          foreach($data_array as $value){
            $row_key = "ROW".$row_no;
            if(!empty($data_temp)) $datas[$row_key] = $data_temp;
            $data_temp =array();
            $i = 0;
            foreach($value as $data) {
              $key = $fields[$i];
              $data_temp[$key] = $data;
              $i++;
            }
            $row_no++;
          }
        }
        else if ($format == 'csv') {
          foreach($fields_array as $value){
            foreach($value as $field) {
              $fields[] = $field;
            }
          }
          foreach($data_array as $value){
            if(!empty($data_temp)) $datas[] = $data_temp;
            $data_temp =array();
            $i = 0;
            foreach($value as $data) {
              $key = $fields[$i];
              $data_temp[$key] = $data;
              $i++;
            }
          }
        }
      }
      else if ( in_array($type, array('text/xml', 'application/atom+xml','application/xml'))) {
        $xml = simplexml_load_file($inputFileName);
        foreach($xml as $value){
          $fields = array();
          foreach($value[0] as $key => $field) {
            $fields[] = $key;
          }
        }
        foreach($xml as $value){
          $datas[] = (array) $value;
        }
      }
      // Now process the file as per file type
      switch($format) {
        case 'json':
          $json_obj = new stdClass();
          $json_obj->url = $url;
          $json_obj->fields = $fields;
          $json_obj->data = $datas;
          header("Content-type:text/html;");
          header("X-Frame-Options: deny");
          echo json_encode($json_obj);
          break;
        case 'jsonp':
          $json_obj = new stdClass();
          $json_obj->url = $url;
          $json_obj->fields = $fields;
          $json_obj->data = $datas;
          header("Content-type:text/html;");
          $field = $callback . '('.json_encode($json_obj).')';
          header("X-Frame-Options: deny");
          echo $field;
          break;
        case 'xml':
          $xml =  self::arrayToXml($datas);
          header("content-type: application/xml");
          header("Content-Disposition:attachment;filename=datafile.xml");
          header("X-Content-Type-Options: nosniff");
          header("X-Frame-Options: deny");echo $xml;
          break;
        case 'csv':
          $csv =  self::array_to_csv($datas, TRUE);
          header("Content-type:application/csv;");
          header("Content-Disposition:attachment;filename=datafile.csv");
          header("X-Content-Type-Options: nosniff");
          header("X-Frame-Options: deny");echo $csv;
          break;
        case 'xls':
          if ( !in_array($type, array('text/plain', 'application/vnd.ms-excel', 'text/csv', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'))) {
          $objPHPExcel = new PHPExcel();
          $objPHPExcel->setActiveSheetIndex($worksheet);
          $activeSheet = $objPHPExcel->getActiveSheet();
          foreach ($fields as $i=>$col) {
            $activeSheet->setCellValue(self::getColLetter($i) . 1, $col);
           }
           $row = 1;
          foreach ($datas as $value) {
            $row++;
            $column = 0;
            foreach ($value as $data) {
              $activeSheet->setCellValue(self::getColLetter($column) . $row, $data);
              $column++;
            }
          }
          }
          else
          {
            $objPHPExcel->setActiveSheetIndex($worksheet);
          }
          header('Content-Type: application/vnd.ms-excel');
          header("Content-Disposition:attachment;filename=datafile.xls");
          header("X-Content-Type-Options: nosniff");
          header("X-Frame-Options: deny");
          $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
          $objWriter->save('php://output');
          break;
      case 'xlsx':
        if ( !in_array($type, array('text/plain', 'application/vnd.ms-excel', 'text/csv', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'))) {
        /** PHPExcel_Writer_Excel2007 */
        include 'PHPExcel/Writer/Excel2007.php';
        $objPHPExcel = new PHPExcel();
        $objPHPExcel->setActiveSheetIndex(0);
        $activeSheet = $objPHPExcel->getActiveSheet();
        foreach ($fields as $i=>$col) {
          $activeSheet->setCellValue(self::getColLetter($i) . 1, $col);
        }
        $row = 1;
        foreach ($datas as $value) {
          $row++;
          $column = 0;
          foreach ($value as $data) {
            $activeSheet->setCellValue(self::getColLetter($column) . $row, $data);
            $column++;
          }
        }
        }
        else
        {
          $objPHPExcel->setActiveSheetIndex($worksheet);
        }
        header('Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet');
        header("Content-Disposition:attachment;filename=datafile.xlsx");
        header("X-Content-Type-Options: nosniff");
        header("X-Frame-Options: deny");
        $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
        $objWriter->save('php://output');
        break;
      case 'pdf':
        if ( !in_array($type, array('text/plain', 'application/vnd.ms-excel', 'text/csv', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'))) {
          $objPHPExcel = new PHPExcel();
          $objPHPExcel->setActiveSheetIndex($worksheet);
          $activeSheet = $objPHPExcel->getActiveSheet();
          foreach ($fields as $i=>$col) {
            $activeSheet->setCellValue(self::getColLetter($i) . 1, $col);
          }
          $row = 1;
          foreach ($datas as $value) {
            $row++;
            $column = 0;
            foreach ($value as $data) {
              $activeSheet->setCellValue(self::getColLetter($column) . $row, $data);
              $column++;
            }
          }
        }
        else
        {
          $objPHPExcel->setActiveSheetIndex($worksheet);
        }
        header('Content-Type: application/pdf');
        header("Content-Disposition:attachment;filename=datafile.pdf");
        header("X-Content-Type-Options: nosniff");
        header("X-Frame-Options: deny");
        $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'PDF');
        $objWriter->save('php://output');
        break;
      case 'html':
        if ( !in_array($type, array('text/plain', 'application/vnd.ms-excel', 'text/csv', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet'))) {
          $objPHPExcel = new PHPExcel();
          $objPHPExcel->setActiveSheetIndex($worksheet);
          $activeSheet = $objPHPExcel->getActiveSheet();
          foreach ($fields as $i=>$col) {
            $activeSheet->setCellValue(self::getColLetter($i) . 1, $col);
          }
          $row = 1;
          foreach ($datas as $value) {
            $row++;
            $column = 0;
            foreach ($value as $data) {
              $activeSheet->setCellValue(self::getColLetter($column) . $row, $data);
              $column++;
            }
          }
        }
        else
        {
          $objPHPExcel->setActiveSheetIndex($worksheet);
        }
        header('Content-Type: text/html');
        header("Content-Disposition:attachment;filename=datafile.html");
        header("X-Content-Type-Options: nosniff");
        header("X-Frame-Options: deny");
        $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'HTML');
        $objWriter->setActiveSheetIndex(1);
        $objWriter->save('php://output');
        break;
      }
      
    }
    else {
      return $inputFileName['Message'];
    }
  }
}



?>