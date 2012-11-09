<?php include('header.inc'); ?>

<div id='page' class='clear-block limiter page-content'>
  <?php if ($show_messages && $messages): ?>
    <div id='console' class='clear-block'><?php print $messages; ?></div>
  <?php endif; ?>

  <div id='content'>
  	<h1 class='page-title <?php print $page_icon_class ?>'>
        <?php if (!empty($page_icon_class)): ?><span class='icon'></span><?php endif; ?>
        <?php if ($title) print $title ?>
      </h1>
    <?php if (!empty($content)): ?>
      <div class='content-wrapper clear-block'><?php print $content ?></div>
    <?php endif; ?>
    <?php print $content_region ?>
  </div>
</div>

<?php include('footer.inc'); ?>
