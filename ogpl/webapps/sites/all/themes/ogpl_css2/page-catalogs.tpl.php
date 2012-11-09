<?php
	global $base_url;	    
	global $theme_key;
    $themes = list_themes();
    $theme_object = $themes[$theme_key];
    $site_var = variable_get('site_country','');
    $node = node_load($site_var);
	$theme_name=$theme_object->name;
   $flag_img=substr($node->field_website_header_image[0]['filepath'],strpos($node->field_website_header_image[0]['filepath'],"files/"));
 
    if(variable_get('file_downloads','') == 2) {		
		$site_img = $base_url."/system/".$flag_img;
	} else {
		$site_img = $base_url.'/'.$node->field_website_header_image[0]['filepath'];
	}
  
  $portal_url = $node->field_country_portal_url[0]['url'];
  $gov_name = $node->field_union_govt_name[0]['value'];

?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
<meta http-equiv="X-UA-Compatible" content="IE=9" >
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<?php global $base_url;?>
<title><?php print $head_title ?></title>
<?php print $head ?>
<?php print $styles ?>
<link href="<?php echo $base_url."/".path_to_theme();?>/high.css" rel="alternate stylesheet" type="text/css" media="screen" title="change" />
<?php 
//drupal_add_css($path = NULL, $type = 'theme', $media = 'all', $preprocess = TRUE);
//drupal_add_css(drupal_get_path('theme', 'nic') . 'small.css'); 
?>
<?php print $scripts; ?>
<!--[if gte IE 9]>
  <style type="text/css">
    .gradient {
       filter: none;
    }
  </style>
<![endif]-->
</head>

<body class="innerPages">
	<span>
		<a class="skipnav" href="#mainNav">Skip to navigation</a>
		<a class="skipnav" href="#mainContent">Skip to main content</a>
	</span>
	
	<?php include ('include/header.tpl.php') ;?>
	   
	
	<!--body panel start here -->
	<div id="bodyPanel">
		<div id="outerContainer">
		  <?php include ('include/nav.tpl.php') ;?>
			<a name="mainContent"></a>
			<div class="mid">
				<?php if ($search_filter){ print'<div id="leftPanel"><div class="container">'.$search_filter.'</div></div>';}?>
				<!--content panel start here -->
				<div id="contentPanel">
					<div class="mainContent">
						<!--breadcrumb start here -->
						<?php print $breadcrumb ?>
						
						<!--main heading start here -->
						<div class="mainHeading">
						<?php if ($title){ print '<h1'. ($tabs ? ' class="page-title"' : '') .'>'. $title .'</h1>';}?>
						</div>
						<!--main heading end here -->                    
						<div class="contentArea mainContainer">
							<?php include ('include/topbar.tpl.php') ;?>
							
							<!--content -->
							<div class="bottom">							
							<?php print $content;?>
							</div>
							<!--content -->
							
							<!--bottom links start here -->
							<div class="contentArea bottomLink">
								<div class="mid"></div>
								<?php print $footer;?>
							</div>
							<!--bottom links end here -->
						</div>
						
					</div>
				</div>
				<!--content panel end here -->
				<div class="clearBoth"></div>
			</div>
		</div>
		
		<!--footer starts here -->
		<?php include ('include/footer.tpl.php') ;?>
		
	</div>
	<!--body panel end here -->
	
	<?php
print $closure;
?>
</body>
</html>