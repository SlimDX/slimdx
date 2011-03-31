<?php
	$g_pageTitle = "SlimDX Documentation";
	$g_pageName = "Documentation";
	
	require_once("../header.php");
?>

<script type="text/javascript" src="lib/jquery.js"></script>
<script type="text/javascript" src="jquery.jstree.js"></script>

<script type="text/javascript">
function getCurrentLocation()
{
	//get the current doc in the iframe
	var frame = document.getElementById("content_frame").contentWindow;
	return frame.location;
}

function navigateToUrl(url)
{
	var target = "#" + url;
	window.location.hash = target;
}

function locationHashChanged() {
	var topic = window.location.hash.substring(1);
	var target = "html/" + topic;
	var current = getCurrentLocation();
	if(current != target)
		$("#content_frame").attr('src', target);
}

function navigateFrame(url)
{
	if(url.charAt(0) == "#")
		url = url.substring(1);

	var target = "html/" + url;
	document.getElementById("content_frame").src = target;
}

function iframeLoaded() {
	var loc = getCurrentLocation(); 
	//ignore the initial blank load
	if(loc.host != document.location.host)
		return;
	//ignore the front page load (hash is "" or "#")
	if(window.location.hash.length < 2)
		return;

	//strip off the html/ and path name from the location, then add the hash
	var target = "#" + loc.pathname.substring(window.location.pathname.length + 5);
	//if this is true, a link inside the iframe was clicked and the hash is updated to match
	if(target != window.location.hash)
		window.location.hash = target;
}

</script>

<div id="page_container">
	<div id="sidebar">
		<div id="tree"></div>
	</div>

	<div id="content_container">
		<div id="frame_container">
			<iframe id="content_frame" frameborder="0" onload="iframeLoaded();"></iframe>
		</div>
	</div>
</div>

<script type="text/javascript">
$(function () {
	//debugger;
	
	//if a target was provided as part of the link, navigate to it
	if(window.location.hash.length > 1)
		navigateFrame(window.location.hash);	
	//hook up hash change detection
	window.onhashchange = locationHashChanged;
	
	$("#tree").jstree({
		"core" : { "animation": 250 },
		"plugins" : [ "themes", "json_data", "ui" ],
		"themes" : { "theme" : "classic", "icons" : false },
		"ui" : {
			"select_limit": 1,
			"selected_parent_close" : "select_parent",
			"initially_select": [ "node_0" ]
		},
		"json_data" : {
				"ajax" : {
				"url" : "topic.php",
				"data" : function (n) {
					var queryString = {};
					if(n.attr)
						queryString.id = n.attr("nodeId");

					return queryString;
				},
				"success" : function (data) {
					//patch the data up to match what jsTree expects
					for(i = 0; i < data.length; ++i)
					{
						data[i].data = data[i].Title;
						data[i].attr = {
							"id": "node_" + data[i].Id, 
							"nodeId" : data[i].Id,
							//strip off the "html/" in front
							"topic": data[i].Url.substring(5)
						};
						if(data[i].TopicId != null)
							data[i].state = "closed";
					}

					//if nothing is in the iframe, use this to fill it
					var loc = getCurrentLocation(); 
					if(loc.host != document.location.host && window.location.hash.length < 2)
						navigateFrame(data[0].attr.topic);					

					return data;
				}
			}
		}
	})
	.bind("click.jstree", function(e) {
		if(e.target.nodeName.toLowerCase() != "a")
			return;

		var node = e.target.parentNode;
		var topic = $(node).attr("topic");
		if(topic != null)
		{
			navigateToUrl(topic);
			$("#tree").jstree("open_node", node);
		}
	});
});
</script>

</body>
</html>
