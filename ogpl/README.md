# OGPL-Beta Installation Guide #



## Drupal Installation ##

----------

For information on Drupal installation, see the INSTALL.txt file in the OGPL/WebApp directory.

- Download OGPL-Beta product from Github
- Move the contents of "core" directory from ogpl/webapp to your web  server's document root or your public HTML directory (e.g. In Linux /var/www/html).
- Move the "sites" directory from ogpl/webapp to your document root.
- Ensure that the following php.ini configurations are set/verified before starting the installation
	- memory_limit = 512M
	- max_execution_time = 120
- In my.cnf file ensure max_allowed_packet_size is 16M
- Create your mysql user and database with desired credentials.
- You can follow either of the bellow step to install OGPL

	- 	If you want to install OGPL using the built-in OGPL profile, move the ogpl folder from ogpl/webapp/profiles to /profiles and run http://your-host/install.php
	
	- If you want to install OGPL manually (for Advanced Users), import the ogpl.sql file from ogpl/db to newly created database. Change the required database connection settings in /sites/default/settings.php in the following line
>	`$db_url = 'mysql://database_username:database_password@localhost/database_name';`



## Post Installation and Configuration ##

----------

**Perform the following configurations after the installation:**

- To access help document please move the "helps" and "WebHelp" folder from ogpl/webapps to your server document root
- For Text resize, in the advance setting of the Text resize module (admin/settings/textsize), update the XHTML element ID/class your theme have.
- Check the Apache SOLR setting (admin/settings/apachesolr/settings) and update the following server settings. 
	- Solr host name (Host name of your Solr server, e.g. localhost or example.com.)
	- Solr port (Port on which the Solr server listens. The Jetty example server is 8983, while Tomcat is 8080 by default.)
	- Solr path (Path that identifies the Solr request handler to be used.)
	
- Check the file system settings (admin/settings/file-system) and provide full permission on specified directory. After changing the default file system path, execute the following query in the database:

	> `UPDATE files SET filepath = replace(filepath, "sites/default/files", "[new file system path]") WHERE 1;`
	
	**Note: For security reason you can keep the file system outside document root. In case your file system is outside the document root the Download method should set to Private.**

- In the Drupal menu, go to Site Configuration and click Site Information. (admin/settings/site-information) Site Information page appears.

	**You can update the following essential settings for site configuration**
	- Powered By Image Settings (Appears at footer of the site)
	- Hosted Agency Image Settings (Appears at footer of the site)
	- Select the Country (Select your country, Depending on selected country the country flag and other details will appear at the site header)
	- Available languages for the country (Provide the comma separated values of languages for the country which will be added to language list)
	- Super Admin access IPs (Enter the IP Address from which Super admin will be allowed to login. Please separate each IP Address by a new line.)
	- Admin URL (Provide the URL which will be used for Data Portal Management System - backend)
	- Email Domain ( Provide the allowed email domain. required if using LDAP)
	- CMS Roles (Select the roles which will be used for login to the Data Portal Management system)
	- Front-End URL (URL to be used for Data Portal frontend)
	- Frontend Roles (Roles to be allowed to login at frontend)
	- Google Map API Key (API key for google MAP implementation)  
- Now you can enabe Captcha and Captcha After module from admin/build/modules/list

## Working with Secure Login Forms (Encrypt Submission and 443 Sessions) ##

----------
If you want to encrypt your login and registration forms please enable "Encrypt Submission" from admin/build/modules/list

> **Important Note: To make encrypt submission work ensure that the php-bcmath module is installed. You can use “php -qa | grep \*bcmath” to verify and “yum install php\*-bcmath” to install it.**

If you want the user to redirect to "https" at the time of user login or registration you can enable 443 Session module from admin/build/modules/list


## Setting Required Taxonomy ##

----------

Vocabulary plays very important role in DMS. Required Vocabularies can be edited at admin/content/taxonomy/list. You can change the values of the following taxonomies as per your country need.

- Ministry/Department
- Sector
- Target Audience
- Language
- File Format
- Asset Jurisdiction

## Community ##

----------

Community is an optional part of OGPL. You can disable community by disabling the following 2 modules

- ogpl_community
- Community Customization

## Data Conversion API ##

----------

If you want to use data conversion tool then copy the datatool folder from ogpl/webapps to your document root.

For available options and parameters of the API please go through the readme.md file under datatool

## Creating Required users for Data Contribution ##

----------

If you do not want to use LDAP for user authentication then admin needs to create Drupal users from backend. Follow the following steps to create users.

1.	Go to : Management  => User Management (content/add-user) 
2.	Choose Roles as External User
3.	Provide Email address and default Password for the user
4.	Choose “Notify user of new account” to Send mail to the newly created user.
5.	Then Newly Created user can login and Apply for desired role by filling the role request form.
6.	Once the role request is done admin can approve the user from “Approve Role” Tab 

## Credentials ##

----------

**SUPER ADMIN**

	**************************************
	User Name: admin
	Password: Super123@
	**************************************

**VRM**

	**************************************
	User Name: vrm@data.gov.in
	Password: Vrm123@
	**************************************
**DMS**

	**************************************
	User Name: pmu@data.gov.in
	Password: Pmu123@
	**************************************
	User Name: poc-education@data.gov.in
	Password: Poceducation123@
	**************************************
	User Name: ds-education@data.gov.in
	Password: Dseducation123@
	**************************************
**CMS**

	**************************************
	User Name: cmsadmin@data.gov.in
	Password: Cmsadmin123@
	**************************************
	User Name: content-creator@data.gov.in
	Password: Contentcreator123@
	**************************************





