<?php
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $class: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * @ingroup views_templates
 */

$view = views_get_current_view();
$arg0 = $view->args[0];

$maxDepth = 3;

$cat = array(
    'phpcode_2'     => array('name' => 'catalog_type_raw_data', 'value' => array('val' => 1),
        'v_count' => array('value' => 0 , 'name' => 'phpcode_8'),
        'hv_count' => array('highvalue' => 0 , 'name' => 'phpcode_9')
    ),
    'phpcode_3'   => array('name' => 'catalog_type_document', 'value' => array('val' => 0)),
    'phpcode_4'   => array('name' => 'catalog_type_data_apps', 'value' => array('val' => 1),
        'v_count' => array('value' => 0 , 'name' => 'phpcode_10'),
        'hv_count' => array('highvalue' => 0 , 'name' => 'phpcode_11')
    ),
    'phpcode_5'   => array('name' => 'catalog_type_data_tools', 'value' => array('val' => 0), 'count' => array('v' => 0 , 'hv' => 0)),
    'phpcode_6'   => array('name' => 'catalog_type_data_service', 'value' => array('val' => 0), 'count' => array('v' => 0 , 'hv' => 0))
);

/*
foreach($rows as $row) {
  foreach($cat as $pc => $arr) {
    if($row[$pc] != 0){
      $cat[$pc]['value']['val'] = $row[$pc];
    }
  }
}
*/

/*
 * Add row ID as index to array
*/
foreach($rows as $row) {
  $data[$row[phpcode]] = $row;
}

/*
 * Rearrange the array as parent child tree structure
*/
for($i = 0; $i < $maxDepth; $i++){
  agency_name_arrange_child(&$data, 'phpcode_1');
}

agency_name_remove_child(&$data, 'phpcode_1');

?>

<table class="<?php print $class; ?> header-width "
<?php print $attributes; ?> style="clear: both;">
	<?php if (!empty($title)) : ?>
	<caption>
		<?php print $title; ?>
	</caption>
	<?php endif; ?>
	<thead>
		<tr>
			<?php 
			foreach ($header as $field => $label):
			if( $field!='phpcode' && $field!='phpcode_1' && $field!='phpcode_8' && $field!='phpcode_9' && $field!='phpcode_10' && $field!='phpcode_11')
			{
			  if($field=='title')
			  {
			    print '<th class="views-field views-field-'. $fields[$field].
			    '  ds-list-head-new ds-list-head-top-left twoline-sort " style="width:210px; ">';
			    print $label;
			  }
			  else if($field!='name' && $field!='changed' && $field!='phpcode_7')
			  {
			    if($cat[$field]['value']['val'] != 0) {
  			    print '<th class="views-field views-field-'. $fields[$field].
  			    '  ds-list-head-new" style="text-align:center;">';
  			    print $label.'<br/>(high-value)';
			    }
			  }
			  else
			  {
			    print '<th class="views-field views-field-'. $fields[$field].
			    '  ds-list-head-new ds-list-head-top-right " style="text-align:center; width:85px;">';
			    print $label;
			  }
			}
			?>
			</th>
			<?php 
			endforeach;
			?>
		</tr>
	</thead>
	<tbody>
		<?php 
		function printRow($row, $fields, $cat, $child = 0){
  	  foreach ($row as $field => $content):
  	  if( $field!='phpcode' && $field!='phpcode_1' && $field!='phpcode_8' && $field!='phpcode_9' && $field!='phpcode_10' && $field!='phpcode_11')
  	  {
  	    if($field!='name') {
          if($cat[$field]['value']['val'] != 0 || $field == 'changed' || $field=='phpcode_7') {
    	      print '<td class="views-field views-field-'. $fields[$field].' " style="text-align:center; ">';
    	      print $content;
    	      print '</td>';
  	      }
  	    } else {
  	      print '<td class="views-field views-field-'. $fields[$field].' " style="'.($child > 0?'padding-left:'.(20*$child).'px;':'').' ">';
    	    print $content;
    	    print '</td>';
    		}
  	  }
  	  endforeach;
    }

    function printTable($data, $fields, $row_classes, $cat, $child = 0){
      foreach ($data as $count => $row):
      ?>
		<tr
			class="
  			ds-list-item-new level-<?php print $child;?> 
  			<?php /* print ($child == 0?'ds-list-item-new':''); */ ?> ">
			<?php 
			printRow($row, $fields, $cat, $child+1);
			if(!empty($row['child'])){
            ?>
		</tr>
		<?php 
		printTable($row['child'], $fields, $row_classes , $cat, $child+1);
          } else {
            ?>
		</tr>
		<?php 
          }
          endforeach;
    }

    printTable($data, $fields, $row_classes, $cat);

    /*
     * Calculate total
    * */
    $total_cal = array();
    foreach ($data as $count => $row):
    foreach ($row as $field => $content):
    if($field == 'phpcode_8'){
          $total_cal['dataset'] +=  (int)$content;
          $total_cal['value'] += (int)$content;
        }
        if($field == 'phpcode_9'){
          $total_cal['dataset_high'] +=  (int)$content;
          $total_cal['highvalue'] += (int)$content;
        }

        if($field == 'phpcode_10'){
          $total_cal['app'] +=  (int)$content;
          $total_cal['value'] += (int)$content;
        }
        if($field == 'phpcode_11'){
          $total_cal['app_high'] +=  (int)$content;
          $total_cal['highvalue'] += (int)$content;
        }

        endforeach;
        endforeach;

        ?>
		<tr>
			<td class="ds-list-head-new  ds-list-head-btm-left"
				style="padding-left: 20px;">Total</td>
			<td class="ds-list-item-new-summary"><?php print $total_cal['dataset'] ;?>
				<?php 
				if($total_cal['dataset_high']){
            print '(' . $total_cal['dataset_high'] . ')' ;
          }
          ?>
			</td>
			<td class="ds-list-item-new-summary"><?php print $total_cal['app'] ;?>
				<?php 
				if($total_cal['app_high']){
            print '(' . $total_cal['app_high'] . ')' ;
          }
          ?>
			</td>
			<td class="ds-list-item-new-summary"><?php print $total_cal['value'] ;?>
				<?php 
				if($total_cal['highvalue']){
            print '(' . $total_cal['highvalue'] . ')' ;
          }
          ?>
			</td>
			<td class="ds-list-item-new-summary ds-list-head-btm-right ">&nbsp;</td>
		</tr>
	</tbody>
</table>


<div
	id="metrics-color-notation">
	<div class="ministry-notation-box"></div>
	<div class="ministry-notation-text">Ministry = Ministry + &#x2211;
		(Department)</div>
	<div class="department-notation-box"></div>
	<div class="department-notation-text">Department = Department +
		&#x2211; (Organization)</div>
	<div class="organization-notation-box"></div>
	<div class="organization-notation-text">Organization</div>
	<!-- <div class="department-cal">Department = Department + &#x2211; (Organization)</div>
 	<div class="ministry-cal">Ministry = Ministry + &#x2211; (Department)</div>  -->
</div>
<!-- <div class="metrics-visitorstats-table-heading"><p>Summary</p></div> -->
