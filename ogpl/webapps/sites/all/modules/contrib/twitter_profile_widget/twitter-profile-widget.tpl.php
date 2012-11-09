<?php
/**
 * @file
 * Block content template for twitter widget
 *
 * @param $twitter_script
 *   A JavaScript with widget settings *
 * @param $external_js
 *   Boolean. Shows whether include external js or not *
 * @param $follow_us_enabled
 *   Boolean. Shows whether include follow us button or not *
 * @param $follow_us_link
 *   Link to follow
 */
?>
<div class = "twitter_profile_widget">

  <?php if ($twitter_script): ?>
    <?php if ($external_js): ?>
      <script type="text/javascript" src="http://widgets.twimg.com/j/2/widget.js"></script>
    <?php endif; ?>
    <script type = "text/javascript"><?php print $twitter_script; ?></script>
  <?php endif; ?>
  
  <?php if ($follow_us_enabled): ?>
    <div class = "twp_bottom">
      <?php print $follow_us_link; ?>
    </div>
  <?php endif; ?>
  
</div>