$(function() {
	$('#header_internal').hide();
	$("#mini-panel-community_tabs .ui-tabs-nav li a").click(function() {
		if ($(this).parent().hasClass('first')) {
			$('.community_header').show();
			$('#header_internal').hide();
		} else {
			$('.community_header').hide();
			$('#header_internal').show();
		}
	});
	
	 $('form#user-register').find('fieldset').each(function(index)
	{
		if(index == 1)
		{
			$(this).hide();
		}
	});
});

