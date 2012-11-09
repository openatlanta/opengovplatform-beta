Drupal.ahahScriptEnsurer = {};

/**
 * Load multiple scripts sequentially and then execute the callback
 */
Drupal.ahahScriptEnsurer.getScripts = function(aScripts, callback) {
  var aFunctions = [];
  for (var i=0; i < aScripts.length; i++) {
    aFunctions[i] = function(callback) {
      $.getScript(arguments.callee.sScript, callback);
    };
    aFunctions[i].sScript = aScripts[i];
  }
  $.seq(aFunctions, callback);
}

/**
 * Intercept ahah's success callback in order to load required scripts
 * before allowing it to proceed.
 */
if (Drupal.ahah) {
  $.aop.around({target: Drupal.ahah.prototype, method: 'success'}, function(invocation) {
    var response = invocation.arguments[0];
    if (response.scripts) {
      var aScripts = response.scripts.match(/src=".*?"/ig);
      for (var i=0; i < aScripts.length; i++) {
        aScripts[i] = aScripts[i].substr(5, aScripts[i].length - 6);
      }
      Drupal.ahahScriptEnsurer.getScripts(aScripts, function() {
        invocation.proceed();
      });
    }
    else {
      invocation.proceed();
    }
  });
}
