<?php
	global $base_url;
	global $theme_key;
    $themes = list_themes();
    $theme_object = $themes[$theme_key];
    $site_var = variable_get('site_country','');
    $site_node = node_load($site_var);
	$theme_name=$theme_object->name;
	$access_denied = 0;	
	$admin_page_urls = variable_get('admin_pages_list', '');
    $flag_img=substr($site_node->field_website_header_image[0]['filepath'],strpos($site_node->field_website_header_image[0]['filepath'],"files/"));
 
    if(variable_get('file_downloads','') == 2) {		
		$site_img = $base_url."/system/".$flag_img;
	} else {
		$site_img = $base_url.'/'.$site_node->field_website_header_image[0]['filepath'];
	}

    $portal_url = $site_node->field_country_portal_url[0]['url'];
    $gov_name = $site_node->field_union_govt_name[0]['value'];
    if(in_array(drupal_get_path_alias($_GET['q']), explode("\r\n", $admin_page_urls)) && in_array('anonymous user', $user->roles)){
		$access_denied = 1;
		$head_title = "Access Denied";
	}
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
<!--[if gte IE 9]>
  <style type="text/css">
    .gradient {
       filter: none;
    }
  </style>
<![endif]-->
</head>

<body class="contact <?php print ($node->type=='dataset'?'dataset-page':''); ?> ">
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
				<!--content panel start here -->
				<div id="contentPanel">
					<div class="mainContent">
					<?php 
  					if ($node->type == 'dataset' ) {
               $_replace     = '</a>';   
               switch($node->field_ds_catlog_type[0][type]) {
                 case 'catalog_type_raw_data':   
                   $_replaceWith = '</a><a href="/catalogs/?filter=catalog_type%3Acatalog_type_raw_data">Datasets</a>';
                   $breadcrumb = str_replace($_replace, $_replaceWith, $breadcrumb);
                 break;
                 case 'catalog_type_data_apps':
                   $_replaceWith = '</a><a href="/catalogs/?filter=catalog_type%3Acatalog_type_data_apps">Apps</a>';
                   $breadcrumb = str_replace($_replace, $_replaceWith, $breadcrumb);
                   break;
               } 
  					} 
					?>
					<?php print $breadcrumb; ?>
					<?php
						if($access_denied == 1) {
							echo '<div class="mainHeading"><h1 class="page-title">'.t('Access denied').'</h1></div>';
						} else {
							?>
							<!--main heading start here -->
							<div class="mainHeading">
							<?php if ($title){ print '<h1'. ' class="page-title"' .'>'. $title .'</h1>';}?>
							</div>
							<!--main heading end here -->
						<?php } ?>

						<div class="contentArea mainContainer">
						  <?php include ('include/topbar.tpl.php') ;?>
							<!--content -->
							<div class="bottom <?php print " content-height";?>">
							<?php if ($metrics_menu){ print '<div class="metrics-menu">'. $metrics_menu .'<div class="page-title-border"></div></div>';} ?>
							<?php print $messages;  ?>
							<?php
							if($access_denied == 1) {
								echo '<div class="access-denied-error">'.t('You are not authorized to access this page.').'</div>';
							}
							else{
								print $content; 
							} ?>
							</div>
							<!--content -->
							<!--bottom links start here -->
							<div class="contentArea bottomLink">
								<div class="mid"></div>
								<?php if(is_frontend_url()):?>
								<?php print $footer;
								endif ; ?>
							</div>
							<!--bottom links end here -->
						</div>
						
						
					</div>
				</div>
				<!--content panel end here -->

			</div>
		</div>

		
		<?php include ('include/footer.tpl.php') ;?>
		
		
	</div>
	<!--body panel end here -->
	
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
<?php
print $closure;
?>
</body>

</html>