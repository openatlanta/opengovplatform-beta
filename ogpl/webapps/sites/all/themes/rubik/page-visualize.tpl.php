<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
  <meta http-equiv="X-UA-Compatible" content="IE=9" >
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
    <title>Data Portal India Visualization Engine</title>
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
  </head>
  <body <?php print drupal_attributes($attr) ?>>

  <?php print $skipnav ?>
  <div id='logo' class='clear-block'>
    <div class='logo'>
    	<a href="<?php echo check_url($front_page); ?>"><img title="Open Government Platform (OGPL)" src="<?php print $logo; ?>" alt="logo" /></a>
    </div>
    <div class="header-anounced-text">The National Data Portal Beta</div>
    <div class="searchPan"></div>
  </div>
  <div id="menu">
  <?php print $header_top; ?>
  </div>
  <div class="clear-block"></div>
  <div id='branding' class='clear-block'>
    <!--  <div class='breadcrumb clear-block'><?php // print $breadcrumb ?></div> -->
    <?php echo $user_link; ?>
    <?php /*  if ($user_links) print theme('links', $user_links) */?>
  </div>

  <div id='page-title' class='clear-block'>
    <?php if ($help_toggler) print $help_toggler ?>
    
    <h1 class='page-title <?php print $page_icon_class ?>'>
      <?php if (!empty($page_icon_class)): ?><span class='icon'></span><?php endif; ?>
      <?php if ($title) print $title ?>
    </h1>
    <div id="spacer"></div>
    <?php if ($tabs): ?><?php print $tabs ?><?php endif; ?>
  </div>

  <div id='page'>
    <?php if ($tabs2): ?><div class='secondary-tabs clear-block'><?php print $tabs2 ?></div><?php endif; ?>
    <?php if ($help) print $help ?>
    <div class='page-content clear-block'>
      <?php if ($show_messages && $messages): ?>
        <div id='console' class='clear-block'><?php print $messages; ?></div>
      <?php endif; ?>

      <div id='content'>
        <?php if (!empty($content)): ?>
          <div class='content-wrapper clear-block'><?php print $content ?></div>
          <div class='dataset-side-wrapper'>
            <div id="dataset-side-content-1" class='dataset-side-content' >
              <?php print $dataset_side;?>
            </div>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </div>

  <div id='footer' class='clear-block'>
  <hr class="footer-hr"></hr>
  	
    <?php if ($feed_icons): ?>
      <div class='feed-icons clear-block'>
        <label><?php print t('Feeds') ?></label>
        <?php print $feed_icons ?>
      </div>
    <?php endif; ?>
    <?php if ($footer_message): ?><div class='footer-message'><?php print $footer_message ?></div><?php endif; ?>
    <div class="footer-admin-poweredby">
  		<a href="<?php echo variable_get('powerby_image_url', NULL); ?>" alt="<?php echo variable_get('powerby_title', NULL); ?>" target="_blank">
	 		<img title="<?php echo variable_get('powerby_title', NULL); ?>" src="<?php echo variable_get('powerby_image', NULL); ?>" />
		</a>
  	</div>
  </div>

  <?php print $closure ?>

  </body>
</html>
