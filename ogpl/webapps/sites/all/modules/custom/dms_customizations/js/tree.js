$(function() {
	$(".tree .tree-toggle").click(function () {
	   $(this).next().next().animate({
		  height: "toggle", opacity: "toggle"
		}, "slow");
		$(this).toggleClass("opened");
		return false;
	}); 
});