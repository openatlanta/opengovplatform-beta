
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
?><table class="<?php print $class; ?> header-width "
  <?php print $attributes; ?> style="clear: both;">
	<?php if (!empty($title)) : ?>
	<caption>
		<?php print $title; ?>
	</caption>
	<?php endif; ?>
<thead>
    <tr>
      <?php foreach ($header as $field => $label): ?>
        
          <?php  
		  if($field=='phpcode_1')
		  { print ' <th class="views-field views-field-'.$fields[$field].' ds-list-head-new-first">';
		    print $label;} 
		  else if($field=='title')
		  { print ' <th class="views-field views-field-'.$fields[$field].' ds-list-head-new" style="width:450px;">';
		    print $label;} 
		  else if($field=='field_ds_sector_nid')
		   { 
		     print ' <th class="views-field views-field-'.$fields[$field].' ds-list-head-new-last" style="width:160px;">';
		     print $label;
			} 
		  else 
		  { 
		     print ' <th class="views-field views-field-'.$fields[$field].' ds-list-head-new " style="text-align:center; padding-left: 0; " >';
		     print $label;
			} 
		  ?>
        </th>
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($rows as $count => $row): ?>
      <tr class="<?php print implode(' ', $row_classes[$count]); ?> ds-list-item-new">
        <?php foreach ($row as $field => $content): 
			      if($field=='title'||$field=='field_ds_sector_nid')
              print '<td class="views-field views-field-'.$fields[$field].'">';
      			else
      			  print '<td class="views-field views-field-'.$fields[$field].' ds-list-item-new-center ">';
			    ?>
			    <?php print $content; ?>
        </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>