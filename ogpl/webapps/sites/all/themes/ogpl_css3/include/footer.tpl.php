	<!--footer link start here -->
	<div class="footerLinks" role="contentinfo">
		<?php print $footer;?>
	</div>
	<!--footer link end here -->

</div> <!-- mainContainer div ends here -->
        
	
    <div class="footerSeparator">&nbsp;</div>
    <!--footer container starts here-->
    	<div class="footerContainer">
            <!--footer sub links -->
            <div class="footerSubLinks">
				<?php print $footer_links;?>
            </div>
            <!--footer sub links -->
            
			<div class="footerContent">
                <?php if ($footer_message): ?><div class='footer-message'><?php print $footer_message ?></div><?php endif; ?>
            </div>
       </div>
     <!--footer container end here-->