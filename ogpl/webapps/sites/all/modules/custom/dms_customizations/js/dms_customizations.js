/*
 * By: India Team
 */
var dms_customization_time;
var dms_customization_id;
Drupal.behaviors.dms_customizations = function(context) {
  /* var field_elam_access_point = $('#edit-field-dsat-access-point-0-value-field-elam-access-point-0-url', context).val(); */
  
	var field_elam_access_point = 'http://example.com';
  
  $('#edit-field-dsat-access-point-0-value-field-elam-access-point-0-url', context)
  .bind('blur', function() {
	  if(field_elam_access_point != this.value && this.value != '') {
		  
		  var urlRegex = /(f|ht)tps?:\/\//g;
		  if(!urlRegex.test(this.value) && this.value != '') {
			  this.value = 'http://' + this.value;
		  } 
		  
		  $(this).parent().append('<div class="url_loading_content"><div class="url_loading"></div></div>');
		  
		  dms_customization_id = $(this).attr('id');
		  
		  clearTimeout(dms_customization_time);
		  
		  dms_customization_time = setTimeout(function(){dms_cust_remove_loading(dms_customization_id);},10000);
		  
		  $.getJSON(Drupal.settings.basePath + 'dms/accessurl/detail?url=' + escape(this.value) + '&op=addhttp&id=edit-field-dsat-access-point-0-value-field-elam-access-point-0-url', 
				  null, 
				  function(data){
			  		
			  		if(data.status) {
			  			$.getJSON(Drupal.settings.basePath+'dms/accesspoint/detail?url=' + escape(data.url), null, populateFileDetail);
			  		} else {
			  			var data = {};
			  			data.status = false;
			  			data.id 	= 'edit-field-dsat-access-point-0-value-field-elam-access-point-0-url';
			  			
			  			dmsLinkAddHTTP(data);
			  		}
		  });		
		  
	  } else if(this.value == '' )
		  this.value = field_elam_access_point;
		  
    return false;
  });
  
  $("#edit-field-ds-ministry-department-tids-hierarchical-select-selects-0", context).addClass('required');
  
  $('#edit-field-dsat-access-point-0-value-field-elam-access-point-0-url', context)
  .bind('focus', function() {
	  if(field_elam_access_point == this.value)
		  this.value = '';
  });
  
  $(document).load(function() {
	  $(".visualize-link").append('<a href="">Preview Visualize</a>');
	  alert("ok");
  });
  
  /*
  $('#edit-field-dsat-access-method-type-0-type', context)
  .bind('change', function() {
	  var access_method_type = this.value;
	  catalogLocationFieldChange(access_method_type);
  });
  
  $('#edit-field-ds-catlog-type-0-type', context)
  .bind('change', function() {
	  var access_method_type = $('#edit-field-dsat-access-method-type-0-type').val();
	  catalogLocationFieldChange(access_method_type);
  });
  */
  
  $('#edit-field-ds-access-url-0-url, input[id^="edit-field-ds-reference-url-"], input[id^="edit-field-dsat-access-point-0-value-field-ds-reference-url-"], input[id^="edit-field-dsat-downloadable-0-value-field-ds-reference-url-"]', context).blur(function() {
	  if (this.value != '') {
		  $(this).parent().append('<div class="url_loading_content"><div class="url_loading"></div></div>');
		  
		  var urlRegex = /(f|ht)tps?:\/\//g;
		  
		  if(!urlRegex.test(this.value)) {
			  this.value = 'http://' + this.value;
		  } 
		  
		  dms_customization_id = $(this).attr('id');
		  
		  clearTimeout(dms_customization_time);
		  
		  dms_customization_time = setTimeout(function(){dms_cust_remove_loading(dms_customization_id);},10000);
		  
		  $.getJSON(Drupal.settings.basePath + 'dms/accessurl/detail?url=' + escape(this.value) + 
				  '&op=addhttp&id=' + $(this).attr('id'), 
				  null, 
				  dmsLinkAddHTTP);
	  }
  });
  
  
  $.validator.addMethod("INphone", function(value, element) {
	  if(value == '' ) {
		  return true;
	  }
	  
	  var _regEx91 = /^\+91/;
	  var _regEx0 = /^0/;
	  
	  var ele_val = value;
	  
	  while (ele_val.substr(0,1) == '0' && ele_val.length>1) { 
		  ele_val = ele_val.substr(1,9999); 
	  }
	  
	  if(! _regEx91.test(ele_val)  && ele_val != '') {
		  ele_val = '+91' + ele_val;
	  }
	  
	  element.value = ele_val;
	  
	  value = ele_val;
	  
	  var regEx = /^\+91\d{7,10}$/;
	  
	  return regEx.test(value);
  }, "Phone Number is not valid");
  
  $.validator.addMethod("selectRequired", function(value, element) {
	  if(value == '' || value == 'label_0') {
		  return false;
	  }
	  return true;
  }, "Phone Number is not valid");
  
  if(typeof $('input[name^="field_ds_contact_phone_number"]') != 'undefined') {
	  $('input[name^="field_ds_contact_phone_number"]').each(function() {
		  var name 	= $(this).attr('name');
		  /*
		  $(this).blur(function() {
			  var _regEx91 = /^\+91/;
			  var _regEx0 = /^0/;
			  
			  var ele_val = $(this).val();
			  
			  while (ele_val.substr(0,1) == '0' && ele_val.length>1) { ele_val = ele_val.substr(1,9999); }
			  
			  $(this).val(ele_val);
			  
			  if(! _regEx91.test($(this).val())  && $(this).val() != '') {
				  $(this).val('+91' + $(this).val()); 
			  }
		  });
		  
		  */
		  
		  if(name == 'field_ds_contact_phone_number[0][value]') {
			  var rule = {
				  required	: true,
				  INphone	: true,
				  messages	: {
					  required	: "Contact Phone Number field is required.",
					  INphone	: "Contact Phone Number is not valid! e.g. +919876543210",
				  }
			  };
		  } else {
			  var rule = {
				  INphone	: true,
				  messages	: {
					  INphone	: "Contact Phone Number is not valid! e.g. +919876543210",
				  }
			  };
		  }
		  Drupal.settings['clientsideValidation']["forms"]["node-form"]["rules"][name] = rule;
		  
	  });
	  
	  if(typeof $('input[name="field_ds_sector[tids][hierarchical_select][selects][0]"]') != 'undefined'){
		  Drupal.settings['clientsideValidation']["forms"]["node-form"]["rules"]['field_ds_sector[tids][hierarchical_select][selects][0]'] = {
			  selectRequired: true,
			  messages: {
				  selectRequired: "Sector field is required."
			  }
		  };
	  }
	  
	  if(typeof $('input[name="field_ds_asset_jurisdiction[tids][hierarchical_select][selects][0]') != 'undefined'){
		  Drupal.settings['clientsideValidation']["forms"]["node-form"]["rules"]['field_ds_asset_jurisdiction[tids][hierarchical_select][selects][0]'] = {
			  selectRequired: true,
			  messages: {
				  selectRequired: "Asset Jurisdiction field is required."
			  }
		  };
	  }
	  
	  if(typeof $('input[name="field_ds_fax_number[0][value]') != 'undefined'){
		  Drupal.settings['clientsideValidation']["forms"]["node-form"]["rules"]['field_ds_fax_number[0][value]'] = {
			  INphone	: true,
			  messages	: {
				  INphone	: "Fax Number is not valid! e.g. +911124305296",
			  }
		  };
	  }
	  
	  if(typeof $('input[name="field_ds_catlog_type[0][type]') != 'undefined'){
		  Drupal.settings['clientsideValidation']["forms"]["node-form"]["rules"]['field_ds_catlog_type[0][type]'] = {
			  selectRequired: true,
			  messages	: {
				  selectRequired	: "Catalog Type field is required.",
			  }
		  };
	  }
	  
  }
}

var dmsLinkAddHTTP = function(data) {
	if(typeof data.id != 'undefined') {
		if(typeof $('#' + data.id).parent().find('.url_loading') != 'undefined' ) {
			$('#' + data.id).parent().find('.url_loading_content').remove();
		}
		
		$('#' + data.id).removeClass('dms_link_tick');
		$('#' + data.id).removeClass('dms_link_cancel');
		
		if(typeof data.status != 'undefined' && data.status) {
			$('#' + data.id).addClass('dms_link_tick');
		} else {
			$('#' + data.id).addClass('dms_link_cancel');
		}
	}
}

var catalogLocationFieldChange = function(value){
	if (typeof value != 'undefined') {
		  var catalog_location_element = 'select[id$="-catalog-location-value"], select[id$="-tool-location-value"]';
		  switch(value){
		  	case 'downloadable': // for access method Downloadable
		  		$(catalog_location_element).val('Internal');
		  		break;
		  	default:
		  		$(catalog_location_element).val('External');
		  }
	  } 
};

/*
 * This function will populate the Access Point Url Detail to the coresp[omding fields
 */
var populateFileDetail = function(result) {
  /* var result = Drupal.parseJson(response); */
	var data = {};
	data.status = result.status;
	data.id 	= 'edit-field-dsat-access-point-0-value-field-elam-access-point-0-url';
	
	dmsLinkAddHTTP(data);
		
  if(typeof result.status != 'undefined' && result.status) {
	  
	   if(typeof $('#edit-field-dsat-access-point-0-value-field-elam-file-size-0-value') != 'undefined' && typeof result.data.size != 'undefined')
		   $('#edit-field-dsat-access-point-0-value-field-elam-file-size-0-value').val(result.data.size);
	   
	   
	   if(typeof $('#edit-field-dsat-access-point-0-value-field-elam-file-format-value') != 'undefined' && typeof result.data.file_type != 'undefined')
		   $('#edit-field-dsat-access-point-0-value-field-elam-file-format-value').val(result.data.file_type);
	   
	   
	   if(typeof $('#edit-field-dsat-access-point-0-value-field-elam-compressed-format-value') != 'undefined' && typeof result.data.compressed != 'undefined')
		   $('#edit-field-dsat-access-point-0-value-field-elam-compressed-format-value').val(result.data.compressed);
	   
  } else {
	  /**/
	 
  }
}


function dms_cust_remove_loading(id){
	if(typeof $('#' + id).parent().find('.url_loading') != 'undefined' ) {
		$('#' + id).parent().find('.url_loading_content').remove();
	}
}