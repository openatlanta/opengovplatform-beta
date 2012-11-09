<?php

/**
 * Implementation of hook_views_default_views().
 */
function agency_wise_metrics_views_default_views() {
  $views = array();

  // Exported view: agency_datasets
  $view = new view;
  $view->name = 'agency_datasets';
  $view->description = 'Agency Datasets';
  $view->tag = '';
  $view->base_table = 'node';
  $view->core = 6;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'phpcode_1' => array(
      'label' => 'High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<?php

$result=db_result(db_query("select * from content_type_dataset ds INNER JOIN content_type_policy_program_open_government ppog on ds.nid=ppog.nid where ds.nid=$data->nid AND ppog.field_ppog_high_value_dataset_value=\'Yes\' ")); 

if($result) return \'Yes\';
else return \'No\';


?>',
      'exclude' => 0,
      'id' => 'phpcode_1',
      'table' => 'customfield',
      'field' => 'phpcode',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_ds_description_value' => array(
      'label' => 'Description',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '75',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_ds_description_value',
      'table' => 'node_data_field_ds_description',
      'field' => 'field_ds_description_value',
      'relationship' => 'none',
    ),
    'phpcode' => array(
      'label' => 'Ratings',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'value' => '<?php

                         $a=0;
			 $q=0;
			 $u=0;
			 $acc=votingapi_select_results(array(\'content_id\' => $data->nid, \'tag\' =>\'voteaccessibility\', \'function\' => \'average\'));
			 $qual=votingapi_select_results(array(\'content_id\' => $data->nid, \'tag\' =>\'votequality\', \'function\' => \'average\'));
			 $usab=votingapi_select_results(array(\'content_id\' => $data->nid, \'tag\' =>\'voteusability\', \'function\' => \'average\'));
			 $oldrange=(25-0);
			 $newrange=(40-20);
			 	$a=(int)$acc[0][\'value\'];		
			    $q=(int)$qual[0][\'value\'];
				$u=(int)$usab[0][\'value\'];
			  if($acc!=null)
			   {
				 if($a>=0&&$a<25)
				 {
				   $a=((($a-0)*$newrange)/$oldrange)+20;
				 }
				 else if($a>=25&&$a<50)
				 {
				    $a=((($a-25)*$newrange)/$oldrange)+40;
				 }
				 else if($a>=50&&$a<75)
				 {
				    $a=((($a-50)*$newrange)/$oldrange)+60;
				 }
				 else if($a>=75&&$a<100)
				 {
				    $a=((($a-75)*$newrange)/$oldrange)+80;
				 }
						   
			   }
			    if($qual!=null)
			   {
				 if($q>=0&&$q<25)
				 {
				   $q=((($q-0)*$newrange)/$oldrange)+20;
				 }
				 else if($q>=25&&$q<50)
				 {
				    $q=((($q-25)*$newrange)/$oldrange)+40;
				 }
				 else if($q>=50&&$q<75)
				 {
				    $q=((($q-50)*$newrange)/$oldrange)+60;
				 }
				 else if($q>=75&&$q<100)
				 {
				    $q=((($q-75)*$newrange)/$oldrange)+80;
				 }
						   
			   }
			    if($usab!=null)
			   {
				 if($u>=0&&$u<25)
				 {
				   $u=((($u-0)*$newrange)/$oldrange)+20;
				 }
				 else if($u>=25&&$u<50)
				 {
				    $u=((($u-25)*$newrange)/$oldrange)+40;
				 }
				 else if($u>=50&&$u<75)
				 {
				    $u=((($u-50)*$newrange)/$oldrange)+60;
				 }
				 else if($u>=75&&$u<100)
				 {
				    $u=((($u-75)*$newrange)/$oldrange)+80;
				 }
						   
			   }
				
		$value=(int)(($a+$q+$u)/3);
		$value=$value/10;
		$value=round($value);
		$value=$value*10;
		if($value<10)
		  $value=0;
	    else if($value>=10 && $value<30)
			$value=20;	
		else if($value>=30 &&$value<50)
			$value=40;	
		else if($value>=50 &&$value<70)
			$value=60;	
		else if($value>=70 &&$value<90)
			$value=80;	
		else if($value>=90 &&$value<=100)
			$value=100;			
			  $vote1= rate_get_results(\'node\', $data->nid, 1);
                          $vote2 = rate_get_results(\'node\', $data->nid, 2);
                          $vote3=rate_get_results(\'node\', $data->nid, 3);
                           $vote=$vote1[\'count\'];
                          if($vote2[\'count\']>$vote) $vote=$vote2[\'count\'];
                          if($vote3[\'count\']>$vote)$vote=$vote3[\'count\'];
                         $votes = \' <span > (\'.$vote.\' votes)</span>\'; 
                         return $value . $votes;
?>',
      'exclude' => 0,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_ds_ministry_department_value' => array(
      'label' => 'Ministry/Department',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 0,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_ds_ministry_department_value',
      'table' => 'node_data_field_ds_ministry_department',
      'field' => 'field_ds_ministry_department_value',
      'relationship' => 'none',
    ),
    'field_ds_sector_value' => array(
      'label' => 'Sector (multiple)',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_ds_sector_value',
      'table' => 'node_data_field_ds_sector',
      'field' => 'field_ds_sector_value',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'name' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'ignorecase' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'add_table' => 0,
      'require_value' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        2 => 0,
        10 => 0,
        18 => 0,
        11 => 0,
        3 => 0,
        20 => 0,
        9 => 0,
        12 => 0,
        4 => 0,
        6 => 0,
        19 => 0,
        13 => 0,
        15 => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_taxonomy_tid_term_page' => 0,
      'default_taxonomy_tid_node' => 0,
      'default_taxonomy_tid_limit' => 0,
      'default_taxonomy_tid_vids' => array(
        16 => 0,
        7 => 0,
        1 => 0,
        8 => 0,
        17 => 0,
        2 => 0,
        3 => 0,
        4 => 0,
        9 => 0,
        10 => 0,
        11 => 0,
        15 => 0,
        13 => 0,
        14 => 0,
        5 => 0,
      ),
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'faq' => 0,
        'access_type_downloadable' => 0,
        'agency' => 0,
        'catalog_type_data_apps' => 0,
        'catalog_type_data_service' => 0,
        'catalog_type_data_tools' => 0,
        'catalog_type_document' => 0,
        'catalog_type_raw_data' => 0,
        'dataset' => 0,
        'geospatial_metadata' => 0,
        'policy_program_data_quality' => 0,
        'policy_program_open_government' => 0,
        'policy_program_privacy' => 0,
        'profile' => 0,
        'sector' => 0,
        'statistical_metadata' => 0,
        'sub_agency' => 0,
        'sub_sector' => 0,
        'subject_keyword' => 0,
        'target_audience' => 0,
        'page' => 0,
        'imageflow' => 0,
        'country_data' => 0,
        'state_data_site' => 0,
        'rotating_panel' => 0,
        'feedback_reply' => 0,
        'feedback' => 0,
        'forum' => 0,
        'block' => 0,
        'blog' => 0,
        'community' => 0,
        'community_featured' => 0,
        'community_home' => 0,
        'community_suggestion' => 0,
        'downloadable' => 0,
        'embed_link_access_method' => 0,
        'feedback_review' => 0,
        'role_request' => 0,
        'story' => 0,
        'theme_file_uploader' => 0,
        'upload_docs' => 0,
        'webform' => 0,
        'whats_new' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        16 => 0,
        7 => 0,
        1 => 0,
        8 => 0,
        17 => 0,
        2 => 0,
        3 => 0,
        4 => 0,
        9 => 0,
        10 => 0,
        11 => 0,
        15 => 0,
        13 => 0,
        14 => 0,
        5 => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => '0',
      'validate_argument_group_node_type' => array(
        'community' => 0,
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'vid' => array(
      'operator' => 'in',
      'value' => array(
        15 => '15',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'vid',
      'table' => 'term_data',
      'field' => 'vid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header_format', '3');
  $handler->override_option('header_empty', 0);
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'title' => 'title',
      'phpcode' => 'phpcode',
      'field_ds_agency_name_nid' => 'field_ds_agency_name_nid',
      'field_ds_sector_nid' => 'field_ds_sector_nid',
      'field_ds_sub_agency_name_value' => 'field_ds_agency_name_nid',
      'field_ds_description_value' => 'title',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '<br>',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'field_ds_agency_name_nid' => array(
        'separator' => '',
      ),
      'field_ds_sector_nid' => array(
        'separator' => '',
      ),
      'field_ds_sub_agency_name_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_ds_description_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'sid_op',
        'label' => 'Workflow: Current state',
        'use_operator' => 0,
        'identifier' => 'sid',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('fields', array(
    'phpcode_1' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<?php

$result=db_result(db_query("select * from content_type_dataset ds INNER JOIN content_type_policy_program_open_government ppog on ds.nid=ppog.nid where ds.nid=$data->nid AND ppog.field_ppog_high_value_dataset_value=\'Yes\' ")); 

if($result) return \'<h1>*</h1>\';


?>',
      'exclude' => 0,
      'id' => 'phpcode_1',
      'table' => 'customfield',
      'field' => 'phpcode',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '[title] ',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '50',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode' => array(
      'label' => 'Ratings',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'value' => '<?php

$avg_rating=variable_get(\'average_rating\',0);
$avg_votes=variable_get(\'average_votes\',0);
$value=calculate_ratings($data->nid,$avg_rating,$avg_votes);


 $vote1= rate_get_results(\'node\', $data->nid, 1);
  $vote2 = rate_get_results(\'node\', $data->nid, 2);
  $vote3=rate_get_results(\'node\', $data->nid, 3);
  $vote=$vote1[\'count\'];
  if($vote2[\'count\']>$vote) $vote=$vote2[\'count\'];
  if($vote3[\'count\']>$vote)$vote=$vote3[\'count\'];                 
  if($vote==1)   $votes=\'<span>(\'.$vote.\' vote)</span>\'; 
else		           
  $votes=\'<span>(\'.$vote.\' votes)</span>\'; 
return theme(\'fivestar_static\',$value).$votes;
?>',
      'exclude' => 0,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'field_agency_short_name_value' => array(
      'label' => 'Agency/Sub-Agency ',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_agency_short_name_value',
      'table' => 'node_data_field_agency_short_name',
      'field' => 'field_agency_short_name_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'field_ds_agency_name_nid',
    ),
    'field_sa_subagency_short_name_value' => array(
      'label' => 'Sub-Agency Short Name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_sa_subagency_short_name_value',
      'table' => 'node_data_field_sa_subagency_short_name',
      'field' => 'field_sa_subagency_short_name_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'field_ds_sub_agency_nid',
    ),
    'field_ds_sector_nid' => array(
      'label' => 'Category',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'plain',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_ds_sector_nid',
      'table' => 'node_data_field_ds_sector',
      'field' => 'field_ds_sector_nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'field_ds_description_value' => array(
      'label' => 'Description',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<p>[field_ds_description_value]</p>',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '75',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 1,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_ds_description_value',
      'table' => 'node_data_field_ds_description',
      'field' => 'field_ds_description_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('arguments', array(
    'field_ds_agency_name_nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1',
      'breadcrumb' => '',
      'default_argument_type' => 'node',
      'default_argument' => '',
      'validate_type' => 'node',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'field_ds_agency_name_nid',
      'table' => 'node_data_field_ds_agency_name',
      'field' => 'field_ds_agency_name_nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        2 => 0,
        10 => 0,
        18 => 0,
        11 => 0,
        3 => 0,
        9 => 0,
        12 => 0,
        4 => 0,
        6 => 0,
        14 => 0,
        13 => 0,
        17 => 0,
        15 => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'agency' => 'agency',
        'diymap' => 0,
        'faq' => 0,
        'page' => 0,
        'imageflow' => 0,
        'flags' => 0,
        'geo_data' => 0,
        'rotating_panel' => 0,
        'access_type_downloadable' => 0,
        'access_type_embed_link' => 0,
        'access_type_execute_upon_access' => 0,
        'catalog_type_data_apps' => 0,
        'catalog_type_data_service' => 0,
        'catalog_type_data_tools' => 0,
        'catalog_type_document' => 0,
        'catalog_type_raw_data' => 0,
        'dataset' => 0,
        'geospatial_metadata' => 0,
        'openlayers_test_type' => 0,
        'policy_program_data_quality' => 0,
        'policy_program_open_government' => 0,
        'policy_program_privacy' => 0,
        'profile' => 0,
        'sector' => 0,
        'statistical_metadata' => 0,
        'story' => 0,
        'subject_keyword' => 0,
        'sub_agency' => 0,
        'upload_docs' => 0,
        'webform' => 0,
        'whats_new' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'relationship' => 'none',
    ),
    'php' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'use_php_setup' => 0,
      'php_setup' => '',
      'php_filter' => '',
      'sql_filter' => 'if($view->args[2]==1)
{
return "node_data_field_ds_agency_name.field_ds_catlog_type_type=\'catalog_type_raw_data\' ";
}
else if($view->args[2]==2)
{
return "node_data_field_ds_agency_name.field_ds_catlog_type_type=\'catalog_type_document\' ";
}
else if($view->args[2]==3)
{
return "node_data_field_ds_agency_name.field_ds_catlog_type_type=\'catalog_type_data_apps\' ";
}
else if($view->args[2]==4)
{
return "node_data_field_ds_agency_name.field_ds_catlog_type_type=\'catalog_type_data_tools\' ";
}
else if($view->args[2]==5)
{
return "node_data_field_ds_agency_name.field_ds_catlog_type_type=\'catalog_type_data_service\' ";
}',
      'id' => 'php',
      'table' => 'views',
      'field' => 'php',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'php_1' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'use_php_setup' => 0,
      'php_setup' => '',
      'php_filter' => '',
      'sql_filter' => 'if($view->args[1]==\'-\')
{
return "node_data_field_ds_agency_name.field_ds_sub_agency_nid IS NULL";
}

if(!strlen(strstr($view->args[1], "main_"))>0 )
{
return "node_data_field_ds_agency_name.field_ds_sub_agency_nid=\'".$view->args[1]."\' ";
}',
      'id' => 'php_1',
      'table' => 'views',
      'field' => 'php',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', '<?php

 /* Calculating average ratings for all items (AR) */
  $result=db_query("select distinct(content_id) as nid from votingapi_vote V LEFT JOIN node N on V.content_id=N.nid where N.type=\'dataset\' ");
  while($row=db_fetch_object($result))
  {
     $sum=$sum+get_average_ratings($row->nid);
     $count++;
  }
  
  $AR=$sum/$count;
  //print "AR=".$AR;

  /*Calculating average number of votes for all items (AV) */
$result=db_query("select distinct(content_id) as nid from votingapi_vote V LEFT JOIN node N on V.content_id=N.nid where N.type=\'dataset\' ");

  $sum=0;
  while($row=db_fetch_object($result))
  {   
     $sum=$sum+get_average_rating_votes($row->nid);
  }
  $AV=$sum/$count;
  $AV=round($AV);

 variable_set(\'average_rating\',$AR);
 variable_set(\'average_votes\',$AV); 
       
        $this_page = $_SERVER[\'REQUEST_URI\'];
	$last =substr($this_page,0,strripos($this_page,\'/\'));
        $slast =substr($last,0,strripos($last,\'/\'));
	$third_last=strripos($slast,\'/\');
	$argument=substr($this_page,$third_last);
	
		$qpos;
     if(strlen(strstr($this_page,"?")))
      {
              $qpos=strpos($this_page,\'?\');
               
       }
	$li=strripos($this_page,\'/\');

       if($qpos!=0)
	$arg=substr($this_page,$li,2);
	else
	$arg=substr($this_page,$li);
       		
	if($arg==\'/1\'||$arg==\'/2\'||$arg==\'/3\'||$arg==\'/4\'||$arg==\'/5\')
	 {
	   $this_page=substr($this_page,0,$li);
	 } 
         global $base_url;

$view = views_get_current_view();
$arg0 = $view->args[0];
$arg1 = $view->args[1];

if($arg1==\'-\') $sub_agency=\'IS NULL\';
else $sub_agency="= $arg1";

if(!strlen(strstr($view->args[1], "main_"))>0 )
$raw=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid  INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_raw_data\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1"));
else
$raw=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_raw_data\' AND field_ds_agency_name_nid=$arg0 AND n.status=1 "));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$doc=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid  where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_document\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1"));
else
$doc=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_document\' AND field_ds_agency_name_nid=$arg0 AND n.status=1"));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$apps=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type IN (\'catalog_type_data_apps\') AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1"));
else
$apps=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type IN (\'catalog_type_data_apps\')  AND field_ds_agency_name_nid=$arg0 AND n.status=1"));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$tool=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid  where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_tools\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1 "));
else
$tool=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid  INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_tools\' AND field_ds_agency_name_nid=$arg0 AND n.status=1 "));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$ser=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_service\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1 "));
else
$ser=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid  INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_service\' AND field_ds_agency_name_nid=$arg0 AND n.status=1 "));



		
	 print \'<div class="catalog-tabs-menu fLeft" style="margin-top:7px;height:23px;">\';
	 print \'<ul class="catalog-tabs" style="position:absolute;">\';
	if($arg==\'/1\' && $raw )
  	 print \'<li><a style="padding:1px 30px;" class="active" href="\'.$this_page.\'/1" title="Raw Dataset Catalogs">Raw Dataset Catalogs</a></li>\';
	else if($raw)
	  print \'<li><a style="padding:0px 30px;" href="\'.$this_page.\'/1" title="Raw Dataset Catalogs">Raw Dataset Catalogs</a></li>\';

	 if($arg==\'/2\' && $doc)
  	 print \'<li><a style="padding:1px 30px;" class="active" href="\'.$this_page.\'/2" title="Document Catalogs">Document Catalogs</a></li>\';
	else if($doc)
	  print \'<li><a style="padding:0px 30px;" href="\'.$this_page.\'/2" title="Document Catalogs">Document Catalogs</a></li>\';

	if($arg==\'/3\' && $apps)
  	 print \'<li><a style="padding:1px 30px;"  class="active" href="\'.$this_page.\'/3" title="App Catalogs">App Catalogs</a></li>\';
	else if($apps)
	  print \'<li><a style="padding:0px 30px;" href="\'.$this_page.\'/3" title="App Catalogs">App Catalogs</a></li>\';

	if($arg==\'/4\' && $tool)
  	 print \'<li><a style="padding:1px 30px;"  class="active" href="\'.$this_page.\'/4" title="Tool Catalogs">Tool Catalogs</a></li>\';
	else if($tool)
	  print \'<li><a style="padding:0px 30px;" href="\'.$this_page.\'/4" title="Tool Catalogs">Tool  Catalogs</a></li>\';

	if($arg==\'/5\' && $ser)
  	 print \'<li><a style="padding:1px 30px;"  class="active" href="\'.$this_page.\'/5" title="Service Catalogs">Service Catalogs</a></li>\';
	else if($ser)
	  print \'<li><a style="padding:0px 30px;" href="\'.$this_page.\'/5" title="Service Catalogs">Service Catalogs</a></li>\';

	print\'</ul></div>\';


?>
<div class="page-title-border cBoth">&nbsp;</div>
<?php print l(\'<< Back to Agency Wise Report\',\'agency-publications/agency-wise\',array(\'attributes\' => array(\'class\' => \'metricsbacklink\',\'title\'=>\'Back to Agency Wise Report\'))); 
print \'<div style="margin-top:-15px;" class="download-report">Download report as: <a  title="CSV Download" class="hyperlink" href="\'.$base_url.\'/federalagency/datasets-agency/csv\'.$argument.\'?itemcount=500"><img alt="CSV" src="[token global site-url]sites/all/themes/ogpl_css3/images/csv.png" /></a> \' ;

print \'<a  title="XLS Download"  class="hyperlink" href="\'.$base_url.\'/federalagency/datasets-agency/xls\'.$argument.\'?itemcount=500"><img alt="XLS" src="[token global site-url]sites/all/themes/ogpl_css3/images/xls.png" /></a>\';

print \'<a style="padding-left:3px;" title="PDF Download" class="hyperlink" href="\'.$base_url.\'/printpdf/agency-publications/datasets-agency/pdf\'.$argument.\'?itemcount=500 "><img alt="PDF" src="[token global site-url]sites/all/themes/ogpl_css3/images/pdf.png" /></a></div>\'; ?>
');
  $handler->override_option('header_empty', 1);
  $handler->override_option('footer', '<br/>
<p>* Asterisks denote agency-reported high-value datasets. </p>');
  $handler->override_option('footer_format', '4');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('empty', '<?php
global $base_url;

print \'<div style="font:bold 1.3em arial; padding-top:10px">No matching records found. Please try your search again or <a style="color:blue;" href="\'.$base_url.\'/suggest_dataset" title="Suggest a dataset">suggest a dataset.</a></div>\';

?>


');
  $handler->override_option('empty_format', '3');
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'phpcode_1' => 'phpcode_1',
      'title' => 'title',
      'phpcode' => 'phpcode',
      'field_agency_short_name_value' => 'field_agency_short_name_value',
      'field_sa_subagency_short_name_value' => 'field_agency_short_name_value',
      'field_ds_sector_nid' => 'field_ds_sector_nid',
      'field_ds_description_value' => 'title',
    ),
    'info' => array(
      'phpcode_1' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '<br/>',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'field_agency_short_name_value' => array(
        'sortable' => 1,
        'separator' => '/',
      ),
      'field_sa_subagency_short_name_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_ds_sector_nid' => array(
        'separator' => '',
      ),
      'field_ds_description_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'title',
  ));
  $handler->override_option('path', 'agency-publications/datasets-agency-1');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('views_data_export', 'CSV', 'views_data_export_1');
  $handler->override_option('items_per_page', '0');
  $handler->override_option('style_plugin', 'views_data_export_csv');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
    'attach_text' => 'CSV',
    'provide_file' => 1,
    'filename' => '%view--%timestamp-full.csv',
    'help' => '',
    'parent_sort' => 0,
    'separator' => ',',
    'quote' => 1,
    'trim' => 1,
    'replace_newlines' => 0,
    'newline_replacement' => ':',
    'header' => 1,
    'encoding' => 'ASCII',
  ));
  $handler->override_option('row_plugin', '');
  $handler->override_option('path', 'federalagency/datasets-agency/csv');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $handler->override_option('use_batch', '0');
  $handler = $view->new_display('views_data_export', 'XLS', 'views_data_export_2');
  $handler->override_option('items_per_page', '0');
  $handler->override_option('style_plugin', 'views_data_export_xls');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
    'attach_text' => 'XLS',
    'provide_file' => 1,
    'filename' => '%view--%timestamp-full.xls',
    'help' => '',
    'parent_sort' => 0,
  ));
  $handler->override_option('row_plugin', '');
  $handler->override_option('path', 'federalagency/datasets-agency/xls');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);
  $handler->override_option('use_batch', '0');
  $handler = $view->new_display('page', 'PDF', 'page_2');
  $handler->override_option('arguments', array(
    'name' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'ignorecase' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'add_table' => 0,
      'require_value' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        2 => 0,
        10 => 0,
        18 => 0,
        11 => 0,
        3 => 0,
        20 => 0,
        9 => 0,
        12 => 0,
        4 => 0,
        6 => 0,
        19 => 0,
        13 => 0,
        15 => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_taxonomy_tid_term_page' => 0,
      'default_taxonomy_tid_node' => 0,
      'default_taxonomy_tid_limit' => 0,
      'default_taxonomy_tid_vids' => array(
        16 => 0,
        7 => 0,
        1 => 0,
        8 => 0,
        17 => 0,
        2 => 0,
        3 => 0,
        4 => 0,
        9 => 0,
        10 => 0,
        11 => 0,
        15 => 0,
        13 => 0,
        14 => 0,
        5 => 0,
      ),
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'faq' => 0,
        'access_type_downloadable' => 0,
        'agency' => 0,
        'catalog_type_data_apps' => 0,
        'catalog_type_data_service' => 0,
        'catalog_type_data_tools' => 0,
        'catalog_type_document' => 0,
        'catalog_type_raw_data' => 0,
        'dataset' => 0,
        'geospatial_metadata' => 0,
        'policy_program_data_quality' => 0,
        'policy_program_open_government' => 0,
        'policy_program_privacy' => 0,
        'profile' => 0,
        'sector' => 0,
        'statistical_metadata' => 0,
        'sub_agency' => 0,
        'sub_sector' => 0,
        'subject_keyword' => 0,
        'target_audience' => 0,
        'page' => 0,
        'imageflow' => 0,
        'country_data' => 0,
        'state_data_site' => 0,
        'rotating_panel' => 0,
        'feedback_reply' => 0,
        'feedback' => 0,
        'forum' => 0,
        'block' => 0,
        'blog' => 0,
        'community' => 0,
        'community_featured' => 0,
        'community_home' => 0,
        'community_suggestion' => 0,
        'downloadable' => 0,
        'embed_link_access_method' => 0,
        'feedback_review' => 0,
        'role_request' => 0,
        'story' => 0,
        'theme_file_uploader' => 0,
        'upload_docs' => 0,
        'webform' => 0,
        'whats_new' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        16 => 0,
        7 => 0,
        1 => 0,
        8 => 0,
        17 => 0,
        2 => 0,
        3 => 0,
        4 => 0,
        9 => 0,
        10 => 0,
        11 => 0,
        15 => 0,
        13 => 0,
        14 => 0,
        5 => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => '0',
      'validate_argument_group_node_type' => array(
        'community' => 0,
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'vid' => array(
      'operator' => 'in',
      'value' => array(
        15 => '15',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'vid',
      'table' => 'term_data',
      'field' => 'vid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', '<?php
	$this_page = $_SERVER[\'REQUEST_URI\'];
	$last =substr($this_page,0,strripos($this_page,\'/\'));
        $slast =substr($last,0,strripos($last,\'/\'));
	$third_last=strripos($slast,\'/\');
	$argument=substr($this_page,$third_last);
	
	//print_r($a);
	//$node=node_load($nid);
	//$title1=$node->title;

	//print \'<h2 class="page-title">\'.$title1.\'</h2>\';	
		$qpos;
     if(strlen(strstr($this_page,"?")))
      {
              $qpos=strpos($this_page,\'?\');
               
       }
	$li=strripos($this_page,\'/\');

       if($qpos!=0)
	$arg=substr($this_page,$li,2);
	else
	$arg=substr($this_page,$li);
       		
	if($arg==\'/1\'||$arg==\'/2\'||$arg==\'/3\'||$arg==\'/4\'||$arg==\'/5\')
	 {
	   $this_page=substr($this_page,0,$li);
	 } 
         global $base_url;

$view = views_get_current_view();
$arg0 = $view->args[0];
$arg1 = $view->args[1];

if($arg1==\'-\') $sub_agency=\'IS NULL\';
else $sub_agency="= $arg1";

if(!strlen(strstr($view->args[1], "main_"))>0 )
$raw=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid  INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_raw_data\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1"));
else
$raw=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_raw_data\' AND field_ds_agency_name_nid=$arg0 AND n.status=1 "));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$doc=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid  where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_document\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1"));
else
$doc=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_document\' AND field_ds_agency_name_nid=$arg0 AND n.status=1"));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$apps=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type IN (\'catalog_type_data_apps\') AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1"));
else
$apps=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type IN (\'catalog_type_data_apps\')  AND field_ds_agency_name_nid=$arg0 AND n.status=1"));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$tool=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid  where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_tools\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1 "));
else
$tool=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid  INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_tools\' AND field_ds_agency_name_nid=$arg0 AND n.status=1 "));

if(!strlen(strstr($view->args[1], "main_"))>0 )
$ser=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_service\' AND field_ds_agency_name_nid=$arg0 AND field_ds_sub_agency_nid $sub_agency AND n.status=1 "));
else
$ser=db_result(db_query("select count( ds.nid) from content_type_dataset ds Left join workflow_node wf on ds.nid=wf.nid  INNER JOIN node n on ds.nid=n.nid where wf.sid=10 and field_ds_catlog_type_type=\'catalog_type_data_service\' AND field_ds_agency_name_nid=$arg0 AND n.status=1 "));

 print \'<div class="catalog-tabs-menu fLeft" style="margin-top:7px;">\';
	 print \'<ul class="catalog-tabs">\';
	if($arg==\'/1\' && $raw )
  	 print \'Catalog Type: Raw Dataset Catalogs\';
	
	 if($arg==\'/2\' && $doc)
  	 print \'Catalog Type: Document Catalogs\';
	
	if($arg==\'/3\' && $apps)
  	 print \'Catalog Type: App Catalogs\';

	if($arg==\'/4\' && $tool)
  	 print \'Catalog Type: Tool Catalogs\';
	
	if($arg==\'/5\' && $ser)
  	 print \'Catalog Type: Service Catalogs\';

	print\'</ul></div>\';


?>
<div class="page-title-border cBoth">&nbsp;</div>
<iframe width="1px" height="1px" style="display: none;" name="download-frame"></iframe>');
  $handler->override_option('header_empty', 1);
  $handler->override_option('footer', '
* Asterisks denote agency-reported high-value datasets. ');
  $handler->override_option('footer_format', '2');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('empty', '<?php
global $base_url;

print \'<div style="font:bold 1.3em arial; padding-top:10px">No matching records found. Please try your search again or <a style="color:blue;" href="\'.$base_url.\'/suggest_dataset">suggest a dataset.</a></div>\';

?>


');
  $handler->override_option('empty_format', '3');
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'phpcode_1' => 'phpcode_1',
      'title' => 'title',
      'phpcode' => 'phpcode',
      'field_agency_short_name_value' => 'field_agency_short_name_value',
      'field_sa_subagency_short_name_value' => 'field_agency_short_name_value',
      'field_ds_sector_nid' => 'field_ds_sector_nid',
      'field_ds_description_value' => 'title',
    ),
    'info' => array(
      'phpcode_1' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '<br>',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'field_agency_short_name_value' => array(
        'sortable' => 0,
        'separator' => '/',
      ),
      'field_sa_subagency_short_name_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_ds_sector_nid' => array(
        'separator' => '',
      ),
      'field_ds_description_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'title',
  ));
  $handler->override_option('path', 'agency-publications/datasets-agency/pdf');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Page', 'page_3');
  $handler->override_option('fields', array(
    'phpcode_1' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<?php

$result=db_result(db_query("select * from content_type_dataset ds INNER JOIN content_type_policy_program_open_government ppog on ds.nid=ppog.nid where ds.nid=$data->nid AND ppog.field_ppog_high_value_dataset_value=\'Yes\' ")); 

if($result) return \'<h1>*</h1>\';


?>',
      'exclude' => 0,
      'id' => 'phpcode_1',
      'table' => 'customfield',
      'field' => 'phpcode',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '[title] ',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '50',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'field_ds_description_value' => array(
      'label' => 'Description',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<p>[field_ds_description_value]</p>',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '75',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_ds_description_value',
      'table' => 'node_data_field_ds_description',
      'field' => 'field_ds_description_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'phpcode' => array(
      'label' => 'Ratings',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'value' => '<?php

$avg_rating=variable_get(\'average_rating\',0);
$avg_votes=variable_get(\'average_votes\',0);
$value=calculate_ratings($data->nid,$avg_rating,$avg_votes);


 $vote1= rate_get_results(\'node\', $data->nid, 1);
  $vote2 = rate_get_results(\'node\', $data->nid, 2);
  $vote3=rate_get_results(\'node\', $data->nid, 3);
  $vote=$vote1[\'count\'];
  if($vote2[\'count\']>$vote) $vote=$vote2[\'count\'];
  if($vote3[\'count\']>$vote)$vote=$vote3[\'count\'];                 
  if($vote==1)   $votes=\'<span>(\'.$vote.\' vote)</span>\'; 
else		           
  $votes=\'<span>(\'.$vote.\' votes)</span>\'; 
return theme(\'fivestar_static\',$value).$votes;
?>',
      'exclude' => 0,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'field_ds_ministry_department_value' => array(
      'label' => 'Ministry/Department',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => 0,
        'multiple_number' => '0',
        'multiple_from' => '0',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_ds_ministry_department_value',
      'table' => 'node_data_field_ds_ministry_department',
      'field' => 'field_ds_ministry_department_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_ds_sector_value' => array(
      'label' => 'Sector/SubSector',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_ds_sector_value',
      'table' => 'node_data_field_ds_sector',
      'field' => 'field_ds_sector_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'name' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'ignorecase' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'add_table' => 0,
      'require_value' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        2 => 0,
        10 => 0,
        18 => 0,
        11 => 0,
        3 => 0,
        20 => 0,
        9 => 0,
        12 => 0,
        4 => 0,
        6 => 0,
        19 => 0,
        13 => 0,
        15 => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_taxonomy_tid_term_page' => 0,
      'default_taxonomy_tid_node' => 0,
      'default_taxonomy_tid_limit' => 0,
      'default_taxonomy_tid_vids' => array(
        16 => 0,
        7 => 0,
        1 => 0,
        8 => 0,
        17 => 0,
        2 => 0,
        3 => 0,
        4 => 0,
        9 => 0,
        10 => 0,
        11 => 0,
        15 => 0,
        13 => 0,
        14 => 0,
        5 => 0,
      ),
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'faq' => 0,
        'access_type_downloadable' => 0,
        'agency' => 0,
        'catalog_type_data_apps' => 0,
        'catalog_type_data_service' => 0,
        'catalog_type_data_tools' => 0,
        'catalog_type_document' => 0,
        'catalog_type_raw_data' => 0,
        'dataset' => 0,
        'geospatial_metadata' => 0,
        'policy_program_data_quality' => 0,
        'policy_program_open_government' => 0,
        'policy_program_privacy' => 0,
        'profile' => 0,
        'sector' => 0,
        'statistical_metadata' => 0,
        'sub_agency' => 0,
        'sub_sector' => 0,
        'subject_keyword' => 0,
        'target_audience' => 0,
        'page' => 0,
        'imageflow' => 0,
        'country_data' => 0,
        'state_data_site' => 0,
        'rotating_panel' => 0,
        'feedback_reply' => 0,
        'feedback' => 0,
        'forum' => 0,
        'block' => 0,
        'blog' => 0,
        'community' => 0,
        'community_featured' => 0,
        'community_home' => 0,
        'community_suggestion' => 0,
        'downloadable' => 0,
        'embed_link_access_method' => 0,
        'feedback_review' => 0,
        'role_request' => 0,
        'story' => 0,
        'theme_file_uploader' => 0,
        'upload_docs' => 0,
        'webform' => 0,
        'whats_new' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        16 => 0,
        7 => 0,
        1 => 0,
        8 => 0,
        17 => 0,
        2 => 0,
        3 => 0,
        4 => 0,
        9 => 0,
        10 => 0,
        11 => 0,
        15 => 0,
        13 => 0,
        14 => 0,
        5 => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => '0',
      'validate_argument_group_node_type' => array(
        'community' => 0,
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'vid' => array(
      'operator' => 'in',
      'value' => array(
        15 => '15',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'vid',
      'table' => 'term_data',
      'field' => 'vid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', '<?php 
global $base_url;

/* Calculating average ratings for all items (AR) */
$result=db_query("select distinct(content_id) as nid 
		from votingapi_vote V 
		LEFT JOIN node N on V.content_id=N.nid 
		where N.type=\'dataset\' ");
while($row=db_fetch_object($result))
{
	$sum=$sum+get_average_ratings($row->nid);
	$count++;
}

$AR=$sum/$count;
//print "AR=".$AR;

/*Calculating average number of votes for all items (AV) */
$result=db_query("select distinct(content_id) as nid 
		from votingapi_vote V 
		LEFT JOIN node N on V.content_id=N.nid 
		where N.type=\'dataset\' ");

$sum=0;
while($row=db_fetch_object($result))
{
	$sum=$sum+get_average_rating_votes($row->nid);
}
$AV=$sum/$count;
$AV=round($AV);

variable_set(\'average_rating\',$AR);
variable_set(\'average_votes\',$AV);
 
$this_page = $_SERVER[\'REQUEST_URI\'];


$view = views_get_current_view();
$arg0 = $view->args[0];
$arg1 = $view->args[1];

$this_page = rtrim(str_replace($view->args[1], \'\', $this_page),\'/\');

$cat = array(
		\'catalog_type_raw_data\'=> array(\'name\' => \'Raw Dataset Catalogs\', 	\'value\' => 0),
		\'catalog_type_document\'=> array(\'name\' => \'Document Catalogs\', 	\'value\' => 0),
		\'catalog_type_data_apps\'=>array(\'name\' => \'App Catalogs\', 	\'value\' => 0),
		\'catalog_type_data_tools\'=>array(\'name\' => \'Tool Catalogs\', 	\'value\' => 0),
		\'catalog_type_data_service\'=>array(\'name\' => \'Service Catalogs\',\'value\' => 0)
);

foreach($cat as $i => $c) {
	$query = "SELECT count(DISTINCT(node.nid)) cnt
		FROM node node 
		LEFT JOIN workflow_node workflow_node ON node.nid = workflow_node.nid 
		LEFT JOIN term_node term_node ON node.vid = term_node.vid 
		LEFT JOIN term_data term_data ON term_node.tid = term_data.tid 
		LEFT JOIN content_type_dataset node_data_field_ds_description ON node.vid = node_data_field_ds_description.vid 
		LEFT JOIN content_field_ds_ministry_department node_data_field_ds_ministry_department ON node.vid = node_data_field_ds_ministry_department.vid 
		WHERE ( node_data_field_ds_description.field_ds_catlog_type_type = \'$i\' ) 
		AND (node.type in (\'dataset\')) 
		AND (workflow_node.sid = 10) 
		AND (node.status = 1) 
		AND (term_data.vid in (\'15\')) 
		AND (term_data.name = \'$arg0\') ";
	
	
	$cat[$i][\'value\'] = db_result(db_query($query));
}


print \'<div class="catalog-tabs-menu fLeft" style="margin-top:7px;height:23px;">\';

print \'<ul class="catalog-tabs" style="position:absolute;">\';

foreach($cat as $i => $c) {
	if($c[\'value\']) {
		print \'<li><a style="padding:1px 30px;" class="\'.($arg1==$i?\' active \':\'\').\'" href="\'  .
			$this_page . \'/\' . $i . \'" title="\'.$c[\'name\'].\'">\'.$c[\'name\'].\'</a></li>\';
	}
}

print \'</ul></div>\';

print \'<div class="page-title-border cBoth">&nbsp;</div>\';

print l(\'<< Back to Ministry/Department Report\',\'agency-publications/agency-wise\', 
	array(\'attributes\' => 
		array(\'class\' => \'metricsbacklink\',\'title\'=>\'Back to Agency Wise Report\')
	)
);

$argument = $arg0;

print \'<div style="margin-top:-15px;" class="download-report">\';

print \'Download report as:\';
print \'<a  title="CSV Download" class="hyperlink" href="\'.$base_url.\'/federalagency/datasets-agency/csv/\'.
	$argument.\'?itemcount=500"><img alt="CSV" src="[token global site-url]sites/all/themes/ogpl_css3/images/csv.png" /></a> \' ;
print \'<a  title="XLS Download"  class="hyperlink" href="\'.$base_url.\'/federalagency/datasets-agency/xls/\'.
	$argument.\'?itemcount=500"><img alt="XLS" src="[token global site-url]sites/all/themes/ogpl_css3/images/xls.png" /></a>\';
print \'<a style="padding-left:3px;" title="PDF Download" class="hyperlink" href="\'.
	$base_url.\'/printpdf/agency-publications/datasets-agency/pdf/\'.$argument.\'?itemcount=500 ">
	<img alt="PDF" src="[token global site-url]sites/all/themes/ogpl_css3/images/pdf.png" /></a>\';
	
print \'</div>\';
?>');
  $handler->override_option('header_empty', 1);
  $handler->override_option('footer', '<br/>
<p>* Asterisks denote agency-reported high-value datasets. </p>');
  $handler->override_option('footer_format', '4');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('empty', '<?php
global $base_url;

print \'<div style="font:bold 1.3em arial; padding-top:10px">No matching records found. Please try your search again or <a style="color:blue;" href="\'.$base_url.\'/suggest_dataset" title="Suggest a dataset">suggest a dataset.</a></div>\';

?>


');
  $handler->override_option('empty_format', '3');
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'phpcode_1' => 'phpcode_1',
      'title' => 'title',
      'phpcode' => 'phpcode',
      'field_agency_short_name_value' => 'field_agency_short_name_value',
      'field_sa_subagency_short_name_value' => 'field_agency_short_name_value',
      'field_ds_sector_nid' => 'field_ds_sector_nid',
      'field_ds_description_value' => 'title',
    ),
    'info' => array(
      'phpcode_1' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '<br/>',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'field_agency_short_name_value' => array(
        'sortable' => 1,
        'separator' => '/',
      ),
      'field_sa_subagency_short_name_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_ds_sector_nid' => array(
        'separator' => '',
      ),
      'field_ds_description_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'title',
  ));
  $handler->override_option('path', 'agency-publications/datasets-agency');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));

  $views[$view->name] = $view;

  // Exported view: agency_wise_report
  $view = new view;
  $view->name = 'agency_wise_report';
  $view->description = 'Agency Wise Report';
  $view->tag = '';
  $view->base_table = 'node';
  $view->core = 6;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'phpcode' => array(
      'label' => 'Tid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 0,
      'value' => '<?php 
return $data->term_data_tid;
?>',
      'exclude' => 1,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_1' => array(
      'label' => 'Parent',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'value' => '<?php 
$sql_total = "SELECT parent
FROM  term_hierarchy 
WHERE tid = $data->term_data_tid";

$parent=db_result(db_query($sql_total));
return $parent;
?>',
      'exclude' => 1,
      'id' => 'phpcode_1',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'Ministry/Department',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_taxonomy' => 0,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'phpcode_2' => array(
      'label' => 'Raw Data',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php
$sql_total = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_raw_data\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($sql_total));

$sql_val = "SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_raw_data\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$val=db_result(db_query($sql_val ));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else 
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_2',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_3' => array(
      'label' => 'Documents',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php

$total=db_result(db_query("SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_document\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_document\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_3',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_4' => array(
      'label' => 'Apps',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_apps\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_apps\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 0,
      'id' => 'phpcode_4',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_5' => array(
      'label' => 'Tools',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_tools\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_tools\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_5',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_6' => array(
      'label' => 'Services',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_service\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_service\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10 "));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_6',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_7' => array(
      'label' => 'Total',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php
$view = views_get_current_view();
$arg0 = $view->args[0];

$catalog_cond = \'ds.field_ds_catlog_type_type IS NOT NULL AND \';			
if($arg0){
  $catalog_cond = "ds.field_ds_catlog_type_type = \'$arg0\' AND ";
}
$total_sql = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE $catalog_cond MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($total_sql));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE $catalog_cond ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 0,
      'id' => 'phpcode_7',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'changed' => array(
      'label' => ' Date Of Last Submission ',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'date_format' => 'custom',
      'custom_date_format' => 'd-m-Y',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
    'field_ds_catlog_type_item_id' => array(
      'label' => 'Catalog Type',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_ds_catlog_type_item_id',
      'table' => 'node_data_field_ds_catlog_type',
      'field' => 'field_ds_catlog_type_item_id',
      'relationship' => 'none',
    ),
    'phpcode_8' => array(
      'label' => 'Raw Data',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$sql_total = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_raw_data\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($sql_total));
return $total;
?>',
      'exclude' => 1,
      'id' => 'phpcode_8',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_9' => array(
      'label' => 'Raw Data High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$sql_val = "SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_raw_data\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$val=db_result(db_query($sql_val ));
return $val;
?>',
      'exclude' => 1,
      'id' => 'phpcode_9',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_10' => array(
      'label' => 'Apps',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_apps\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));
return $total;
?>',
      'exclude' => 1,
      'id' => 'phpcode_10',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_11' => array(
      'label' => 'Apps High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_apps\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

return $val;

?>',
      'exclude' => 1,
      'id' => 'phpcode_11',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'nid' => array(
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
    ),
    'delta' => array(
      'order' => 'DESC',
      'id' => 'delta',
      'table' => 'node_data_field_ds_ministry_department',
      'field' => 'delta',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'vid' => array(
      'operator' => 'in',
      'value' => array(
        15 => '15',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'vid',
      'table' => 'term_data',
      'field' => 'vid',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header_format', '3');
  $handler->override_option('header_empty', 0);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('distinct', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'nid' => 'nid',
      'phpcode' => 'phpcode',
      'phpcode_1' => 'phpcode_1',
      'name' => 'name',
      'phpcode_2' => 'phpcode_2',
      'phpcode_3' => 'phpcode_3',
      'phpcode_4' => 'phpcode_4',
      'field_ds_catlog_type_item_id' => 'field_ds_catlog_type_item_id',
      'phpcode_5' => 'phpcode_5',
      'phpcode_6' => 'phpcode_6',
      'phpcode_7' => 'phpcode_7',
    ),
    'info' => array(
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'phpcode_1' => array(
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'phpcode_2' => array(
        'separator' => '',
      ),
      'phpcode_3' => array(
        'separator' => '',
      ),
      'phpcode_4' => array(
        'separator' => '',
      ),
      'field_ds_catlog_type_item_id' => array(
        'separator' => '',
      ),
      'phpcode_5' => array(
        'separator' => '',
      ),
      'phpcode_6' => array(
        'separator' => '',
      ),
      'phpcode_7' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('views_data_export', 'CSV', 'views_data_export_1');
  $handler->override_option('title', 'CSV');
  $handler->override_option('items_per_page', '0');
  $handler->override_option('style_plugin', 'views_data_export_csv');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
    'attach_text' => 'CSV',
    'provide_file' => 1,
    'filename' => '%view--%timestamp-full.csv',
    'help' => '',
    'parent_sort' => 0,
    'separator' => ',',
    'quote' => 1,
    'trim' => 1,
    'replace_newlines' => 0,
    'newline_replacement' => '',
    'header' => 1,
    'encoding' => 'ASCII',
  ));
  $handler->override_option('row_plugin', '');
  $handler->override_option('path', 'federalagency/agency-wise/csv');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', 0);
  $handler->override_option('use_batch', '0');
  $handler = $view->new_display('views_data_export', 'XLS', 'views_data_export_2');
  $handler->override_option('items_per_page', '0');
  $handler->override_option('style_plugin', 'views_data_export_xls');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
    'attach_text' => 'XLS',
    'provide_file' => 1,
    'filename' => '%view--%timestamp-full .xls',
    'help' => '',
    'parent_sort' => 0,
  ));
  $handler->override_option('row_plugin', '');
  $handler->override_option('path', 'federalagency/agency-wise/xls');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array(
    'default' => 'default',
    'page_1' => 0,
  ));
  $handler->override_option('sitename_title', FALSE);
  $handler->override_option('use_batch', '0');
  $handler = $view->new_display('page', 'PDF', 'page_2');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode' => array(
      'label' => 'Tid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 0,
      'value' => '<?php 
return $data->term_data_tid;
?>',
      'exclude' => 0,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_1' => array(
      'label' => 'Parent',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'value' => '<?php 
$sql_total = "SELECT parent
FROM  term_hierarchy 
WHERE tid = $data->term_data_tid";

$parent=db_result(db_query($sql_total));
return $parent;
?>',
      'exclude' => 0,
      'id' => 'phpcode_1',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => 'Ministry/Department',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_taxonomy' => 0,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'phpcode_2' => array(
      'label' => 'Raw Data',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php
$sql_total = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_raw_data\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($sql_total));

$sql_val = "SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_raw_data\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$val=db_result(db_query($sql_val ));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else 
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_2',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_3' => array(
      'label' => 'Documents',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php

$total=db_result(db_query("SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_document\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_document\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_3',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_4' => array(
      'label' => 'Apps',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_apps\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_apps\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 0,
      'id' => 'phpcode_4',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_5' => array(
      'label' => 'Tools',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_tools\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_tools\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_5',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_6' => array(
      'label' => 'Services',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_service\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_service\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10 "));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_6',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_7' => array(
      'label' => 'Total',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php
$view = views_get_current_view();
$arg0 = $view->args[0];

$catalog_cond = \'ds.field_ds_catlog_type_type IS NOT NULL AND \';			
if($arg0){
  $catalog_cond = "ds.field_ds_catlog_type_type = \'$arg0\' AND ";
}
$total_sql = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE $catalog_cond MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($total_sql));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE $catalog_cond ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 0,
      'id' => 'phpcode_7',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'changed' => array(
      'label' => ' Date Of Last Submission ',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'date_format' => 'custom',
      'custom_date_format' => 'd-m-Y',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
    'field_ds_catlog_type_item_id' => array(
      'label' => 'Catalog Type',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_ds_catlog_type_item_id',
      'table' => 'node_data_field_ds_catlog_type',
      'field' => 'field_ds_catlog_type_item_id',
      'relationship' => 'none',
    ),
    'phpcode_8' => array(
      'label' => 'Raw Data',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$sql_total = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_raw_data\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($sql_total));
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_8',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_9' => array(
      'label' => 'Raw Data High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$sql_val = "SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_raw_data\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$val=db_result(db_query($sql_val ));
return $val;
?>',
      'exclude' => 0,
      'id' => 'phpcode_9',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_10' => array(
      'label' => 'Apps',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_apps\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_10',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_11' => array(
      'label' => 'Apps High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_apps\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

return $val;

?>',
      'exclude' => 0,
      'id' => 'phpcode_11',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('title', 'Ministry/Department Wise');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'nid' => 'nid',
      'phpcode_7' => 'phpcode_7',
      'field_agency_short_name_value' => 'field_agency_short_name_value',
      'title' => 'title',
      'phpcode' => 'phpcode',
      'phpcode_1' => 'phpcode_1',
      'phpcode_2' => 'phpcode_2',
      'phpcode_3' => 'phpcode_3',
      'phpcode_6' => 'phpcode_6',
      'phpcode_4' => 'phpcode_4',
      'phpcode_5' => 'phpcode_5',
    ),
    'info' => array(
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'phpcode_7' => array(
        'separator' => '',
      ),
      'field_agency_short_name_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'phpcode_1' => array(
        'separator' => '',
      ),
      'phpcode_2' => array(
        'separator' => '',
      ),
      'phpcode_3' => array(
        'separator' => '',
      ),
      'phpcode_6' => array(
        'separator' => '',
      ),
      'phpcode_4' => array(
        'separator' => '',
      ),
      'phpcode_5' => array(
        'separator' => '',
      ),
    ),
    'default' => 'title',
  ));
  $handler->override_option('path', 'agency-publications/agency-wise/pdf');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Page', 'page_3');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'phpcode' => array(
      'label' => 'Tid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 0,
      'value' => '<?php 
return $data->term_data_tid;
?>',
      'exclude' => 0,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_1' => array(
      'label' => 'Parent',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'value' => '<?php 
$sql_total = "SELECT parent
FROM  term_hierarchy 
WHERE tid = $data->term_data_tid";

$parent=db_result(db_query($sql_total));
return $parent;
?>',
      'exclude' => 0,
      'id' => 'phpcode_1',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => 'Ministry/Department',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'agency-publications/datasets-agency/[name]',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_taxonomy' => 0,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_2' => array(
      'label' => 'Raw Data',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php
$sql_total = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_raw_data\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($sql_total));

$sql_val = "SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_raw_data\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$val=db_result(db_query($sql_val ));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else 
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_2',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_3' => array(
      'label' => 'Documents',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php

$total=db_result(db_query("SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_document\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_document\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_3',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_4' => array(
      'label' => 'Apps',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_apps\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_apps\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\' <span style="color:red;">(\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 0,
      'id' => 'phpcode_4',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_5' => array(
      'label' => 'Tools',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_tools\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_tools\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_5',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_6' => array(
      'label' => 'Services',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_service\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_service\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10 "));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 1,
      'id' => 'phpcode_6',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'phpcode_7' => array(
      'label' => 'Total',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php
$view = views_get_current_view();
$arg0 = $view->args[0];

$catalog_cond = \'ds.field_ds_catlog_type_type IS NOT NULL AND \';			
if($arg0){
  $catalog_cond = "ds.field_ds_catlog_type_type = \'$arg0\' AND ";
}
$total_sql = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE $catalog_cond MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($total_sql));

$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE $catalog_cond ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

if($val)
return $total.\'<span style="color:red;"> (\'.$val.\')</span>\';
else return $total
?>',
      'exclude' => 0,
      'id' => 'phpcode_7',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'changed' => array(
      'label' => ' Date Of Last Submission ',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'date_format' => 'custom',
      'custom_date_format' => 'd-m-Y',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
    'field_ds_catlog_type_item_id' => array(
      'label' => 'Catalog Type',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'hide_alter_empty' => 1,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_ds_catlog_type_item_id',
      'table' => 'node_data_field_ds_catlog_type',
      'field' => 'field_ds_catlog_type_item_id',
      'relationship' => 'none',
    ),
    'phpcode_8' => array(
      'label' => 'Raw Data',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$sql_total = "SELECT count( DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_raw_data\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$total=db_result(db_query($sql_total));
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_8',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_9' => array(
      'label' => 'Raw Data High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 

$sql_val = "SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_raw_data\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10";
$val=db_result(db_query($sql_val ));
return $val;
?>',
      'exclude' => 0,
      'id' => 'phpcode_9',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_10' => array(
      'label' => 'Apps',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$total=db_result(db_query("SELECT count(DISTINCT ds.nid ) 
FROM content_type_dataset ds 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type = \'catalog_type_data_apps\') 
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));
return $total;
?>',
      'exclude' => 0,
      'id' => 'phpcode_10',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'phpcode_11' => array(
      'label' => 'Apps High Value',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'absolute' => 0,
        'link_class' => '',
        'alt' => '',
        'rel' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 1,
      'hide_alter_empty' => 0,
      'value' => '<?php 
$val=db_result(db_query("SELECT count( DISTINCT ds.nid )  
FROM  content_type_dataset ds 
INNER JOIN content_type_policy_program_open_government ppog ON ds.nid=ppog.nid 
INNER JOIN workflow_node WF On WF.nid=ds.nid 
LEFT JOIN content_field_ds_ministry_department MD ON MD.nid = ds.nid 
WHERE (ds.field_ds_catlog_type_type =\'catalog_type_data_apps\') 
AND ppog.	field_ppog_high_value_dataset_value=\'Yes\'  
AND MD.field_ds_ministry_department_value = $data->term_data_tid
AND WF.sid=10"));

return $val;

?>',
      'exclude' => 0,
      'id' => 'phpcode_11',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'nid' => array(
      'order' => 'ASC',
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'delta' => array(
      'order' => 'DESC',
      'id' => 'delta',
      'table' => 'node_data_field_ds_ministry_department',
      'field' => 'delta',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'vid' => array(
      'operator' => 'in',
      'value' => array(
        15 => '15',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'vid',
      'table' => 'term_data',
      'field' => 'vid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'dataset' => 'dataset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => 0,
        'identifier' => 'type',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'sid' => array(
      'operator' => 'in',
      'value' => array(
        10 => '10',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sid',
      'table' => 'workflow_node',
      'field' => 'sid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', '<?php

global $base_url;

print \'<h1 class="metrics-visitorstats-table-heading fLeft">Ministry/Department Wise</h1>\';

print \'<div class="download-report">Download report as: <a title="CSV Download"  class="hyperlink"  href="\'.$base_url.\'/federalagency/agency-wise/csv"><img alt="CSV" src="[token global site-url]sites/all/themes/ogpl_css3/images/csv.png" /></a> \' ;

print \'<a title="XLS Download"  class="hyperlink" href="\'.$base_url.\'/federalagency/agency-wise/xls"><img alt="XLS" src="[token global site-url]sites/all/themes/ogpl_css3/images/xls.png" /></a>\';

print \'<a style="padding-left:3px;" title="PDF Download" class="hyperlink" href="\'.$base_url.\'/printpdf/agency-publications/agency-wise/pdf"><img alt="PDF" src="[token global site-url]sites/all/themes/ogpl_css3/images/pdf.png" /></a></div>\';

print \'<div style="display:inline-block;"><p>Data Portal India offers a platform for government agencies to publish their raw datasets, documents, apps, tools and services, allowing important and featured ones to be marked as high value datasets. Get a consolidated view of Ministry/Department wise publications right here. Drill down to view individual datasets.</p></div>\';

?>

');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'summary' => '',
    'columns' => array(
      'nid' => 'nid',
      'name' => 'name',
      'phpcode' => 'phpcode',
      'phpcode_1' => 'phpcode_1',
      'phpcode_2' => 'phpcode_2',
      'phpcode_3' => 'phpcode_3',
      'phpcode_6' => 'phpcode_6',
      'phpcode_4' => 'phpcode_4',
      'phpcode_5' => 'phpcode_5',
      'changed' => 'changed',
      'phpcode_7' => 'phpcode_7',
    ),
    'info' => array(
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'phpcode' => array(
        'separator' => '',
      ),
      'phpcode_1' => array(
        'separator' => '',
      ),
      'phpcode_2' => array(
        'separator' => '',
      ),
      'phpcode_3' => array(
        'separator' => '',
      ),
      'phpcode_6' => array(
        'separator' => '',
      ),
      'phpcode_4' => array(
        'separator' => '',
      ),
      'phpcode_5' => array(
        'separator' => '',
      ),
      'changed' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'phpcode_7' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('path', 'agency-publications/agency-wise');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));

  $views[$view->name] = $view;

  return $views;
}
