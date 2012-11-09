
***********
443 SESSION
***********

About
*****

The 443 Session module makes using HTTPS on your site simple. It is most useful
for doing mixed HTTPS where some pages are sent via HTTP, and others via HTTPS.
It can be used to protect credit card transactions or to protect against session
hijacking (via tools such as Firesheep).



Important Disclaimer
********************

If 443 Session module is making your site inaccessible (because your server is
not setup for HTTPS, or is incorrectly setup), you can disable redirects by
entering the following at the bottom of your settings.php file:
    $conf['session443_enable'] = FALSE;
Or you can disable the module using drush:
    drush disable session443



Installation
************

1. Make sure that HTTPS is working on your site before installing this module.
You can lock yourself out of your site if you don't know what you are doing.
If you do lock yourself out, see the notes above.

2. Download, unpack, and enable the module as per usual.

3. Enable 443 Session at
    admin/settings/session443
   Most sites will not need to alter any other settings.

4. If you choose redirection rules that force authenticated users to use HTTPS
then you must include the following in settings.php.  
  if (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] != 'off') {
    ini_set('session.cookie_secure', 1);
  }
If you choose rules that *DON'T* force authenticated users to use HTTPS then
you must *NOT* include the above in settings.php.



Advanced
********

* If you want to create your own complex rules about when redirects should
happen, call the session443_set_page_should_be_secure() function.  See the
docbook comments for details.

* 443 Session module is compatible with HTTP accelerators and reverse-proxies 
such as Varnish or nginx. However HTTP requests with the LOGGED_IN cookie
should be allowed to pass through to Drupal. Otherwise when authenticated
users visit HTTP pages they will be logged out.

* 443 Session module is mostly compatible with Drupal's aggressive page cache.
However when authenticated users visit HTTP pages they will be logged out.

* 443 Session module should work with HTTPS accelerators.  You will have to 
modify the addition to settings.php and you may need to set the 
session443_ssl_headers variable.
