/* nibir.me - Nibir Bora
 *
 * Copyright (C) Nibir Bora
 * Author: Nibir Bora <nbora@usc.edu>
 * URL: <http://nibir.me/>
 * For license information, see LICENSE
 */


var BASE_URL = '//127.0.0.1:8020/nibir.me/';
 
$(document).ready(function() {
	$('#a-home').attr('href', BASE_URL);
	
	$('#a-project-all').attr('href', BASE_URL+"projects/");
	$('#a-project-gambit').attr('href', BASE_URL+"projects/gambit/");
	$('#a-project-dirbi').attr('href', BASE_URL+"projects/dirbi/");
	$('#a-project-etola').attr('href', BASE_URL+"projects/etola/");
	$('#a-project-mejaj').attr('href', BASE_URL+"projects/mejaj/");
	$('#a-project-ssms').attr('href', BASE_URL+"projects/ssms/");
	$('#a-project-others').attr('href', BASE_URL+"projects/others.html");
	
	$('#a-writing').attr('href', BASE_URL+"writing/");
	$('#a-calendar').attr('href', BASE_URL+"calendar/");
	$('#a-about').attr('href', BASE_URL+"about/");
	
	$('#a-cpl').attr('href', BASE_URL+"_cpl/");
	$('#a-cpl').removeAttr("href")
	
	$('#a-resume').attr('href', BASE_URL+"~files/Nibir_Bora_(resume).pdf");
	
	// Breadcrumb
	$('#b-home').attr('href', BASE_URL);
	
	$('#b-projects').attr('href', BASE_URL+"projects/");
	
});
