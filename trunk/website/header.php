<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" 
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link rel="stylesheet" href="css/reset.css" type="text/css" />
	<link rel="stylesheet" href="css/default.css" type="text/css" />

<?php
	if(empty($g_pageTitle))
		$g_pageTitle = "SlimDX";
		
	echo "<title>$g_pageTitle</title>"
?>

</head>
<body>

<div id="top1">
	<div class="wrapper">
    	<div id="logo">
        <img src="images/logoblackbg.jpg" alt="SlimDX" />
        </div>
        
        <ul class="menu">
<?php
	function WriteListItem($itemName, $url)
	{
		global $g_pageName;
		
		if($g_pageName == $itemName)
			echo '<li class="current">';
		else
			echo '<li>';
			
		echo "<a href=\"$url\">$itemName</a></li>\n";
	}
	
	WriteListItem("Home", "index.php");
	WriteListItem("Features", "features.php");
	WriteListItem("Download", "download.php");
	WriteListItem("Licensing", "license.php");
	WriteListItem("News", "news.php");
	WriteListItem("Support", "support.php");
?>            
        </ul>
    </div>
</div>