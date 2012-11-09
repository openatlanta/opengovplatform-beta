<div class='form form-layout-simple clear-block'>
  <?php  
    $group_ds_upload = $form['group_ds_upload'];
    $group_ds_contact_information = $form['group_ds_contact_information'];
    unset($form['group_ds_upload']);
    unset($form['group_ds_contact_information']);
  ?>
  <?php print drupal_render($form['group_ds_profile']); ?>
  <?php print drupal_render($form['group_ds_all_datasets']); ?>
  <?php print drupal_render($sidebar['taxonomy']); ?>
  <?php print drupal_render($form) ?>
  <?php print drupal_render($group_ds_contact_information); ?>
  <?php print drupal_render($group_ds_upload); ?>
  <?php if ($buttons): ?>
    <div class='buttons'><?php print drupal_render($buttons) ?></div>
  <?php endif; ?>
</div>