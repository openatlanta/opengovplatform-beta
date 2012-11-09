<!--footer start here -->
		<div id="footer">
			<?php if(is_frontend_url()):?>
			<div class="left">
					<?php print $footer_links;?>
				<p>&copy; 2011-2012 
				<a class="india_portal_text" title="<?php echo $gov_name; ?>" href="<?php echo $portal_url; ?>" ><?php echo $gov_name; ?></a>. All rights reserved.</p>
		 	</div>
			<?php endif; ?>
			<div class="right">
				<a href="<?php echo variable_get('hostedby_image_url', NULL); ?>" title="<?php echo variable_get('hostedby_title', NULL); ?>">
					<img title="<?php echo variable_get('hostedby_title', NULL); ?>" src="<?php echo variable_get('hostedby_image', NULL); ?>" />
				</a>
			
			 	<a href="<?php echo variable_get('powerby_image_url', NULL); ?>" alt="<?php echo variable_get('powerby_title', NULL); ?>" target="_blank">
			 		<img title="<?php echo variable_get('powerby_title', NULL); ?>" src="<?php echo variable_get('powerby_image', NULL); ?>" />
				</a>
			</div>
			<div class="spacer" ></div>
		</div>
		<!--footer end here -->
		
		<!--footer start here -->
		<div id="footer2">
			<div class="footerContent">
                <?php if ($footer_message): ?><div class='footer-message'><?php print $footer_message ?></div><?php endif; ?>
                <div class="spacer" ></div>
	        </div>
		</div>
		<!--footer end here -->