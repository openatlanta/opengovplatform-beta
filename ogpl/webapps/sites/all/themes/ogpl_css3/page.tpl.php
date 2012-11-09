<?php
    global $base_url;
	global $user;
	$access_denied = 0;	
	$admin_page_urls = variable_get('admin_pages_list', '');
 
	if(in_array(drupal_get_path_alias($_GET['q']), explode("\r\n", $admin_page_urls)) && in_array('anonymous user', $user->roles)){
		$access_denied = 1;
		$head_title = "Access Denied";
	}
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">
<head>
<meta http-equiv="X-UA-Compatible" content="IE=8" />
<meta http-equiv="content-language" content="<?php echo $language->language;?>" />
<title><?php print $head_title ?></title>
<?php print $head ?>
<?php print $styles ?>
<?php print $scripts; ?>
<!--[if gte IE 9]>
  <style type="text/css">
    .gradient {
       filter: none;
    }
  </style>
<![endif]-->
</head>
<?php if(empty($_GET['embed'])&& empty($_GET['print'])){ ?>
<body class="innerPages <?php print ($node->type=='dataset'?'dataset-page':''); ?>" role="application" >
	<span>
		<a class="skipnav" accesskey="1" href="#mainNav">Skip to navigation</a>
		<a class="skipnav" accesskey="2" href="#mainContent">Skip to main content</a>
	</span>
	
	
<div id="outerContainer">	
	<div id="mainContainer">
    	
        <?php include ('include/header.tpl.php') ;?>
        
        
        
        
        <!--blocks panel start here -->
		<div id="mainContent" role="main">
			<div id="contentPanel">	
				<?php
			if($access_denied == 1) {
				echo '<div class="containers"><h1 class="page-title">'.t('Access denied').'</h1><div class="page-title-border"></div>'
					.'<div class="access-denied-error">'.t('You are not authorized to access this page.').'</div></div>';
			} else {
			?>
            	<div class="containers">
				<?php if ($metrics_menu){ print '<div class="metrics-menu">'. $metrics_menu .'<div class="page-title-border"></div></div>';}else{ ?>
				<?php if ($title){ 
				switch(strtolower($title)) {
					case 'contact':
						$title = "Contact Us"; break;
					default: break;
				}
				print '<h1'. ($tabs ? ' class="page-title"' : '') .'>'. $title .'</h1>';
				$uri1 = strrpos($_SERVER["REQUEST_URI"], "datasets-agency");
				$uri2 = strrpos($_SERVER["REQUEST_URI"], "agency-publications-month");
				$uri3 = strrpos($_SERVER["REQUEST_URI"], "datasets-per-month-year");
				
				if($uri1===false && $uri2===false && $uri3===false)
				print '<div class="page-title-border">&nbsp;</div>';} }?>
				<?php //if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul>'; endif; ?>
          		<?php //if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
				<?php print $messages; ?>
				<?php if ($search_filter){ print'<div class="small-catalog-panel">'.$search_filter.'</div>';}?>
				<?php print $content;?>
				<?php
                if($node->type=='dataset')  {
                    print '<div id="suggest-cp-block"><div style="text-align:center;margin-right:20px;" class="suggest-cp">';	  
                    print '<div class="suggest-label">Didn`t find what you are looking for? Would like to inform/suggest?  <a href="'.$base_url.'/suggest_dataset?nid='.$node->nid.'" title="Click here to suggest dataset" >Suggest</a></div></div></div>';
                }
                ?>
				</div>
				<?php } ?>
			</div>
        </div>
        <!--blocks panel end here -->
        
        <?php include ('include/footer.tpl.php') ;?>
        
        
</div> 	<!-- outerContainer div ends here -->
<script type="text/javascript">
<!--//--><![CDATA[//><!--
userAgentLowerCase = navigator.userAgent.toLowerCase();
 
function resizeTextarea(t) {
	
  if ( !t.initialRows ) t.initialRows = t.rows;
  a = t.value.split('\n');
  b=0;
  for (x=0; x < a.length; x++) {
	if (a[x].length >= t.cols) b+= Math.floor(a[x].length / t.cols);
  }
  b += a.length;
  if (userAgentLowerCase.indexOf('opera') != -1) b += 2;
 
  if (b > t.rows || b < t.rows)
	t.rows = (b < t.initialRows ? t.initialRows : b);
	
}

$("#edit-recipients").attr('rows',3);
$("#edit-recipients").keyup(function(){
		resizeTextarea(document.getElementById('edit-recipients'));

});

$("#edit-recipients").mouseout(function(){
		resizeTextarea(document.getElementById('edit-recipients'));

});
//--><!]]>
</script>


</body>
<?php
print $closure;
?>

    <?php } else { ?>
<body class="innerPages embed-code">
    <div id="mainContent">
        <div id="contentPanel">
            <div class="containers">
            <?php if ($metrics_menu){ print '<div class="metrics-menu">'. $metrics_menu .'<div class="page-title-border"></div></div>';}else{ ?>
            <?php if ($title){ 
            switch(strtolower($title)) {
                case 'contact':
                    $title = "Contact Us"; break;
                    default: break;
                }
            print '<h1'. ($tabs ? ' class="page-title"' : '') .'>'. $title .'</h1><div class="page-title-border">&nbsp;</div>';} }?>
            <?php if ($show_messages && $messages): print $messages; endif; ?>
            <?php if ($search_filter){ print'<div class="small-catalog-panel">'.$search_filter.'</div>';}?>
            <?php print $content;?>
            <?php
				if(empty($_GET['print'])){
					print '<div class="embed-feature-links">';
					print '<div class="fLeft"><a class="embeded-link discuss" target="_blank" href="">Write to Data Controller</a></div>';
					print '<div class="fLeft"><a class="embeded-link rating" target="_blank" href="">Rating</a></div>';
					print '<div class="fLeft"><a class="embeded-link suggest-dataset-link" target="_blank" href="">Suggest Dataset</a></div>';
					print '<div class="fLeft print"><a>Print</a></div>';
					print '<div class="cBoth"></div></div>';
				}	
            ?>
            </div>
        </div>
    </div>
</body>
<?php } ?>
</html>