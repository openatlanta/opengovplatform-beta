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
<?php print $scripts; ?>
</head>

<body class="homePage <?php echo (is_cms_url()? 'cmsHome' : ''); ?> " >
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
				<!--header panel start here -->
				<?php if(is_frontend_url()):?>
				<div id="headerPan">
					<div id="rotating-panes">
						<?php print $banner; ?>
					</div>
				</div>
				<?php endif; ?>
				<!--header panel end here -->
				
				<!--bodyPan start here -->
				<div id="bodyPan">
					<!--content panel start here -->
					<div class="contentPanel">
						<!--top blocks start here -->
						<div class="topBlocks">
						  <?php if(is_cms_url()): ?>
						    <?php print $messages;  ?>
						  <?php endif; ?>
							<?php print $content;?>
						</div>
					</div>
					<!--content panel end here -->
				</div>
				<!--bodyPan end here -->
				
				<!--bottom links -->
				<div class="footerLinks">
					
					<!--  <a href="http://ogpl.gov.in" title="Open Government Platform" class="logo">Open Government Platform</a>
					<a href="http://www.nic.in" title="National Informatics Centre" alt="National Informatics Centre" target="_blank" class="nic-logo-footer">
					National Informatics Centre</a> -->
					<?php if(is_frontend_url()): ?>
						<?php print $footer; 
					endif; ?>
					<div class="right">
						<a href="<?php echo variable_get('hostedby_image_url', NULL); ?>" title="<?php echo variable_get('hostedby_title', NULL); ?>">
							<img title="<?php echo variable_get('hostedby_title', NULL); ?>" src="<?php echo variable_get('hostedby_image', NULL); ?>" />
						</a>
			
					 	<a href="<?php echo variable_get('powerby_image_url', NULL); ?>" alt="<?php echo variable_get('powerby_title', NULL); ?>" target="_blank">
					 		<img title="<?php echo variable_get('powerby_title', NULL); ?>" src="<?php echo variable_get('powerby_image', NULL); ?>" />
						</a>
					</div>
					
					
					<div class="spacer" ></div>
				</div>
				<!--bottom links -->
			</div>
		</div>
	</div>
	<!--body panel end here -->
	
	<!--bottom panel start here -->
	<div class="bottomLinks">
		<div class="mid blocks">
			<?php echo theme('site_map'); ?>
		</div>
	</div>
	<!--bottom panel end here -->

	<!--footer start here -->
	<div id="footer">
	<?php if(is_frontend_url()): ?>
		<ul class="top">
			<?php print $footer_links;?>
		</ul>
	<?php endif;?>
		<div class="footerContent">
      		<?php if ($footer_message): ?><div class='footer-message'><?php print $footer_message ?></div><?php endif; ?>
      <div class="spacer" ></div>
    </div>
	</div>
	<!--footer end here -->
<?php
  print $closure;
?>
</body>
</html>