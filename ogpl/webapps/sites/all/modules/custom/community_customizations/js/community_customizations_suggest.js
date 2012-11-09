$(function() {
	/* community_customizations_get_content(); */
});

function community_customizations_get_content(modal_id) {
	if( !_ele_exist(modal_id) )
		modal_id = 'community_customizations_modal';
	
	$('body').append('<div style="display: none;"><div id="' + modal_id + '"></div></div>');
	
	if( _ele_exist($('#' + modal_id )) && _ele_exist($('.nodequeue-ajax-toggle')) ) {
		
		$('#' + modal_id ).append('<h3>Add This Dataset To:</h3><ul id="community_customizations_list"></ul>'+
				'If you don\'t find your community, Please '+
				'<a id="community_customizations_suggest_ajax" href="#block-formblock-community_suggestion">Suggest</a> !'+
				/* '<input type="button" class="form-submit" id="community_customizations_suggest" value="Suggest" /> ' + */ 
				'<div id="community_customizations_suggest_from"></div>');
		
		$('.nodequeue-ajax-toggle').appendTo('#community_customizations_list');
		
		$('#block-formblock-community_suggestion').hide();
		
		if( _ele_exist($.fancybox) ) {
			$('<a id="community_customizations_modal_link" href="#' + modal_id + '">').fancybox({
				'autoDimensions' : true,
				'height' : 400,
				'width' : 500, 
				'showCloseButton' : true ,
				'enableEscapeButton' : true,
				
			}).trigger("click");
			
			$("#community_customizations_suggest_ajax").click(function(){
				$('#block-formblock-community_suggestion').show();
				$('<a id="community_customizations_modal_link" href="#block-formblock-community_suggestion">').fancybox({
					'autoDimensions' : true,
					'height' : 400,
					'width' : 500, 
					'showCloseButton' : true ,
					'enableEscapeButton' : true,
					'onClosed'		: function(){
						$('#block-formblock-community_suggestion').hide();
					}
				}).trigger("click");
			});
			
			$("#fancybox-inner").live('change',function(){
				$.fancybox.resize();
				setTimeout(function() {$.fancybox.close();},5000);
			});
			
		}
		
		$('#community_customizations_suggest').click(function(){
			/*
			$.ajax({
				url: Drupal.settings.basePath + 'community_suggest/form',
				type: 'get',
				success: function(data){
					$('#community_customizations_suggest_from').html(html);
				}
			});
			*/
			
			$.getJSON(Drupal.settings.basePath + 'community_suggest/form', 
			  null, 
			  function(data){
		  		if(data.html)
		  			$('#community_customizations_suggest_from').html(data.html);
			});
			
		});
	}
}

if(typeof _ele_exist != 'function'){
	function _ele_exist(ele) {
		if(typeof ele != 'undefined' ) return true;
		return false;
	}
}