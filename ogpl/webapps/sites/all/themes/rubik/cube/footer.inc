  <hr class="footer-hr"></hr>
  <div id='footer' class='limiter clear-block'>
	  <div class="footer-admin-poweredby">
  		<a href="<?php echo variable_get('powerby_image_url', NULL); ?>" alt="<?php echo variable_get('powerby_title', NULL); ?>" target="_blank">
	 		<img title="<?php echo variable_get('powerby_title', NULL); ?>" src="<?php echo variable_get('powerby_image', NULL); ?>" />
		</a>
  	  </div>
    <?php 
    if ($feed_icons || $footer_message): ?>
    <?php if ($feed_icons): ?>
      <div class='feed-icons clear-block'>
        <label><?php print t('Feeds') ?></label>
        <?php print $feed_icons ?>
      </div>
    <?php endif; ?>
    <?php if ($footer_message): ?><div class='footer-message'><?php print $footer_message ?></div><?php endif; ?>
  </div>
  <?php endif; ?>

  <?php print $closure ?>

  </body>
</html>
