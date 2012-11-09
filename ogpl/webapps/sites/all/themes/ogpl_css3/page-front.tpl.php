<?php
    global $base_url;
     
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">
<head>
<meta http-equiv="X-UA-Compatible" content="IE=8" />
<meta http-equiv="content-language" content="<?php echo $language->language;?>" />
<title>Home | Welcome to ODP</title>
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

<body role="application" class="homePage">
	<span>
		<a class="skipnav" accesskey="1" href="#mainNav">Skip to navigation</a>
		<a class="skipnav" accesskey="2" href="#mainContent">Skip to main content</a>
	</span>
<div id="outerContainer">	
	<div id="mainContainer">
        
        
       <?php include ('include/header.tpl.php') ;?> 
        
        
        
        <!--blocks panel start here -->
        <div id="mainContent" role="main">
			<?php print $content;?>
        </div>
        <!--blocks panel end here -->
        
        <?php include ('include/footer.tpl.php') ;?>
        
        
	</div> <!-- outerContainer div ends here -->
</body>
<?php
print $closure;
?>
</html>
