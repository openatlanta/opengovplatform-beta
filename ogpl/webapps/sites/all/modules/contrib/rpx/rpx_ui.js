(function ($) {

Drupal.behaviors.rpxUIProfileFields = function (context) {
  $('.rpx-field-select:not(.rpx-processed)', context)
    .addClass('rpx-processed')
    .each(function() {
      var mid = getMID(this);
      var map = Drupal.settings.map;
      var rpx_fields = Drupal.settings.rpx_fields;

      this.initialValue = this.options[0].text;
      $(this).val(map[mid].fid);

      // Display the Engage datafield path in the label below the dropdown.
      $(this).bind('change keyup', function () {
        var fid = $(this).val();
        var path = fid in rpx_fields ? rpx_fields[fid].path : this.initialValue;
        $(this).siblings('.description').html(path);
      });
      // Trigger the above event on initial pageload to update the label.
      $(this).trigger('change', false);
  });
};

/**
 * Return the mapping ID for the element's row.
 */
function getMID(element) {
  var classList = $(element).attr('class').split(/\s+/);
  var mid = "";
  $.each(classList, function(index, item) {
    if (item.substr(0,4) == 'mid-') {
        mid = item.substr(4);
        return false;
    }
  });
  if (mid)
    return mid;
  else
    throw 'rpx_ui.js getMID(): element\'s class list does not contain a mid.';
}

Drupal.behaviors.rpxPathTree = function (context) {
  $('table.rpx-path-tree:not(.rpx-processed)', context)
    .addClass('rpx-processed')
    .each(function() {
      $(this).treeTable();
    });
};


Drupal.behaviors.rpxPathInsert = function (context) {
  Drupal.settings.rpxPathInput = $('.rpx-path-input', context).eq(0);

  $('.rpx-path-click-insert .rpx-path:not(.rpx-processed)', context)
    .addClass('rpx-processed')
    .each(function() {
      var newThis = $('<a href="javascript:void(0);" title="' + Drupal.t('Insert this path into your form') + '">' + $(this).html() + '</a>').click(function() {
        Drupal.settings.rpxPathInput.val($(this).text());
        $('html,body').animate({scrollTop: $('.rpx-field-title-input').offset().top}, 500);
        return false;
      });
      $(this).html(newThis);
    });
};

})(jQuery);
