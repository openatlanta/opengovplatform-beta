<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">
	<?php print $picture ?>
	<div class="content">
	<div class="feedback">
		<div class="fieldgroup">
			<div class="field">
				<div class="field-label">Submitted On: </div>
				<div class="field-items"><div class="field-item"><?php print format_date($node->created, 'small'); ?></div></div>
			</div>
			
			
			<div class="field">
				<div class="field-label">Sender Name: </div> 
				<?php if($node->field_sender_name[0]['safe']) : ?>
					<div class="field-items"><div class="field-item"><?php print $node->field_sender_name[0]['safe']; ?></div></div>
				<?php else :?>
					<div class="field-items"><div class="field-item">Anonymous</div></div>
				<?php endif;?>	
			</div>
			
			
			<?php if($node->field_feedback_body[0]['view']) : ?>
				<div class="field">
					<div class="field-label">Suggestion: </div>
					<div class="field-items"><div class="field-item"><?php print nl2br($node->field_feedback_body[0]['view']); ?></div></div>
				</div>
			<?php endif;?>
				<?php  
				if ((arg(0) == 'node') && is_numeric(arg(1))) :
				
				$tag = variable_get('vud_tag', 'vote');
		  		$widget = variable_get('vud_node_widget', 'plain');
		  		$output .= theme('vud_widget', arg(1), 'node', $tag, $widget);?>
				<div class="field">
					<div class="field-label">Endorse: </div>
					<div class="field-items"><div class="field-item"><?php print $output; ?></div></div>
				</div>
				<?php endif; ?>
		</div>
	
	</div>
	
    </div>
</div>