<?php 
  $validator_flag = false;
  
  if($validator_wf = dms_customizations_get_dataset_validator_details($node->nid)) {
    $validator_flag = true;
    if($_GET['debug'] == 'validator') {
      print '<pre>' . print_r($validator_wf, true) . '</pre>';
    }
  } 
  
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>" >
<?php global $base_url;?>    
    <?php print $picture ?>
    <?php 
  	drupal_add_js(drupal_get_path('module', 'clientside_validation') . '/jquery-validate/jquery.validate.js');
  	drupal_add_js(drupal_get_path('theme', 'ogpl_css2') . '/js/validation.js');	
  	?>	
    <?php
   	global $base_path;
    function embedURL() {
		global $base_path;
		$pageURL = 'http';
        if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
        $pageURL .= "://";
		$pageURL .= $_SERVER["SERVER_NAME"].$base_path;
        $pageURL .= 'embed-preview/';
        return $pageURL;
    }
	
	function get_string_between($string, $start, $end){
   	 $string = " ".$string;
   	 $ini = strpos($string,$start);
   	 if ($ini == 0) return "";
   	 $ini += strlen($start);
   	 $len = strpos($string,$end,$ini) - $ini;
   	 return substr($string,$ini,$len);
	}
    ?>
    <?php /*if ($submitted): ?>
    <span class="submitted"><?php print $submitted; //print format_date($node->created, 'custom', "d.m.Y"); ?></span>
    <?php endif;*/ 
	
	/*MARK NODE FOR INDEXING */
	 apachesolr_mark_node($node->nid);
	
	?>
  <div class="cBoth"></div>
    <div class="content">
		<div class="dataset">
    <?php 
  			$args = array($node->nid);
  			function _views_embed_view($name, $display_id = 'default', $args) {
  			  $view = views_get_view($name);
  			  return $view->preview($display_id, $args);
  			}
  			?>
  			<div class="pane-dataset basic-info">
  			<h2>Basic Info</h2><?php 
  			  if(empty($_GET['embed']) && empty($_GET['print'])){
  			    print _views_embed_view('dataset', 'block_1', $args);
  			  } else {
            print _views_embed_view('dataset', 'block_4', $args);
          }
  			?></div>
  			<div class="pane-dataset more-info">
  			<h2>More Info</h2><?php 
  			  if(empty($_GET['embed']) && empty($_GET['print'])){
  			    print _views_embed_view('dataset', 'block_2', $args);
  			  } else {
  			    print _views_embed_view('dataset', 'block_5', $args);
  			  }
  			?></div>
  			<div class="pane-dataset contact-info">
  			<h2>Contact</h2><?php 
  			  $uid_args = array($validator_wf->uid);
  			  if(empty($_GET['embed']) && empty($_GET['print'])){
  			    print _views_embed_view('dataset', 'block_3', $uid_args);
  			  } else {
  			    print _views_embed_view('dataset', 'block_6', $uid_args);
  			  }
  			?></div>
		</div>
		<div style="clear:both;"></div>
    </div>
    <?php if(empty($_GET['embed'])&& empty($_GET['print'])){ ?>
    <div class="content-bottom">
	    <div id="tabs-block" class="js-disable-hide">
			<ul class="list">
				<li class="ratings first active" title="Rate this dataset">Ratings</li>
				<li class="embed" title="Embed this dataset">Embed</li>		
        <li class="discuss" title="Discuss this dataset">Discuss</li>
        <li class="contactOwner last" title="Write to Data Controller">Write to Data Controller</li>				
			</ul>	
		</div>
			<div style="clear:both;"></div>
		<div class="messages error clientside contactOwnerError" id="web-contact-owner-form-errors" style="display: none;"><ul><li style="display:none">No Errors</li></ul></div>
		<div class="messages error clientside ratingsError" id="ratings-form-errors" style="display: none;"><ul><li style="display:none">No Errors</li></ul></div>
		<div class="messages error clientside commentsError" id="comment-form-errors" style="display: none;"><ul><li style="display:none">No Errors</li></ul></div>
		<div class="js-disable-show">Embed</div>
	    <form name="embed-form" action="<?php echo $base_url.'/'?>embed_preview" method="post" target="_new">
		    <div class="tabs-cont embed-block">
			    <div class="textblock">
					  <label for="embed_code" style="display:none">Embed code</label>
					  <div class="head"><?php echo t('Include this code on your website');?></div>
            <textarea rows="5" cols="60" class="textbx" name="embed_code" id="embed_code"><div><iframe width="500px" title="<?php echo $node->title; ?>" height="425px" src="<?php echo embedURL().$node->path; ?>" frameborder="1" scrolling="auto"></iframe></div></textarea>
			    </div>    
			    <div class="econf-block">
			        <div style="float:right;">
			            <div class="head">Size</div>
			                <div class="block">    
			                    <p class="size-large">950x808</p>
			                    <p class="size-medium">760x646</p>
			                    <p class="size-small">500x425</p>
			                    <p style="clear:both;margin:0px;"></p>
			                    <div id="large" class="large iframe-dimensions" title="950x808">&nbsp;</div>
			                    <div id="medium" class="medium iframe-dimensions" title="760x646">&nbsp;</div>
			                    <div id="small" class="small iframe-dimensions" title="500x425">&nbsp;</div>
			                 </div>
			             </div>
			         <div style="float:left;">
			             <div class="head">Custom Size</div>
			             <div class="block">    
			       			 <label for="ewidth">Width: </label>
			                 <input type="text" name="ewidth" value="500" id="ewidth" class="custom-size" />
			                 <div style="clear:both">&nbsp;</div>
			                 <label for="eheight">Height: </label>
			                 <input type="text" name="eheight" value="425" id="eheight" class="custom-size" />
			                 <div style="clear:both">&nbsp;</div>
			                 <div class="min-text">425x425 is the minimum size</div>
			             </div>
			         </div>
			         <div style="clear:both">&nbsp;</div>
			         <input type="submit" class="form-submit" name="preview" value="Preview" id="preview" title="Click here to preview" />
			         <input type="hidden" name="embed-url" title="embed-url-hidden" value="<?php print htmlspecialchars($node->path); ?>" />
			         <input type="hidden" name="js-embed-url" class="hidden-embed-url" title="embed-url-hidden" value="<?php echo embedURL().$node->path; ?>" />
			         <input type="hidden" name="embed-title" title="embed-title-hidden" value="<?php echo $node->title; ?>" />
			    </div>
			</div>
		</form>
		<div class="clear-block clear" style="clear: both;">
			<?php if ($links): ?>
			<div class="js-disable-show element-properties">Rating</div>
			<div class="links ratings-block">
				<?php print $links; ?>
				<div class="clear-block clear" style="clear: both;"></div>
				<?php endif; ?>
			</div>
		</div>
	</div>
<?php } ?>
<style type="text/css">
	#node-form {padding: 15px;}
	#node-form label{padding: 0 0 5px;}
	#node-form #edit-submit{border: 1px solid #999999;font-size: 1.4em;}
</style>
<script type="text/javascript">
$(".field-item").each(function(){
	if($(this).find('.field').size() > 0){
		var htmlcontent = $(this).html();
		var pObj = $(this).parent().parent();
		$(pObj).removeClass('field');
		$(pObj).attr('innerHTML',htmlcontent);
	}
});

$(".field-item").each(function(){
	if($(this).find('.field').size() > 0){
		var htmlcontent = $(this).html();
		var pObj = $(this).parent().parent();
		$(pObj).removeClass('field');
		$(pObj).attr('innerHTML',htmlcontent);
	}
});


$(".fieldgroup").each(function(){
	$(this).find('.field:last').css('border','none');
});

$("#print-icon").hover(function(){
	$(this).css('opacity','0.8');
	$(this).css('filter','alpha(opacity=80)');
},function(){
	$(this).css('opacity','1');
	$(this).css('filter','alpha(opacity=100)');
});
$(document).ready(function() {
	$("span.qr-alt").hide();
	  $("#qr-icon").mouseover(function (){
			$(this).parent().find('span').show();   
	   });
		$("#qr-icon").mouseout(function (){
			$(this).parent().find('span').hide();   
	   });
	});
<?php if($_GET['print']){ ?>
$(window).bind('load',function(){
	if (typeof(window.print) != 'undefined') {
        window.print();
    }
});
<?php } ?>
</script>
</div>