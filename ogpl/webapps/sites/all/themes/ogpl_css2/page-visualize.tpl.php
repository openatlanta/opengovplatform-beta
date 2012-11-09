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
<title>Dataportal India Visualization Engine</title>
<?php print $head ?>
<?php print $styles ?>
<?php $scripts = drupal_add_js();
     $new_jquery = array('recline/vendor/jquery/1.7.1/jquery.js' => $scripts['core']['sites/all/modules/contrib/jquery_update/replace/jquery.min.js']);
      $scripts['core'] = array_merge($new_jquery, $scripts['core']);
      unset($scripts['core']['misc/jquery.js']);
      unset($scripts['core']['sites/all/modules/contrib/jquery_update/replace/jquery.min.js']);
      $visual_scripts = drupal_get_js('header', $scripts);
      print $visual_scripts;
 ?>
<link href="<?php echo $base_url."/".path_to_theme();?>/high.css" rel="alternate stylesheet" type="text/css" media="screen" title="change" />
<!-- Le HTML5 shim, for IE6-8 support of HTML elements -->
  <!--[if lt IE 9]>
    <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->

	<link rel="stylesheet" href="/recline/vendor/bootstrap/2.0.2/css/bootstrap.css" />
	<link rel="stylesheet" href="/recline/vendor/leaflet/0.3.1/leaflet.css">
<!--[if lte IE 8]>
    <link rel="stylesheet" href="http://cdn.leafletjs.com/leaflet-0.4.4/leaflet.ie.css" />
<![endif]-->
  <!--[if lte IE 8]>
  <link rel="stylesheet" href="vendor/leaflet/0.3.1/leaflet.ie.css" />
  <![endif]-->
  <link rel="stylesheet" href="/recline/vendor/slickgrid/2.0.1/slick.grid.css">
  <link rel="stylesheet" href="/recline/vendor/timeline/20120520/css/timeline.css">

  <!-- Recline CSS components -->
  <link rel="stylesheet" href="/recline/css/grid.css">
  <link rel="stylesheet" href="/recline/css/slickgrid.css">
  <link rel="stylesheet" href="/recline/css/graph.css">
  <link rel="stylesheet" href="/recline/css/transform.css">
  <link rel="stylesheet" href="/recline/css/map.css">
  <link rel="stylesheet" href="/recline/css/multiview.css">
  <!-- /Recline CSS components -->

  <!-- 3rd party JS libraries -->
  <script type="text/javascript" src="/recline/vendor/underscore/1.1.6/underscore.js"></script>
  <script type="text/javascript" src="/recline/vendor/backbone/0.5.1/backbone.js"></script>
  <script type="text/javascript" src="/recline/vendor/mustache/0.5.0-dev/mustache.js"></script>
  <script type="text/javascript" src="/recline/vendor/bootstrap/2.0.2/bootstrap.js"></script>
  <script type="text/javascript" src="/recline/vendor/flotr2/flotr2.js"></script>
  <script type="text/javascript" src="/recline/vendor/leaflet/0.3.1/leaflet.js"></script>
  <script type="text/javascript" src="/recline/vendor/slickgrid/2.0.1/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="/recline/vendor/slickgrid/2.0.1/jquery.event.drag-2.0.min.js"></script>
  <script type="text/javascript" src="/recline/vendor/slickgrid/2.0.1/slick.grid.min.js"></script>
  <script type="text/javascript" src="/recline/vendor/moment/1.6.2/moment.js"></script>
  <script type="text/javascript" src="/recline/vendor/timeline/20120520/js/timeline.js"></script>

  <!--
    ## Just use the all in one library version rather than individual files

  <script type="text/javascript" src="dist/recline.js"></script>

  -->

  <!-- model and backends -->
  <script type="text/javascript" src="/recline/src/model.js"></script>
  <script type="text/javascript" src="/recline/src/backend.memory.js"></script>
  <script type="text/javascript" src="/recline/src/backend.dataproxy.js"></script>
  <script type="text/javascript" src="/recline/src/backend.datatool.js"></script>
  <script type="text/javascript" src="/recline/src/backend.gdocs.js"></script>
  <script type="text/javascript" src="/recline/src/backend.elasticsearch.js"></script>
  <script type="text/javascript" src="/recline/src/backend.csv.js"></script>

  <!-- views -->
  <script type="text/javascript" src="/recline/src/view.grid.js"></script>
  <script type="text/javascript" src="/recline/src/view.slickgrid.js"></script>
  <script type="text/javascript" src="/recline/src/view.transform.js"></script>
  <script type="text/javascript" src="/recline/src/data.transform.js"></script>
  <script type="text/javascript" src="/recline/src/view.graph.js"></script>
  <script type="text/javascript" src="/recline/src/view.map.js"></script>
  <script type="text/javascript" src="/recline/src/view.timeline.js"></script>
  <script type="text/javascript" src="/recline/src/widget.pager.js"></script>
  <script type="text/javascript" src="/recline/src/widget.queryeditor.js"></script>
  <script type="text/javascript" src="/recline/src/widget.filtereditor.js"></script>
  <script type="text/javascript" src="/recline/src/widget.fields.js"></script>
  <script type="text/javascript" src="/recline/src/widget.workbooks.js"></script>
  <script type="text/javascript" src="/recline/src/view.multiview.js"></script>

<script type="text/javascript" src="/recline/app.js"></script>
<style type="text/css">
.recline-slickgrid {
  height: 500px;
}

.recline-timeline .vmm-timeline {
  height: 400px;
}
</style>
<!--[if gte IE 9]>
  <style type="text/css">
    .gradient {
       filter: none;
    }
  </style>
<![endif]-->
</head>

<body class="contact <?php print ($node->type=='dataset'?'dataset-page':''); ?>">
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
							<?php if ($show_messages && $messages): print '<div class="error-block">'. $messages .'</div>'; endif; ?>
							<?php
							if($access_denied == 1) {
								echo '<div class="access-denied-error">'.t('You are not authorized to access this page.').'</div>';
							}
							else{
								print $content; 
							} ?>
							<?php
							if($node->type=='dataset')  {
							print '<div id="suggest-cp-block"><div style="text-align:center;margin-right:20px;" class="suggest-cp">';	 
							print '<div class="suggest-label">
						 		 <div class="midTxt">
									<div class="midTxt-content">Could not find your searched dataset</div>
						 			<div class="midTxt-content-image"><a title="Suggest Dataset"  href="'.$base_url.'/suggest_dataset" >Suggest</a></div>
						 		 </div>
					 		 </div>';
							print '</div></div>';
							}
							?>
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