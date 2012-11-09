/**
 * jQuery SeqPar - jQuery plugin to be able to run an array of asynchronous functions in sequence or in parallel.
 */
(function($){

/**
 * seq
 * Executes an array of asynchronous functions sequentially.
 * 
 * @param Array a
 *    An array of functions, each one assumed to take a single parameter, 
 *    a callback function that's triggered when the operation started by 
 *    the function is complete.
 * @param Function callback
 *    A function to run when the last input function has completed.
 */
$.seq = function(a, callback) {
  if (!a || !a.length) {
    callback(); 
  }
  else {
    a[0](function() {
      $.seq(a.slice(1), callback);
    });
  }
};

/**
 * par
 * Executes an array of asynchronous functions in parallel.
 * 
 * @param Array a
 *    An array of functions, each one assumed to take a single parameter, 
 *    a callback function that's triggered when the operation started by 
 *    the function is complete.
 * @param Function callback
 *    A function to run when all input functions have completed.
 */
$.par = function(a, callback) {
  if (!a || !a.length) {
    callback(); 
  }
  else {
    var k = 0; 
    for (var i = 0; i < a.length; i++) {
      a[i](function() {
        if (k++ == a.length) {
          callback();
        }
      });
    }
  }   
};
	
})(jQuery);

