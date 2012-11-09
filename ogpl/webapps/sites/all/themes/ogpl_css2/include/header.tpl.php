<!--top panel start here -->
	<div id="topPanel">
		<div class="mid">
			<!--goi -->
            <div class="goi">
            	<div class="gov"><a target="_blank" class="country-flag" title="<?php echo $gov_name; ?>" href="<?php echo $portal_url; ?>">
            	<img style="float: left; width: auto; padding-right:7px;" src="<?php echo $site_img; ?>" alt="Country Flag" width="auto" height="14" />
            	<?php echo $gov_name; ?></a>
            	</div>
            	<span class="ext"></span>&nbsp;
            </div>
			<!--goi -->
				
			<!--accessibility panel start here -->
			<div class="accessPan">
				<ul>
					
					<!--flags options -->
                    <li class="flags">
						<?php print $header_flags; ?>
                    </li>
                    <!--text resizing option -->
					<li class="resize">
						<?php print $text_resize; ?>
					</li>
					<!--color contrast options -->
					<li class="contrast">
						<a href="javascript:void(0);" class="dark" onclick="chooseStyle('change', 60);"><img src="<?php echo $base_url."/".path_to_theme();?>/images/texthighContrast.gif" alt="High Contrast View"/></a>
						<a href="javascript:void(0);" class="light" onclick="chooseStyle('none', 60);"><img src="<?php echo $base_url."/".path_to_theme();?>/images/textNormal.gif" alt="Standard Contrast View"/></a>
					</li>
					<!--color contrast options -->
					<?php if(is_frontend_url()):?>
					<li class="feedback"><a href="<?php echo $base_url;?>/feedback" title="Feedback">Feedback</a></li>
					<li><a href="<?php echo $base_url;?>/rssfeeds" title="RSS Feeds" class="rss">RSS Feeds</a></li>
					<li class="share">
                    <!-- AddThis Button BEGIN -->
                        <div class="addthis_toolbox addthis_default_style ">
                            <a class="addthis_button_compact add-this-link" href="http://www.addthis.com/bookmark.php" title="Bookmark and Share">Share+</a>
                        </div>
                    <!-- AddThis Button END -->
					</li>
					<?php 
					global $user;
					
					if ($user->uid) {
                  	echo "<li><a href='$base_url/user'>Welcome ".$user->name." </a></li>";
					echo "<li><a href='$base_url/logout'>Log out</a></li>";
					}
					else
					{
						echo "<li><a href ='$base_url/user/register'>SignUp </a></li>";
						echo "<li> <a href='$base_url/user/login'> Log In </a></li>";
					}
					
					?>
					<?php endif ;?>
				</ul>
			</div>
			<!--accessibility panel end here -->
		</div>
	</div>
	<!--top panel end here -->
	
	
	<!--logo panel start here -->
	<div id="logoPanel">
		<div class="mid">
			<div class="left">
				<!--logo start here -->
				<div class="logoPan">
					
					<div class="logo">
					<?php
					// Prepare header
					$site_fields = array();
					if ($site_name) {
						$site_fields[] = check_plain($site_name);
					}
					if ($site_slogan) {
						$site_fields[] = check_plain($site_slogan);
					}
					$site_title = implode(' ', $site_fields);
					if ($site_fields) {
						$site_fields[0] = '<span>'. $site_fields[0] .'</span>';
					}
					$site_html = implode(' ', $site_fields);
					
					if ($logo || $site_title) {
						print '<a href="'. check_url($front_page) .'" title="'. $site_title .'">';
					if ($logo) {
						print '<img src="'. check_url($logo) .'" alt="'. $site_title .'" id="logo-image" />';
					}
					print '</a>';
					}
					?>
					</div>
					<!--logo end here -->
					
					
				</div>
				<!--logo start here -->
				
				<!-- The National Data Portal Beta Version Text added Code Starts -->
				<div class="header-anounced-text">The National Data Portal Beta</div>
				<!-- The National Data Portal Beta Version Text added Code ends -->
				
				<!--search form start here -->
				<div class="searchPan">
					<?php print $search_box; ?>
				</div>
				<!--search form end here -->
			</div>
		</div>
	</div>
	<!--logo panel end here -->