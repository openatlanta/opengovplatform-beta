/**
 * Intercept ahah's success callback in order to load required css files
 * before allowing it to proceed.
 */
if (Drupal.ahah) {
  $.aop.around({target: Drupal.ahah.prototype, method: 'success'}, function(invocation) {
    var response = invocation.arguments[0];
    if (response.styles) {
      $(response.styles).prependTo('head');
    }
    invocation.proceed();
  });
}
