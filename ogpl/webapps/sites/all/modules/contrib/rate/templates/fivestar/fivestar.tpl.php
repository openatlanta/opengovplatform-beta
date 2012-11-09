<?php 
/**
 * @file
 * Rate widget theme
 */
if ($display_options['description']) {
	print '<div class="rate-description">' . $display_options['description'];
}
	print theme('item_list', $stars);
	if ($info) {
	  print '<div class="rate-info">' . $info . '</div>';
	}
	
	if($display_options['description']=='Usability')
	{
		?>
	  
	  <?php 
		$delay_time_seconds = variable_get('votingapi_anonymous_window', 86400);
		if($delay_time_seconds > 0 ){ 
	?>
			<br/>  
				<?php $map = drupal_map_assoc(array(300, 900, 1800, 3600, 10800, 21600, 32400, 43200, 86400, 172800, 345600, 604800), 'format_interval');?>
			
	<?php
		} else if ($delay_time_seconds == -1) { ?>
			<br/> 
				<?php 
					print "<span class='ratings-note'>Note: You are allowed to rate this content only once.</span>";
				?>
			
		
	<?php }?>
	 <?php
	}
	
	?>


