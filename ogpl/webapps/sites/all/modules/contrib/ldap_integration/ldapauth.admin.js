
/**
 * Behaviours are bound to the Drupal namespace.
 */
Drupal.behaviors.ldapauth = function(context) {
  if(window.location.href.search(/add$/) > 0) {
    $('#edit-test').hide();
  }
  $('#edit-test').click(function(event) {
    $('#test-message').hide();
    $('#test-spinner').show();
    var url = window.location.href + '/test';
    $.post(url, { binddn: $('#edit-binddn').val(), bindpw: bindpw = $('#edit-bindpw').val(), bindpw_clear: bindpw_clear = $('#edit-bindpw-clear').val() },
      function(data){
        $('#test-spinner').hide();
        $('#test-message').show().removeClass('status error').addClass(data.status ? 'status' : 'error').html(data.message);
      }, "json");
    return false;
  });
  // Server edit/create form machine_name JS
  $('.ldapauth-name:not(.processed)').each(function() {
    $('.ldapauth-name')
      .addClass('processed')
      .after(' <small class="ldapauth-machine-name-suffix">&nbsp;</small>');
    if ($('.ldapauth-machine-name').val() === $('.ldapauth-name').val().toLowerCase().replace(/[^a-z0-9]+/g, '_').replace(/_+/g, '_') || $('.ldapauth-machine-name').val() === '') {
      $('.ldapauth-machine-name').parents('.form-item').hide();
      $('.ldapauth-name').bind('keyup change', function() {
        var machine = $(this).val().toLowerCase().replace(/[^a-z0-9]+/g, '_').replace(/_+/g, '_');
        if (machine !== '_' && machine !== '') {
          $('.ldapauth-machine-name').val(machine);
          $('.ldapauth-machine-name-suffix').empty().append(' Machine name: ' + machine + ' [').append($('<a href="#">'+ Drupal.t('Edit') +'</a>').click(function() {
            $('.ldapauth-machine-name').parents('.form-item').show();
            $('.ldapauth-machine-name-suffix').hide();
            $('.ldapauth-name').unbind('keyup');
            return false;
          })).append(']');
        }
        else {
          $('.ldapauth-machine-name').val(machine);
          $('.ldapauth-machine-name-suffix').text('');
        }
      });
      $('.ldapauth-name').keyup();
    }
  });
  
};

