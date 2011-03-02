<?php
	$g_pageTitle = "SlimDX Homepage";
	$g_pageName = "Home";
	
	require_once("header.php");
?>

<div id="content">
	<div class="wrapper">    
    	<div class="paragraph">
			<h1>What is SlimDX?</h1>
			<p>SlimDX is a free open source framework that enables developers to easily build DirectX applications using .NET technologies such as C#, VB.NET, and IronPython. 
      It is designed to be an efficient, simple, and lean wrapper that fully encompasses all of Microsoft's gaming and multimedia technologies and exposes them to managed code.
      All of the code is under the MIT/X11 license, and all content is under the Creative Commons Attribution-Share Alike license.
      Our latest release is June 2010, and can be found for users and developers on the <a href="download.php">Download page</a>.
			<br /><br />
      Originally, the managed game development niche was filled by Microsoft's Managed DirectX, which is now deprecated and no longer recommended for new development. In its wake, SlimDX has stepped up to provide support in a 
      way that is very similar to the original MDX libraries. While similar, however, they are not intended to be the same APIs. SlimDX exposes a broader range of technologies, has a core design that improves upon that provided 
      by MDX, and is more in-tune with managed methodologies since the advent of .NET 2.0. SlimDX is already widely used and can be found in several major multimedia and gaming applications.
      <br /><br />  
      All development is based in our <a href="http://code.google.com/p/slimdx/">Google Code homepage</a>.
			You can use that site to report bugs (using our issues page), as well as download a complete copy of the source code.
			If you have questions to ask, or otherwise wish to discuss SlimDX, we ask that you use the <a href="http://www.gamedev.net/community/forums/forum.asp?forum_id=10">DirectX forum</a> on GameDev.Net.
			This is the only forum on which the developers are active; we do not use any other forums or mailing lists.
			Please prefix your thread subject with [SlimDX] if the question is reasonably specific to SlimDX.
			If it isn't, feel free to include or exclude the prefix as you like.
			You can also try and get a hold of us on IRC, in the #graphicsdev channel on <a href="http://www.afternet.org/">AfterNET</a>.			
			<br /><br />
			<h2>Consulting Highlight</h2>
			SlimDX Consulting is now up and running to serve your custom software needs.
			Our expertise in DirectX, SlimDX, and managed/unmanaged interop of all kinds means getting things done in a fraction of the time and cost.
			That leaves you to focus on your application, instead of fighting with unfamiliar libraries.
			<br />Our current Featured Customer is <a href="http://www.starcounter.com/">Starcounter AB</a>;
			see <a href="support.php">the Support page</a> for more information about our services.
			</p><br /><br />

			<p><a href="download.php"><img src="images/install.png" alt="latest release" /></a></p>
      </div>
        
      <div id="left_column">
			<h2>Why use SlimDX?</h2>
			<p>
        SlimDX is a highly polished, fully featured wrapper around almost all Microsoft multimedia and gaming APIs. There are however several
        other choices for managed game development. Follow the link below to our features page to get a list of notable SlimDX
        features, as well as comparison charts comparing the main players in the managed game development scene, both past and present:
        SlimDX, XNA, MDX, OpenTK, and the Windows API Code Pack.
			</p>
			<a href="features.php" class="homea">Read More...</a>
        </div>
        
        <div id="mid_column">
			<h2>Getting Started</h2>
			<p>
			Getting started is easy! Check out our <a href="tutorials.php">tutorials</a> page for an introduction
      to SlimDX and Direct3D 11, or follow the link below to read our documentation article on getting started
      with SlimDX development. While SlimDX doesn't have many samples and or in-depth documentation, concepts
      related by XNA, MDX, and DirectX tutorials on the web should translate easily to SlimDX. We recommend
      the DirectX SDK documentation as a particularly good source of explanatory material.
			</p>
			<a href="http://slimdx.org/latestdocs/Default.aspx?topic=Programming+Guide/Getting+Started" class="homea">Read More...</a>
        </div>
        
        <div id="right_column">
			<h2>Current Status</h2>
			<p>
        SlimDX is currently rock solid, covers just about every multimedia API provided by Microsoft, and is stable enough to be used
        by commercial projects and companies, including several AAA game studios. Several companies and products using SlimDX:<br/>
        <ul style="margin-left: 1em">
          <li>
            <a href="http://seizecontrol.marvel.com/">Spiderman: Web of Shadows</a>
          </li>
          <li>
            <a href="http://www.zipperint.com/">Zipper Interactive</a>
          </li>
          <li>
            <a href="http://www.lizardtech.com/">LizardTech</a>
          </li>
          <li>
            <a href="http://www.lucasarts.com/games/theforceunleashed/">Star Wars: The Force Unleashed</a>
          </li>
        </ul>
      </p>
			</div>
			<div id="clear"></div>
    </div>
</div>

<?php	
	require_once("footer.php");
?>

