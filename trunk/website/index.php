<?php
	$g_pageTitle = "SlimDX Homepage";
	$g_pageName = "Home";
	
	require_once("header.php");
?>

<div id="content">
	<div class="wrapper">    
    	<div class="paragraph">
			<h1>What is SlimDX?</h1>
			<p>SlimDX is a free open source framework that enables developers to easily build DirectX applications using .NET technologies such as C#, VB.NET, and !IronPython. 
      It is designed to be an efficient, simple, and lean wrapper that fully encompasses all of Microsoft's gaming and multimedia technologies and exposes them to managed code.
      All of the code is under the MIT/X11 license, and all content is under the Creative Commons Attribution-Share Alike license.
      Our latest release is August 2009, and can be found for users and developers on the <a href="download.php">Download page</a>.
			<br /><br />
      Originally, the managed game development niche was filled by Microsoft's Managed DirectX, which is now deprecated and no longer recommended for new development. In it's wake, SlimDX has stepped up to provide support in a 
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
			Lastly, be sure to check us out on <a href="http://twitter.com/SlimDX">Twitter</a>!
			<br /><br />
			Last but not least, the <b>SlimDX team is now accepting donations</b>, and offering support contracts as well.
			Developing SlimDX takes a lot of time and work, alongside our normal lives.
			By donating or purchasing contracts, you will ensure that the project continues to thrive and serve all its users as much as possible.
			For more information, please visit the <a href="support.php">Support page</a>.
			Thank you!
			</p><br />

			<a href="download.php"><img src="images/latest.jpg" alt="latest release" /></a>
        </div>
        
        <div id="left_column">
			<h2>Why not use XNA Game Studio?</h2>
			<p>
			XNA Game Studio (XNA GS) is Microsoft's new initiative for game development in .NET, targeting Windows and the Xbox 360.
			It is mostly source compatible between both Windows and Xbox 360 platforms.
			Note that "XNA" is used as shorthand for the XNA Framework.
			Although XNA and SlimDX share several goals and expose some common components, the overall intent of the two libraries is very different.
			While XNA's main focus is to provide a comprehensive solution for producing managed games, SlimDX seeks to faithfully expose as much of the Windows multimedia architecture as possible for all kinds of applications.
			As a result, the actual features and interfaces in each are quite different.
			</p>
			<a href="features.php" class="homea">Read More...</a>
        </div>
        
        <div id="mid_column">
			<h2>Getting Started</h2>
			<p>
			Getting started is easy!
			In order to work with SlimDX, you need to have a development environment that allows you to write and run code in a .NET language.
			We recommend Visual C# Express, but any similar tool should work just fine.
			It's also recommended that you download the latest DirectX SDK from the Microsoft DirectX Developer Center.
			This SDK contains a lot of Microsoft's documentation, as well as sample projects in C++ (which are easily translated to SlimDX code) showcasing many useful tricks and techniques.
			However, this is a very large package, typically over 450 MB, and not required to build SlimDX applications.
			If you prefer, you can simply use online documentation, tutorials, and samples. 
			</p>
			<a href="http://slimdx.org/latestdocs/Default.aspx?topic=Programming+Guide/Getting+Started" class="homea">Read More...</a>
        </div>
        
        <div id="right_column">
			<h2>Current Status</h2>
			<p>
			SlimDX was first publically revealed in beta form on June 30, 2007.
			Since then, it has grown at a rapid pace and now covers just about every corner of multimedia provided by Microsoft.
			As of the June 2008 release, it is no longer in beta and is considered stable.
			Several commercial projects and companies are using SlimDX, including at least one shipped AAA game title for Windows.
			With support for many libraries, including DirectX 9, DirectX 10, DirectX 11, DirectSound, XAudio2, and XInput, SlimDX is the most complete multimedia library for .NET you will find anywhere.
			</p>
			<a href="features.php" class="homea">Read More...</a>
			</div>
			<div id="clear"></div>
    </div>
</div>

<?php	
	require_once("footer.php");
?>

