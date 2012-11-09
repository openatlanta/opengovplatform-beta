(function ($) {

Drupal.behaviors.rpx = function (context) {
  function finishCallback(results) {
    var setting = Drupal.settings.rpx.clicked_link_settings;
    if ('cookie' in setting) {
      $.each(results, function(key, provider) {
        if (provider.success) {
          document.cookie = 'rpx_social_' + setting.cookie.type + '=' + setting.cookie.id + '; path=/';
          location.replace(Drupal.settings.basePath + '?q=rpx/cookie_handler&destination=' + location.href);
          return false;
        }
      });
    }
  }
  function popupSocial() {
    RPXNOW.loadAndRun(['Social'], function () {
      var post = Drupal.settings.rpx.clicked_link_settings.post;
      var activity = new RPXNOW.Social.Activity(
        post.label,
        post.linktext,
        post.link
      );
      if ('comment' in post) {
        activity.setUserGeneratedContent(post.comment);
      }
      if ('summary' in post) {
        activity.setDescription(post.summary);
      }
      if ('title' in post) {
        activity.setTitle(post.title);
      }
      RPXNOW.Social.publishActivity(activity, {finishCallback: finishCallback});
    });
  };
  if ('rpx' in Drupal.settings && 'atonce' in Drupal.settings.rpx) {
    Drupal.settings.rpx.clicked_link_settings = Drupal.settings.rpx.atonce;
    popupSocial();
  }
  $('.rpx-link-social:not(.rpx-processed)', context)
    .addClass('rpx-processed')
    .each(function() {
      $(this).bind('click', function(e) {
        Drupal.settings.rpx.clicked_link_settings = Drupal.settings.rpx[$(this).attr('id')];
        popupSocial();
        return false;
    });
  });
};

})(jQuery);
