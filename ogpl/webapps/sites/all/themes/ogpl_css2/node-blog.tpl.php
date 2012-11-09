<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

  <?php print $picture ?>
  <?php if ($submitted): ?>
  <span class="submitted"><?php print $submitted; //print format_date($node->created, 'custom', "d.m.Y"); ?></span>
  <?php endif; ?>

  <div class="content">
    <?php print $content ?>
  </div>
  <?php if ($links) { ?><div class="links">&raquo; <?php print $links?></div><?php }; ?>
  <div class="terms"><span>Tags:</span><?php print $terms; ?></div>
</div>