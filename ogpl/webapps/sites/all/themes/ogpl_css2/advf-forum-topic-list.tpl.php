<?php 
$name = 'forum_active_topicd';
$display_id = 'block_1';
$args = array($topic_id);
function _views_embed_view($name, $display_id = 'default', $args) {
  $view = views_get_view($name);
  return $view->preview($display_id, $args);
}
$output = _views_embed_view($name, $display_id , $args);
print $output;
?>