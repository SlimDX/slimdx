<!--
Copyright (c) 2007-2011 SlimDX Group
 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
-->

<?php
	$g_pageTitle = "SlimDX Documentation";
	$g_pageName = "Documentation";
	
	require_once("../header.php");
?>

<script type="text/javascript" src="lib/jquery.js"></script>
<script type="text/javascript" src="jquery.jstree.js"></script>

<script type="text/javascript">
//Returns the location currently displayed by the iframe
function getCurrentLocation()
{
	//get the current doc in the iframe -- src attribute is >>> WRONG <<<
	var frame = document.getElementById("content_frame").contentWindow;
	return frame.location;
}

//Get the current topic, by stripping down the location string to just the topic portion
function getCurrentTopic()
{
	var loc = getCurrentLocation();
	var topic = loc.pathname.substring(window.location.pathname.length + 5);
	topic = topic.substring(0, topic.lastIndexOf("."));
	return topic;
}

//Change the window location hash, triggering the hash changed event
function navigateToUrl(url)
{
	var target = "#" + url;
	window.location.hash = target;
}

//Navigate the frame directly, without touching other state (triggers iframeLoaded)
function navigateFrame(url)
{
	if(url.charAt(0) == "#")
		url = url.substring(1);

	var target = "html/" + url + ".htm";
	document.getElementById("content_frame").src = target;
}

//Respond to a change in the hash by navigating if needed, can be done by user or code
function locationHashChanged() {
	var topic = window.location.hash.substring(1);
	var current = getCurrentTopic();
	if(current != topic)
		navigateFrame(topic);
}

//scroll the tree to a target node (after a search for that node triggered by iframe navigate)
function scrollTree() {
	//check if there's a scroll point set
	var scrollto = $("#sidebar").attr("scrollto");
	if(scrollto == null || scrollto.length == 0)
		return;
	
	//find the ndoe if it exists
	var node = document.getElementById("node_" + scrollto);
	if(node == null)
		return;

	//select and open the node, since its children are now relevant
	$("#tree").jstree("open_node", node);
	$("#tree").jstree("select_node", node, true);
	
	//okay we have a target, scroll to it
	var offset = node.offsetTop;
	if(offset == 0)
	{
		//node has not been positioned, try and use its parents instead
		path = $("#tree").jstree("get_path", node, true);
		path.pop();
		while(path.length > 0 && offset == 0)
		{
			var parentId = path.pop();
			offset = document.getElementById(parentId).offsetTop;
		}
	}

	document.getElementById("sidebar").scrollTop = offset;
	//clear the scroll point ttribute
	$("#sidebar").attr("scrollto", "");
}

//Respond to the iframe being loaded -- if new page, change location hash and search tree
function iframeLoaded() {
	var loc = getCurrentLocation(); 
	//ignore the initial blank load
	if(loc.host != document.location.host)
		return;
	//ignore the front page load (hash is "" or "#")
	if(window.location.hash.length < 2)
		return;

	//strip off the html/ and path name from the location, then add the hash
	var target = "#" + getCurrentTopic();
	//if this is true, a link inside the iframe was clicked and the hash is updated to match
	if(target != window.location.hash)
	{
		window.location.hash = target;
		$("#tree").jstree("search", target);
	}
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
		"core" : { "animation": 100 },
		"plugins" : [ "themes", "json_data", "ui", "search" ],
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
							"topic": data[i].Url
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
		},
		"search" : {
			"ajax" : {
				"url": "search.php",
				"data": function(n) {
					var queryString = {};
					queryString.url = getCurrentTopic();
					return queryString;
				},
				"success": function(data) {
					if(data.length == 0)
						return null;

					//build an id list from the path sent back
					var path = data[0].ParentPath;
					var nodes = path.split("/");
					nodes.shift();
					for(i = 0; i < nodes.length; ++i)
					{
						nodes[i] = "#node_" + nodes[i];
					}

					//mark the node as the scroll target
					$("#sidebar").attr("scrollto", data[0].Id);
					//attempt to scroll right now, in case we already have the node loaded
					scrollTree();

					return nodes;
				}
			}
		}
	})
	.bind("load_node.jstree", function(e, data) {
		if(data[0] == -1)
			return;

		//if this load was triggered by a search, we'll want to scroll
		scrollTree();
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

<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
try {
var pageTracker = _gat._getTracker("UA-2872756-3");
pageTracker._trackPageview();
} catch(err) {}</script>

</body>
</html>

