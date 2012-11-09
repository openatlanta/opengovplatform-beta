// JavaScript Document
var _GLOBAL_CNT = 0;
var slideTimeIn;
	/*
	function startscroller() {
	    var sObj = $("#scroll-content");
	    var inContHeight = $("#scroll-content").find("ul:first").height();
	    if (inContHeight > $(sObj).parent().height()) {
	        if (Math.abs(_GLOBAL_CNT) >= parseInt($(sObj).height())) {
	            _GLOBAL_CNT = 0;
	        }
	        _GLOBAL_CNT -= 1;
	        $(sObj).css("marginTop", _GLOBAL_CNT + "px");
	        $("#play").show();
	        $("#stop").show();
	    } else {
	        $(sObj).css("marginTop", "0px");
	        $("#play").hide();
	        $("#stop").hide();
	        _GLOBAL_CNT = 0;
	    }
	    slideTimeIn = setTimeout("startscroller()", 40);
	}
	*/


function togglesDiv(class_name) {
    switch (class_name.trim()) {
        case 'contactOwner':
        case 'contactOwner last':
            $('#web-contact-owner-form').parent().fadeIn("slow");
            $('#web-contact-owner-form-errors.error').show();
            //$('#clientsidevalidation-web-contact-owner-form-errors').show("fast");
            $('.clear-block .ratings-block').parent().hide();
            $('#ratings-form-errors.error').hide();
            //$('#feedback-comment-form').parent().parent().hide();
            $('#block-vrm_customization-0').hide();
            $('.embed-block').hide();
            $('body.dataset-page #comments').hide();
            $('#comment-form-errors.error').hide();
            break;
        case 'ratings':
        case 'ratings first':
            //$('#feedback-comment-form').parent().parent().fadeIn("slow");
            $('#ratings-form-errors.error').show();
            $('#block-vrm_customization-0').fadeIn("slow");
            $('.clear-block .ratings-block').parent().show();
            $('#web-contact-owner-form').parent().hide();
            $('#web-contact-owner-form-errors.error').hide();
            $('.embed-block').hide();
            $('body.dataset-page #comments').hide();
            $('#comment-form-errors.error').hide();
            break;
        case 'embed':
            $('.embed-block').fadeIn("slow");
            $('.clear-block .ratings-block').parent().hide();
            $('#ratings-form-errors.error').hide();
            $('#web-contact-owner-form').parent().hide();
            $('#web-contact-owner-form-errors.error').hide();
            //$('#feedback-comment-form').parent().parent().hide();
            $('#block-vrm_customization-0').hide();
            $('body.dataset-page #comments').hide();
            $('#comment-form-errors.error').hide();
            break;
        case 'discuss':
            $('body.dataset-page #comments').fadeIn("slow");
            $('.clear-block .ratings-block').parent().hide();
            $('#ratings-form-errors.error').hide();
            $('#web-contact-owner-form').parent().hide();
            $('#web-contact-owner-form-errors.error').hide();
            //$('#feedback-comment-form').parent().parent().hide();
            $('#block-vrm_customization-0').hide();
            $('.embed-block').hide();
            $('#comment-form-errors.error').show();
            break;
    }
}
function togglesTab(tab_class_name) {
    switch (tab_class_name) {
        case 'recent_catalogs':
            $('#recent_catalogs').show();
            $('#popular_catalogs').hide();
            break;
        case 'popular_catalogs':
            $('#popular_catalogs').show();
            $('#recent_catalogs').hide();
            break;
    }
}
function textCounter(max, textarename, desc) {
    if (document.getElementById(textarename).value.length > parseInt(max)) {
        document.getElementById(textarename).value = document.getElementById(textarename).value.substring(0, max)
    } else {
        var txtlength = document.getElementById(textarename).value.length;
        desc = desc ? desc : 'feedback-textarea-limit-count';
        $('#' + desc).html(parseInt(max) - txtlength);
    }
}
function add_to_favourites() {
    if (document.all) window.external.AddFavorite(location.href, document.title);
    else if (window.sidebar)window.sidebar.addPanel(document.title, location.href, ' ');
    else if (window.opera && window.print) {
        alert("Please use your browser's bookmarking facility to create a bookmark");
    } else if (window.chrome) {
        alert("Please use your browser's bookmarking facility to create a bookmark");
    }
}
function mesgCounters(max, textarename, desc) {
    test = $('#' + textarename).val();
    if (test.length > parseInt(max)) {
        var text = $('#' + textarename).val().substr(0, max);
        $('#' + textarename).val(text);
    }
    else {
        var txtlength = test.length;
        desc = desc ? desc : 'message-textarea-limit-count';
        $('#' + desc).html(parseInt(max) - txtlength);
    }
}

$(document).ready(function () {
    $.ajax({
        url:'//s7.addthis.com/js/250/addthis_widget.js#pubid=xa-4f0d8e4b63d561d0',
        dataType:"script",
        success:function () {
            addthis.init();
        }
    });
    $('.feed-item-body').each(function (index) {
        $(this).html($(this).html().replace(/(&nbsp;)*/g, ""));
        $(this).html($(this).html().replace(/(<br>)*/g, ""));
    });
    if ($(".js-disable-hide").length > 0) {
        $(".js-disable-hide").removeClass('js-disable-hide');
    }
    $('.js-disable-show').each(function (index) {
        $(this).remove();
    });
    $('.block-contact_owner h2').each(function (index) {
        if ($.trim($(this).html()) == 'Contact Dataset Owner') {
            $(this).remove();
        }
    });
    if ($("#node-form").length > 0) {
        var action_url = $("#node-form").attr('action');
        if (action_url.toLowerCase().indexOf("contactus") >= 0) {
            $('#node-form select').each(function (index) {
                $(this).addClass('category-field');
                $(this).wrap('<div class="category-id" />');
            });
        }
    }
    if ($("#web-contact-owner-form").length > 0) {
        $('#web-contact-owner-form select').each(function (index) {
            $(this).addClass('purpose-field');
            $(this).wrap('<div id="contactowner-id" />');
        });
    }
    if ($('.preview-hide').length > 0) {
        $('.preview-hide').removeClass('preview-hide');
    }
    if ($('.imageflow-visible').length > 0) {
        $('.imageflow-visible').removeClass('imageflow-visible');
    }
    $("#context-block-region-text_resize").hide();
    if ($('#web-contact-owner-form').length > 0) {
        var datasetTitle = $('input[name="dataset-title"]').val();
        $('select[name="purpose"]').change(
            function () {
                purpose = $('select[name="purpose"]').val();
                switch (purpose) {
                    case 'Copyright Violation':
                        $('input[name="subject"]').val('Your dataset "' + datasetTitle + '" has been flagged for copyright violation');
                        break;
                    case 'Offensive Content':
                        $('input[name="subject"]').val('Your dataset "' + datasetTitle + '" has been flagged for offensive content');
                        break;
                    case 'Spam or Junk':
                        $('input[name="subject"]').val('Your dataset "' + datasetTitle + '" has been flagged as potential spam');
                        break;
                    case 'Personal Information':
                        $('input[name="subject"]').val('Your dataset "' + datasetTitle + '" has been flagged for containing personal information');
                        break;
                    case 'Other':
                        $('input[name="subject"]').val('data.gov.in: Feedback on "' + datasetTitle + '" dataset');
                        break;
                }
            }).trigger("change");
    }

    /* Search form prefill data*/
    if ($('#views-exposed-form-Catalogs-Search-page-1').length > 0) {
        if ($(".mainHeading h1").html() != "Search") {
        	/* var _fielVal = "Search for " + $(".mainHeading h1").html(); */
        	
        	$(".view-Catalogs-Search .views-widget-filter-keys label").html("Search for " + $(".mainHeading h1").html());
        	
            var _fielVal = "Search terms";
            
            if ($('input[name="keys"]').val() == "") {
                $('input[name="keys"]').val(_fielVal);
            }
            $('input[name="keys"]').blur(function () {
                if ($(this).val() == "") {
                    $(this).val(_fielVal);
                }
            });

            $('input[name="keys"]').focus(function () {
                if ($(this).val() == _fielVal) {
                    $(this).val("");
                }
            });
        }
    }

    if ($(".metrics-menu").length > 0) {
        var repString = "http://" + window.location.hostname;
        var turl = location.href.replace(repString, '');
        var cmpstring = turl.substring(turl.indexOf('/'), turl.lastIndexOf('/'));
        cmpstring = cmpstring.substring(turl.indexOf('/'), cmpstring.lastIndexOf('/'));


        $(".metrics-menu .menuparent a").each(function () {
            var activemode = ($(this).attr('href').indexOf('top10datasetreport') > -1 && turl.indexOf('top10datasetreport') > -1);
            if (cmpstring == $(this).attr('href') || activemode) {
                $(this).addClass('active');
                $(this).parents(".menuparent").addClass('active-trail');
            }
        });


        if ($(".metrics-menu .menuparent a").hasClass("active")) {
            $(".metrics-menu .menuparent a").parent(".active-trail").find("a").filter(":first").addClass("active");
        }
    }


    if ($(".resize").length > 0) {
        $(".resize ul li a").each(function (index) {
            text = $(this).find('img').attr('alt');
            switch (text) {
                case 'Decrease':
                    $(this).attr('title', 'Decrease Text Size');
                    $(this).find('img').attr('alt', 'Decrease Text Size');
                    break;
                case 'Normal':
                    $(this).attr('title', 'Normal Text Size');
                    $(this).find('img').attr('alt', 'Normal Text Size');
                    break;
                case 'Increase':
                    $(this).attr('title', 'Increase Text Size');
                    $(this).find('img').attr('alt', 'Increase Text Size');
                    break;
            }
        });
    }
    if ($('#mainContent .content .dataset fieldset.group-ds-upload').length > 0) {
        $('#mainContent .content .dataset fieldset.group-ds-upload').find('legend').html('Download');
    }
    var page_full_url = $(location).attr('href');
    page_url_index = page_full_url.indexOf('showrating');
    if (page_url_index != -1) {
        $('.clear-block .ratings-block').parent().hide();
        $('#block-vrm_customization-0').hide();
        
        $('#web-contact-owner-form').parent().show();
        
        $(".dataset #tabs-block li").each(function (index) {
            $(this).removeClass('active');
            if ($(this).hasClass('ratings')) {
                $(this).addClass('active');
            }
        });
    } else {
        if (page_full_url.indexOf('embed=1') != -1 || page_full_url.indexOf('print=1') != -1) {
            $('#web-contact-owner-form').parent().show();
        } else {
        	$('#web-contact-owner-form').parent().hide();
        }
        
        $('.clear-block .ratings-block').parent().show();
        $('#block-vrm_customization-0').show();
       
    }
    $('.embed-block').hide();


    $('#tabs-block li').click(function () {
        $('#tabs-block li').removeClass('active');
        class_name = $(this).attr('class');
        $(this).addClass('active');
        togglesDiv(class_name);
    });

    $(".anchor-links a").click(function () {
        $('#tabs-block li').removeClass('active');
        if ($(this).attr('rel') == "contactOwner") {
            $($('#tabs-block li').get(0)).addClass('active');
        }
        if ($(this).attr('rel') == "ratings") {
            $($('#tabs-block li').get(1)).addClass('active');
        }
        if ($(this).attr('rel') == "embed") {
            $($('#tabs-block li').get(2)).addClass('active');
        }
        if ($(this).attr('rel') == "discuss") {
            $($('#tabs-block li').get(3)).addClass('active');
        }
        togglesDiv($(this).attr('rel'));
    });

//embed code functionality
    if ($('.embed-block').length > 0) {
        var text_area_content = '<div><iframe width="500px" title=":title" height="425px" src=":page_url" frameborder="1" scrolling="auto"></iframe></div>';
        var page_url = $(".hidden-embed-url").val();
        var title = $(this).attr('title');
        text_area_content = text_area_content.replace(':title', title);
        text_area_content = text_area_content.replace(':page_url', page_url);
        $('.embed-block textarea#embed_code').val(text_area_content);
        $('.econf-block #small').addClass('econf-block-selected-color');
    }

    $(".iframe-dimensions").click(function () {
        $(".iframe-dimensions").removeClass("econf-block-selected-color");
        $(this).addClass("econf-block-selected-color");
        var element_id = $(this).attr('id');
        var embed_html = $('.embed-block textarea#embed_code').val();
        var width;
        var height;
        var new_width = 500;
        var new_height = 425;
        var is_width = true;
        var offset_width = embed_html.indexOf('width');
        var offset_height = embed_html.indexOf('height');
        var string_length = embed_html.length;
        var html_1st_part = '';
        var html_2nd_part = '';
        if (offset_width > offset_height) {
            is_width = false;
            html_1st_part = embed_html.substring(0, offset_width);
            html_2nd_part = embed_html.substring(offset_width, string_length);
        } else {
            html_1st_part = embed_html.substring(0, offset_height);
            html_2nd_part = embed_html.substring(offset_height, string_length);
        }
        width = $($('.embed-block textarea#embed_code').val()).find('iframe').attr('width');
        height = $($('.embed-block textarea#embed_code').val()).find('iframe').attr('height');
        if (width.indexOf("px") == -1) {
            width = width + 'px';
        }
        if (height.indexOf("px") == -1) {
            height = height + 'px';
        }
        switch (element_id) {
            case 'large':
                new_width = 950;
                new_height = 808;
                if (is_width) {
                    html_1st_part = html_1st_part.replace(width, new_width + 'px');
                    html_2nd_part = html_2nd_part.replace(height, new_height + 'px');
                } else {
                    html_1st_part = html_1st_part.replace(height, new_height + 'px');
                    html_2nd_part = html_2nd_part.replace(width, new_width + 'px');
                }
                embed_html = html_1st_part + html_2nd_part;
                $('#ewidth').val(new_width);
                $('#eheight').val(new_height);
                $('.embed-block textarea#embed_code').val(embed_html);
                break;
            case 'medium':
                new_width = 760;
                new_height = 646;
                if (is_width) {
                    html_1st_part = html_1st_part.replace(width, new_width + 'px');
                    html_2nd_part = html_2nd_part.replace(height, new_height + 'px');
                } else {
                    html_1st_part = html_1st_part.replace(height, new_height + 'px');
                    html_2nd_part = html_2nd_part.replace(width, new_width + 'px');
                }
                embed_html = html_1st_part + html_2nd_part;
                $('#ewidth').val(new_width);
                $('#eheight').val(new_height);
                $('.embed-block textarea#embed_code').val(embed_html);
                break;
            case 'small':
                new_width = 500;
                new_height = 425;
                if (is_width) {
                    html_1st_part = html_1st_part.replace(width, new_width + 'px');
                    html_2nd_part = html_2nd_part.replace(height, new_height + 'px');
                } else {
                    html_1st_part = html_1st_part.replace(height, new_height + 'px');
                    html_2nd_part = html_2nd_part.replace(width, new_width + 'px');
                }
                embed_html = html_1st_part + html_2nd_part;
                $('#ewidth').val(new_width);
                $('#eheight').val(new_height);
                $('.embed-block textarea#embed_code').val(embed_html);
                break;
        }
        $('.embed-block input#preview').removeClass('disabled');
        $('.embed-block textarea#embed_code').removeAttr('disabled');
        $('.embed-block input#preview').removeAttr('disabled');
    });
    $(".custom-size").keyup(function () {
        var element_id = $(this).attr('id');
        var value = $(this).val();
        var numberRegex = /^[+-]?\d+(\.\d+)?([eE][+-]?\d+)?$/;
        if (!numberRegex.test(value)) {
            var str_len = value.length;
            value = value.slice(0, str_len - 1);
            $(this).val(value);
            return;
        }
        value = value + 'px';
        var input_width = $('#ewidth').val();
        var input_height = $('#eheight').val();
        if (input_width < 425 || input_height < 425) {
            $('.econf-block .block .min-text').addClass('max-size-message');
            $('.embed-block textarea#embed_code').attr('disabled', 'disabled');
            $('.embed-block input#preview').attr('disabled', 'disabled');
            $('.embed-block input#preview').addClass('disabled');
        } else {
            $('.econf-block .block .min-text').removeClass('max-size-message');
            $('.embed-block input#preview').removeClass('disabled');
            $('.embed-block textarea#embed_code').removeAttr('disabled');
            $('.embed-block input#preview').removeAttr('disabled');
        }
        var width;
        var height;
        var embed_html = $('.embed-block textarea#embed_code').val();

        var is_width = true;
        var offset_width = embed_html.indexOf('width');
        var offset_height = embed_html.indexOf('height');
        var string_length = embed_html.length;
        var html_1st_part = '';
        var html_2nd_part = '';
        if (offset_width > offset_height) {
            is_width = false;
            html_1st_part = embed_html.substring(0, offset_width);
            html_2nd_part = embed_html.substring(offset_width, string_length);
        } else {
            html_1st_part = embed_html.substring(0, offset_height);
            html_2nd_part = embed_html.substring(offset_height, string_length);
        }
        switch (element_id) {
            case 'ewidth':
                width = $($('.embed-block textarea#embed_code').val()).find('iframe').attr('width');
                if (width.indexOf("px") == -1) {
                    width = width + 'px';
                }
                if (is_width) {
                    html_1st_part = html_1st_part.replace(width, value);
                } else {
                    html_2nd_part = html_2nd_part.replace(width, value);
                }
                embed_html = html_1st_part + html_2nd_part;
                $('.embed-block textarea#embed_code').val(embed_html);
                $(".iframe-dimensions").removeClass("econf-block-selected-color");
                break;
            case 'eheight':
                height = $($('.embed-block textarea#embed_code').val()).find('iframe').attr('height');
                if (height.indexOf("px") == -1) {
                    height = height + 'px';
                }
                if (is_width) {
                    html_2nd_part = html_2nd_part.replace(height, value);
                } else {
                    html_1st_part = html_1st_part.replace(height, value);
                }
                embed_html = html_1st_part + html_2nd_part;
                $('.embed-block textarea#embed_code').val(embed_html);
                $(".iframe-dimensions").removeClass("econf-block-selected-color");
                break;
        }
        if (input_width == 500 && input_height == 425) {
            $('.econf-block #small').addClass('econf-block-selected-color');
        }
        if (input_width == 760 && input_height == 646) {
            $('.econf-block #medium').addClass('econf-block-selected-color');
        }
        if (input_width == 950 && input_height == 808) {
            $('.econf-block #large').addClass('econf-block-selected-color');
        }
    });
    if ($('.embed-code').length > 0) {
        var container_width = $('.embed-code .containers').width();
        var attr_col = (container_width / 10).toFixed(0);
        var field_item_wt = (container_width * (45 / 100)).toFixed(0);
        $(".embed-code .containers textarea").each(function (index) {
            $(this).attr('cols', attr_col);
        });
        $(".embed-code .dataset .field-items").each(function (index) {
            $(this).attr('style', 'width:69%');
        });
        var page_url_woparam = $(location).attr('href');
        page_url_woparam = page_url_woparam.substring(0, page_url_woparam.indexOf('?'));
        var suggest_dataset_url = Drupal.settings.basePath + 'suggest_dataset';
        $(".embed-code .embed-feature-links .embeded-link").each(function (index) {
            if ($(this).hasClass('suggest-dataset-link')) {
                $(this).attr('href', suggest_dataset_url);
            } else {
                $(this).attr('href', page_url_woparam + '#tabs-block');
                if ($(this).hasClass('rating')) {
                    $(this).attr('href', page_url_woparam + '?showrating#tabs-block');
                }
            }
        });
    }
    $(".embed-feature-links .print").click(function () {
        window.print();
    });

    $(".metrics-menu li").each(function () {
        if ($(this).find('ul').size() > 0) {
            $(this).bind('mouseover',
                function () {
                    $("#submit_btn").focus();
                }
            );
        }
    });
    if ($('#rotating-panes').length > 0) {
        $("#rotating-panes a").each(function () {
            var title_text = $.trim($(this).html());
            $(this).attr('title', title_text);
            if (title_text == 'Pause') {
                $(this).attr('title', 'Pause/Play');
            }
        });
    }
    
    
    $('.tabPanel li a').click(function () {
        $('.tabPanel li a').removeClass('active');
        tab_class_name = $(this).attr('class');
        $(this).addClass('active');
        togglesTab(tab_class_name);
    });
    
    $('body.dataset-page #comments').hide();
});
$(document).ready(function () {
    if ($('#web-tellafriend-form').length > 0) {
        mesgCounters(300, 'edit-message', 'message-textarea-limit-count');
        $(".messages.error ul li").each(function () {
            if ($(this).find('ul').size() > 0) {
                var cont = $(this).find('ul li').html();
                $(this).find('ul').remove();
                $(this).append(cont);
            }
        });
    }
    if ($('#node-form').length > 0) {
        mesgCounters(300, 'edit-field-feedback-body-0-value', 'feedback-textarea-limit-count');
        $(".messages.error ul li").each(function () {
            if ($(this).find('ul').size() > 0) {
                var cont = $(this).find('ul li').html();
                $(this).find('ul').remove();
                $(this).append(cont);
            }
        });
    }
    if ($('#web-contact-owner-form').length > 0) {
        mesgCounters(300, 'edit-message', 'shrt-textarea-limit-count');
        $(".messages.error ul li").each(function () {
            if ($(this).find('ul').size() > 0) {
                var cont = $(this).find('ul li').html();
                $(this).find('ul').remove();
                $(this).append(cont);
            }
        });
    }
    if ($('#contact-mail-page').length > 0) {
        mesgCounters(300, 'edit-message', 'feedback-textarea-limit-count');
    }

    $("#rss-feed-aggregator").css('overflow', 'hidden');
    
    /*
    $("#stop").click(function () {
        clearTimeout(slideTimeIn);
        $("#scroll-content").css("marginTop", "0px");
        $("#scroll-content").css("marginTop", "0px");
        $("#scroll-content").hide();

        $("#fs2").show();
        $("#fs2").empty();
        $("#fs2").html($("#scroll-content").html());
    });

    $("#play").click(function () {
        clearTimeout(slideTimeIn);
        _GLOBAL_CNT = 0;
        $("#fs2").hide();
        $("#scroll-content").show();
        startscroller();
    });
    startscroller();
    */
    
});

	
	$(document).ready(function () {
		$("#scroll-content").vTicker({ 
			speed: 2000,
			pause: 6000,
			animation: 'fade',
			mousePause: true,
			height: 0,
			showItems: 1
			
		});
	});
	
$(document).ready(function () {
    $(".switch-js-disabled").hide();
    $(".switch-js-enabled").show();
    $("#views-slideshow-imageflow-images-1_previous").attr("title", "Previous");
    $("#views-slideshow-imageflow-images-1_next").attr("title", "Next");
    $(".apachesolr-showhide").attr("title", "Show more");
    if (navigator.userAgent.indexOf('MSIE') < 0 && navigator.userAgent.indexOf('Opera') < 0) {
        $("#contentPanel .site-map-box ul li ul li").attr('style', 'padding:0px 40px 0 7px!important;');
    }

    if ($(".block-vrm_customization form")) {
        var frmaction = $(".block-vrm_customization form").attr('action');
        $(".block-vrm_customization form").attr('action', frmaction + "?showrating");
    }

    $("span.ext").after("&nbsp;");
});
$(document).ready(function () {
    if ($("#contact-mail-page").length > 0) {
        var cat_id = $('#contact-mail-page #edit-cid-wrapper #edit-cid').attr('id');
        var cat_class = $('#contact-mail-page #edit-cid-wrapper #edit-cid').attr('class');
        var cat_name = $('#contact-mail-page #edit-cid-wrapper #edit-cid').attr('name');
        var cat_html = $('#contact-mail-page #edit-cid-wrapper #edit-cid').html();
        $('#contact-mail-page #edit-cid-wrapper #edit-cid').remove();
        $('#contact-mail-page #edit-cid-wrapper').append('<div id="category-id"><select id=' + cat_id + ' name=' + cat_name + '>' + cat_html + '</select></div>');
        $('#test #edit-cid').addClass(cat_class);
    }
    if ($(".banner-right .quicktabs_tabs").length > 0) {
        $('.banner-right .quicktabs_tabs li a').each(function (index) {
            var a_text = $(this).html();
            $(this).html('<span>' + a_text + '</span>');
        });
    }
    $("#context-block-region-text_resize").hide();
    if(typeof jQuery('#leftPanel') != 'undefined') {
	  var leftPanel = jQuery('#leftPanel').height();
	  if(typeof leftPanel != 'undefined' && jQuery('#contentPanel') != 'undefined') {
		  leftPanel = leftPanel - 18;
		  jQuery('#contentPanel').css("min-height", leftPanel);
	  }
    }
    
    /*
    if(typeof jQuery("#clientsidevalidation-user-register-errors") != 'undefined') {
    	var dis_status = jQuery("#clientsidevalidation-user-register-errors").css('display');
    	if(dis_status == 'none') {
    		jQuery("#block-panels_mini-user_register").show();
    		jQuery("#user-register, #block-panels_mini-signup_panel").hide();
    	} else {
    		jQuery("#block-panels_mini-user_register").hide();
    		jQuery("#user-register, #block-panels_mini-signup_panel").show();
    	}
    }
    */
    
    $('a[href="#register"]').click(function() {
    	$("#block-panels_mini-user_register").hide();
		$("#user-register, #block-panels_mini-signup_panel").show();
    	return false;
    })
    
    if($(".messages.error ul li").length){
    	$("#block-panels_mini-user_register").hide();
		$("#user-register, #block-panels_mini-signup_panel").show();
    }else {
    	$("#block-panels_mini-user_register").show();
		$("#user-register, #block-panels_mini-signup_panel").hide();
	}
});




/* Left Panel li a.active background color has been used  */
$(document).ready(function () {
	$("#leftPanel .item-list li a.active").parent().css('background-color', '#BCC8A0');
    $("#leftPanel .item-list li a").hover(  
      function () { 
    	  $(this).parent().css('background-color', '#BCC8A0'); 
	  },
      function () { 
		  if(!$(this).hasClass('active') )
			  { 
			  	$(this).parent().css('background-color', 'transparent');
			  } 
		  	
	  }
    );
    
    if(jQuery("input#edit-keys").val() == "") {
		jQuery("input#edit-keys").val("Enter your keywords");
    }
    
    jQuery("input#edit-keys").focus(function() {
    	if(jQuery(this).val() == "Enter your keywords"){
    		jQuery(this).val("");
    	}
    });
    
    jQuery("input#edit-keys").blur(function() {
    	if(jQuery(this).val() == "") {
    		jQuery(this).val("Enter your keywords");
    	} 
    });
    
    jQuery("#search-form").submit(function(){
    	if(jQuery("input#edit-keys").val() == "Enter your keywords"){
    		jQuery("input#edit-keys").val("");
    	}
    });
    
    /*
    jQuery("input#edit-keys").keyup(function(){
    	if(jQuery(this).val() == ""){
    		jQuery(".apachesolr_search_message .apachesolr_search_message_text").show();
    	} else {
    		jQuery(".apachesolr_search_message .apachesolr_search_message_text").hide();
    	}
    });
    */
    
  });
/* Left Panel li a.active background color has been used  */

/* Resize and Calculate Maximum Height of a div of Communty page Code Starts */
	$(document).ready(function(){
	    var tallest = 0;    
	    	$('.column-3').each(function() {
	            if(tallest < $(this).height()){
	              tallest = $(this).height()
	            }
	        });
	
	      $('.column-3').each(function() {
	    	  $(this).height(tallest);
	      });
	      $('.column-2').each(function() {
	            if(tallest < $(this).height()){
	              tallest = $(this).height()
	            }
	        });
	
	      $('.column-2').each(function() {
	    	  $(this).height(tallest);
	      });
	})
/* Resize and Calculate Maximum Height of a div of Communty page Code Starts */








var datset_tab_default = 0;
var datset_tab_inc	   = 104;

var default_width = 15;
var active_width  = 17;

var default_content_height = 308;


jQuery(function() {
	reset_tab_reset();
	
	jQuery(".dataset-page .basic-info").css('z-index','1');
	jQuery(".dataset-page .basic-info").find('.view-dataset').show();
	jQuery(".dataset-page .basic-info h2").css("width", active_width);
	
	var content_height = jQuery(".dataset-page .basic-info").height();
	
	if( content_height < default_content_height ) {
		content_height = default_content_height;
		jQuery(".dataset-page .basic-info").css('height',content_height);
	}
	
	jQuery(".dataset").css('height', content_height + 10);
	
	jQuery(".dataset-page .pane-dataset h2 ").each(function(i) {
		jQuery(this).css('margin-top', datset_tab_default + ( datset_tab_inc  * i) );
	});
	
	jQuery(".dataset-page .pane-dataset h2 ").click(function() {
		reset_tab_reset();
		jQuery(this).parent().find('.view-dataset').show();
		jQuery(this).parent().css('z-index','1');
		jQuery(this).css("width", active_width);
		content_height = jQuery(this).parent().height();
		
		if( content_height < default_content_height ) {
			content_height = default_content_height;
			jQuery(this).parent().css('height',content_height);
		}
		
		jQuery(".dataset").css('height', content_height + 10);
	});
	jQuery(".trouble").hide();
	jQuery('li.trouble-login').click(function() {
		jQuery('.contribute-link').hide();
		jQuery('.error').hide();
		jQuery('.trouble').fadeIn();
	});
});

 function reset_tab_reset() {
	 jQuery(".dataset-page .pane-dataset .view-dataset").hide();
	 jQuery(".dataset-page .pane-dataset").css('z-index', '0');
	 jQuery(".dataset-page .pane-dataset h2").css("width", default_width);
 }
 
 /*
  *  Cookies Set Get Delete Definations
  */
 	var today = new Date();
 	var expiry = new Date(today.getTime() + 365 * 24 * 60 * 60 * 1000);

 	function _getCookieVal (offset) {
	   var endstr = document.cookie.indexOf (";", offset);
	   if (endstr == -1) { endstr = document.cookie.length; }
	   return unescape(document.cookie.substring(offset, endstr));
 	}
 	
 	function _getCookie (name) {
	  var arg = name + "=";
	  var alen = arg.length;
	  var clen = document.cookie.length;
	  var i = 0;
	  while (i < clen) {
	    var j = i + alen;
	    if (document.cookie.substring(i, j) == arg) {
	      return _getCookieVal (j);
	      }
	    i = document.cookie.indexOf(" ", i) + 1;
	    if (i == 0) break; 
	    }
	  return null;
 	}

	function deleteCookie (name,path,domain) {
	  if (_getCookie(name)) {
	    document.cookie = name + "=" +
	    ((path) ? "; path=" + path : "") +
	    ((domain) ? "; domain=" + domain : "") +
	    "; expires=Thu, 01-Jan-70 00:00:01 GMT";
	  }
	}

	function _setCookie (name,value,expires,path,domain,secure) {
	  document.cookie = name + "=" + escape (value) +
	    ((expires) ? "; expires=" + expires.toGMTString() : "") +
	    ((path) ? "; path=" + path : "") +
	    ((domain) ? "; domain=" + domain : "") +
	    ((secure) ? "; secure" : "");
	}
	
 /*
  *  Cookies Set Get Delete Definations end
  */
	 
