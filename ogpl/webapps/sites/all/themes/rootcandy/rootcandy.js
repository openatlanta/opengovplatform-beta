$(function()
 {
  $("table tr").hover(
   function()
   {
    $(this).addClass("highlight");
   },
   function()
   {
    $(this).removeClass("highlight");
   }
  )
 }
)

$(document).ready(function() {
  $('body.admin-build-modules tr:has(:checkbox:disabled)').addClass('module-disabled');

  $("a[rel=external]").click(function() {
    this.target = "_blank";
  });

  $(".description").parent().each(function(){
    $(this).children('label').each(function(){
      $(this).removeClass("option");
      $(this).addClass("label-help");
    });
  });

});

/* Code for show/hide the block in workflow of backend Code starts */
$(function () {
	  
	  $("#edit-workflow-scheduled-date-wrapper").hide();
	  $("#edit-workflow-scheduled-hour-wrapper").hide();

	  $('#edit-workflow-scheduled-0').change(function() { 
		  $("#edit-workflow-scheduled-date-wrapper").hide();
		  $("#edit-workflow-scheduled-hour-wrapper").hide();
	  });
	  $('#edit-workflow-scheduled-1').change(function() { 
		  $("#edit-workflow-scheduled-date-wrapper").show();
		  $("#edit-workflow-scheduled-hour-wrapper").show();
	  });
	  
});

/* Code for show/hide the block in workflow of backend Code ends */
