/**
 * Setup all forms to send the pageBuildId when they are submitted with AJAX.
 */
Drupal.behaviors.ahahPageStorage = function(context) {
  $('form:not(.ahahPageStorage-processed)', context).each(function() {
    $(this)
      .bind('form-submit-validate', function(oEvent, aDataToSubmit) {
        aDataToSubmit.push( {name: 'ahah_page_storage[page_build_id]', value: Drupal.settings.ahahPageStorage.pageBuildId} );
      })
      .addClass('ahahPageStorage-processed');
  });
};
