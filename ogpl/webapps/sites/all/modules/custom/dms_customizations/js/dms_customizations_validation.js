//Define a Drupal behaviour with a custom name
Drupal.behaviors.dms_customizationsBehavior = {
  attach: function (context) {
    //Add an eventlistener to the document reacting on the
    //'clientsideValidationAddCustomRules' event.
    $(document).bind('clientsideValidationAddCustomRules', function(event){
      //Add your custom method with the 'addMethod' function of jQuery.validator
      //http://docs.jquery.com/Plugins/Validation/Validator/addMethod#namemethodmessage
      jQuery.validator.addMethod("notValidUrl", function(value, element, param) {
    	var urlRegex = /(f|ht)tps?:\/\//g;
        return !urlRegex.test(value);
      }, jQuery.format('Must Enter a valid url'));
    });
  }
}