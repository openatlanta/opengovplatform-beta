<?php

/**
 * @file
 * Provide views field handler for dms_customizations.module.
 */

/**
 * Field handler to present a link to the node.
 */
class views_handler_field_allowed_node_operation extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['preview_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Preview link text'),
      '#default_value' => $this->options['preview_link_text'],
    );
    $form['download_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Download link text'),
      '#default_value' => $this->options['download_link_text'],
    );
    $form['approve_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Approve link text'),
      '#default_value' => $this->options['approve_link_text'],
    );
    $form['sendback_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Send back link text'),
      '#default_value' => $this->options['sendback_link_text'],
    );
    $form['publish_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Publish link text'),
      '#default_value' => $this->options['publish_link_text'],
    );
    $form['submit_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Submit link text'),
      '#default_value' => $this->options['submit_link_text'],
    );
    $form['edit_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Edit link text'),
      '#default_value' => $this->options['edit_link_text'],
    );
    $form['delete_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Delete link text'),
      '#default_value' => $this->options['delete_link_text'],
    );
    $form['update_request_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Update request link text'),
      '#default_value' => $this->options['update_request_link_text'],
    );  
    $form['delete_request_link_text'] = array(
      '#type' => 'textfield',
      '#description' => 'Leave blank to not show this link.',
      '#title' => t('Delete request link text'),
      '#default_value' => $this->options['delete_request_link_text'],
    );

    $form['display_workflow_state'] = array(
      '#type' => 'checkbox',
      '#description' => 'Enable to show current workflow state.',
      '#title' => t('Show current workflow state'),
      '#options' => array(0 => t('Hide'), 1 => t('Show')),
      '#default_value' => $this->options['display_workflow_state'],
    );
    $form['visualization_preview_link_text'] = array(
        '#type' => 'textfield',
        '#description' => 'Leave blank to not show this link.',
        '#title' => t('Preview Visualization'),
        '#default_value' => $this->options['visualization_preview_link_text'],
    );
    $form['visualization_approve_link_text'] = array(
        '#type' => 'textfield',
        '#description' => 'Leave blank to not show this link.',
        '#title' => t('Approve Visualization'),
        '#default_value' => $this->options['visualization_approve_link_text'],
    );
    
    $form['visualization_disapprove_link_text'] = array(
        '#type' => 'textfield',
        '#description' => 'Leave blank to not show this link.',
        '#title' => t('Disapprove Visualization'),
        '#default_value' => $this->options['visualization_disapprove_link_text'],
    );
    
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function possible_workflow_transitions($node) {
    $wid = workflow_get_workflow_for_type($node->type);
	
    $published_state = variable_get("workflow_node_revision_published_state_$wid",10);
    $actions = array();
    global $user;
    $roles = $user->roles;


    $choices = workflow_field_choices($node);

    if (!is_array($choices)) {
      return $actions;
    }

    if ($system_state = array_search('Draft', $choices)) {
      unset($choices[$system_state]);
    }

    $choice_keys = array_keys($choices);

    $current_state = workflow_node_current_state($node);
    $current_state_key = array_search($current_state, $choice_keys);

    $current_state_name = workflow_get_state_name($current_state);
    $actions['current_state'] = $current_state;
    $actions['current_state_name'] = $current_state_name;

    if (($current_state_key - 1) >= 0 ) {
      $author = user_load($node->uid);
      // If the logged in user has the Agency POC role and the node was created by a data steward show the sendback option
      if ($user->uid == 1 || !isset($roles['4']) || (isset($roles['4']) && isset($author->roles['3']))) {
      $actions['sendback'] = $choice_keys[$current_state_key - 1];
    }
    }

    if (($current_state_key + 1) < count($choice_keys) && $current_state_key != 0) {
      $actions['approve'] = $choice_keys[$current_state_key + 1];
      $actions['next'] = $choice_keys[$current_state_key + 1];
    }

    if ($current_state_key == 0 && ($current_state_key + 1) < count($choice_keys)) {
      $actions['submit'] = $choice_keys[$current_state_key + 1];
    }

    if (!empty($choices[$published_state]) && $current_state != $published_state) {
      $actions['publish'] = $published_state;
    }
   
    if ($current_state == $published_state) {
      $actions['update_and_delete_request'] = $published_state;
      $actions['update_request'] = $published_state;
      if(!in_array('Contributor', $author->roles)) {
        $actions['delete_request'] = $published_state;
      }
    }

    return $actions;
  }

    function custom_node_access($action, $wid, $node)
    {
        return node_access($action, $node); //DMS
    }

    function render($values) {
    global $user;
    global $base_url;
    $links = '';

    $nid = $values->{$this->aliases['nid']};
    $node = node_load($nid);
    module_load_include('inc', 'workflow_customizations', 'workflow_customizations.validation');
    //$validated = workflow_customizations_validate_node($node);
    
    $validated = 1;
    
    $actions = $this->possible_workflow_transitions($node);
	  $wid = workflow_get_workflow_for_type($node->type);
	  if($node->field_dsat_access_method[0][value] == 'Downloadable') {
	    $file_query = "SELECT F.filemime, F.filepath
      FROM content_type_dataset ds LEFT JOIN node n on ds.nid=n.nid
      LEFT JOIN workflow_node wf on ds.nid=wf.nid
      LEFT JOIN  content_type_downloadable as downloadable ON downloadable.vid = ds.field_dsat_downloadable_item_id
      LEFT JOIN files F on downloadable.field_dam_datafile_fid=F.fid
      WHERE ds.nid = ".$nid." AND  n.status=1 AND wf.sid=10 AND F.filemime IS NOT NULL
      GROUP BY F.filemime";
	    
	    $file_det=db_fetch_object(db_query($file_query));
	    
	    if(variable_get('file_downloads', FILE_DOWNLOADS_PUBLIC) == FILE_DOWNLOADS_PRIVATE){
	      $path = urlencode(str_replace(file_directory_path(), 'system/files', $file_det->filepath));
	    } else {
	      $path = $_SERVER['DOCUMENT_ROOT'] . base_path() . $file_det->filepath;
	    }
	    
	    $visualize_link = variable_get('frontend_url', 'http://data.gov.in').'/'.$path;
	  }
	  else
	  {
	    $visualize_link = $node->field_dsat_access_point[0]['value']['field_elam_access_point'][0]['url'];
	  }
    if ($this->options['display_workflow_state']) {
      $links.= $actions['current_state_name'] . '<br>';

      if (!$validated) {
        // $links .= '<em class="required">Dataset does not meet requirements</em><br>';
      }
    }

    if (isset($actions['approve']) && !empty($this->options['approve_link_text'])) {
      // No go without validation
      if ($validated && $actions['next'] != $actions['publish'] ) {
        $attributes = array('attributes' => array('class' => 'approve-link', 'title' => 'Approve the record for publishing'));
        $text = $this->options['approve_link_text'];
        $links .= l($text, url("node/$nid/workflow", array('query' => 'workflow_state=' . $actions['approve'] . '&destination=', 'absolute' => TRUE)), $attributes);
      }
    }

    if (isset($actions['submit']) && !empty($this->options['submit_link_text'])) {
      // No go without validation
      if ($validated) {
        $attributes = array('attributes' => array('class' => 'submit-link', 'title' => 'Submit this record for approval'));
        $text = $this->options['submit_link_text'];
        $links .= l($text, url("node/$nid/workflow", array('query' => 'workflow_state=' . $actions['submit'] . '&destination=', 'absolute' => TRUE)), $attributes);
      }
    }

    if (isset($actions['publish']) && !empty($this->options['publish_link_text'])) {
      // No go without validation
      if ($validated) {
      $attributes = array('attributes' => array('class' => 'publish-link', 'title' => 'Publish this record to the main website'));
      $text = $this->options['publish_link_text'];
      $links .= l($text, url("node/$nid/workflow", array('query' => 'workflow_state=' . $actions['publish'] . '&destination=', 'absolute' => TRUE)), $attributes);
    }
    }

    if (isset($actions['sendback']) && !empty($this->options['sendback_link_text'])) {
      $attributes = array('attributes' => array('class' => 'sendback-link', 'title' => 'Send this record back in workflow'));
      $text =$this->options['sendback_link_text'];
      $links .= l($text, url("node/$nid/workflow", array('query' => 'workflow_state=' . $actions['sendback'] . '&destination=', 'absolute' => TRUE)), $attributes);
    }

	if ($this->custom_node_access('update',$wid,$node) && !empty($this->options['edit_link_text'])) {
	  $attributes = array('attributes' => array('class' => 'edit-link', 'title' => 'Edit this record'));
	  $text = $this->options['edit_link_text'];
	  $links .= l($text, url("node/$nid/edit", array('query' => 'destination=', 'absolute' => TRUE)), $attributes);
	}	

    if ($this->custom_node_access('delete',$wid,$node) && !empty($this->options['delete_link_text'])) {
      $attributes = array('attributes' => array('class' => 'delete-link', 'title' => 'Delete this record'));
      $text = $this->options['delete_link_text'];
      $links .= l($text, url("node/$nid/delete", array('query' => 'destination=', 'absolute' => TRUE)), $attributes);
    }

    if (isset($actions['update_request']) && !empty($this->options['update_request_link_text']) && user_access('create dataset content')) {
      $attributes = array('attributes' => array('class' => 'update-request-link', 'title' => 'Update this published dataset'));
      $text = $this->options['update_request_link_text'];
      $links .= l($text, url("node/$nid/update_request", array('query' => 'destination=', 'absolute' => TRUE)), $attributes);
    }

    if (isset($actions['delete_request']) && !empty($this->options['delete_request_link_text'])  && user_access('create dataset content')) {
      $attributes = array('attributes' => array('class' => 'delete-request-link', 'title' => 'Delete this published dataset'));
      $text = $this->options['delete_request_link_text'];
      $links .= l($text, url("node/$nid/delete_request", array('query' => 'destination=', 'absolute' => TRUE)), $attributes);
    }

    if ($this->custom_node_access('view',$wid,$node) && !empty($this->options['preview_link_text'])) {
      $attributes = array('attributes' => array('class' => 'preview-link', 'title' => 'Preview this record'));
      $text = $this->options['preview_link_text'];
      $links .= l($text, url("node/$nid", array('query' => 'destination=', 'absolute' => TRUE)), $attributes);
    }

    if ($this->custom_node_access('view',$wid,$node) && !empty($this->options['download_link_text'])) {
      $attributes = array('attributes' => array('class' => 'download-csv-link', 'title' => 'Download this record in CSV format'));
      $text = $this->options['download_link_text'];
      $links .= l($text, url("node/$nid/view/csv", array('query' => 'destination=', 'absolute' => TRUE)), $attributes);
    }
    
    if($node->field_ds_catlog_type[0][type] == 'catalog_type_data_apps') {
      $visualize_status = FALSE;
    } else {
      $visualize_status = TRUE;
    }
    
    if ($node->field_ds_is_visual[0]['value'] == 1) {
      $visualization_approve_status = TRUE;
    } 
    else {
      $visualization_approve_status = FALSE;
    }
    
    if ($visualize_status && $this->custom_node_access('view',$wid,$node) && !empty($this->options['visualization_preview_link_text'])) {
      $attributes = array('attributes' => array('class' => 'preview-visualization', 'title' => 'Preview Visualization', 'target' => '_blank'));
      $text = $this->options['visualization_preview_link_text'];
      $links .= l($text, url("visualize", array('query' => array('url' => $visualize_link, 'backend' => variable_get('webservice_to_use', 'dataproxy')), 'absolute' => TRUE)), $attributes);
    }
    
    
    if (!$visualization_approve_status) {
      if ($visualize_status && $this->custom_node_access('view',$wid,$node) && !empty($this->options['visualization_approve_link_text'])) {
        $attributes = array('attributes' => array('class' => 'Approve-visualization', 'title' => 'Approve Visualization'));
        $text = $this->options['visualization_approve_link_text'];
        $links .= l($text, url("node/$nid/approvevisualization", array('query' =>  'destination=<front>', 'absolute' => TRUE)), $attributes);
      }
    }
    else {
      if ($visualize_status && $this->custom_node_access('view',$wid,$node) && !empty($this->options['visualization_disapprove_link_text'])) {
        $attributes = array('attributes' => array('class' => 'Disapprove-visualization', 'title' => 'Disapprove Visualization'));
        $text = $this->options['visualization_disapprove_link_text'];
        $links .= l($text, url("node/$nid/disapprovevisualization", array('query' =>  'destination=<front>', 'absolute' => TRUE)), $attributes);
      }
    }
    
    return $links;
  }
}

