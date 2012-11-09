<?php

/**
 * Implementation of hook_default_panels_mini().
 */
function what_s_new_default_panels_mini() {
  $export = array();

  $mini = new stdClass;
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'new_dataset';
  $mini->category = '';
  $mini->admin_title = 'Front End Whats New ';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display;
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 3,
          1 => 'main-row',
          2 => 2,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'reg3',
          1 => 'reg1',
          2 => 'reg2',
        ),
        'parent' => 'main',
        'class' => 'topPanel',
      ),
      'reg1' => array(
        'type' => 'region',
        'title' => 'reg1',
        'width' => '14.4939070646945',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'whats-new-block alpha one',
      ),
      'reg2' => array(
        'type' => 'region',
        'title' => 'reg2',
        'width' => '19.501405845479436',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'whats-new-block alpha one',
      ),
      'reg3' => array(
        'type' => 'region',
        'title' => 'reg3',
        'width' => '32.7083150109141',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'whats-new-block alpha one',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'reg1__',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'reg1__' => array(
        'type' => 'region',
        'title' => 'reg1',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'reg1_',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'reg1_' => array(
        'type' => 'region',
        'title' => 'reg1',
        'width' => 100,
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'reg2' => NULL,
      'reg3' => NULL,
      'reg1' => NULL,
      'reg1_' => NULL,
      'reg2_' => NULL,
      'reg1__' => NULL,
    ),
    'reg1' => array(
      'style' => 'default',
    ),
    'reg3' => array(
      'style' => 'default',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->pid = 'new-1';
    $pane->panel = 'reg1';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1452';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['reg1'][0] = 'new-1';
    $pane = new stdClass;
    $pane->pid = 'new-2';
    $pane->panel = 'reg1';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1453';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'image-padding',
    );
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-2'] = $pane;
    $display->panels['reg1'][1] = 'new-2';
    $pane = new stdClass;
    $pane->pid = 'new-3';
    $pane->panel = 'reg1_';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1448';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'main-title-padding',
    );
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-3'] = $pane;
    $display->panels['reg1_'][0] = 'new-3';
    $pane = new stdClass;
    $pane->pid = 'new-4';
    $pane->panel = 'reg1__';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1449';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-4'] = $pane;
    $display->panels['reg1__'][0] = 'new-4';
    $pane = new stdClass;
    $pane->pid = 'new-5';
    $pane->panel = 'reg2';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1454';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-5'] = $pane;
    $display->panels['reg2'][0] = 'new-5';
    $pane = new stdClass;
    $pane->pid = 'new-6';
    $pane->panel = 'reg2';
    $pane->type = 'block';
    $pane->subtype = 'web_feed_aggregator-0';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'rss-padding rss-lists',
    );
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-6'] = $pane;
    $display->panels['reg2'][1] = 'new-6';
    $pane = new stdClass;
    $pane->pid = 'new-7';
    $pane->panel = 'reg2';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1450';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $display->content['new-7'] = $pane;
    $display->panels['reg2'][2] = 'new-7';
    $pane = new stdClass;
    $pane->pid = 'new-8';
    $pane->panel = 'reg2';
    $pane->type = 'block';
    $pane->subtype = 'nodeblock-1451';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'image-padding',
    );
    $pane->extras = array();
    $pane->position = 3;
    $display->content['new-8'] = $pane;
    $display->panels['reg2'][3] = 'new-8';
    $pane = new stdClass;
    $pane->pid = 'new-9';
    $pane->panel = 'reg3';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Front End Latest News Block Header',
      'title' => '',
      'body' => '<div class="content">
<div><!-- <a href="latestnews"> -->
<img class="latest-news-img" style="width: 288px; height: 155px;" title="Latest News" src="[token global site-url]sites/all/themes/ogpl_css2/images/governmentcommunications_banner.png" alt="Latest News" />
<!-- </a> -->
</div>
<div class="block-data-whats-new">Watch this space to keep yourself updated on the latest Data Portal India happenings and introductions.</div>
</div>',
      'format' => '3',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-9'] = $pane;
    $display->panels['reg3'][0] = 'new-9';
    $pane = new stdClass;
    $pane->pid = 'new-10';
    $pane->panel = 'reg3';
    $pane->type = 'views';
    $pane->subtype = 'whats_new';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 1,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-10'] = $pane;
    $display->panels['reg3'][1] = 'new-10';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['new_dataset'] = $mini;

  return $export;
}
