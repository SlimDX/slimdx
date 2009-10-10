<?php
	$g_pageTitle = "SlimDX Features";
	$g_pageName = "Features";
	
	require_once("header.php");
?>

<div id="content">
	<div class="wrapper">
		<div class="paragraph">
			<h2>Supported Systems</h2>
			<p>
			SlimDX supports a wide range of APIs, operating systems, and configurations.
			All versions of Windows XP, Vista, Server 2003, Server 2008, and 7 are supported, for both 32 and 64 bit.
			There is a minimum requirement of .NET 2.0, but any subsequent version (including or excluding service packs) will work.
			</p>
		</div>
		
		<div class="paragraph">
			<h2>Supported APIs</h2>
			<p>	
			SlimDX has full support for the following APIs in the March 2009 release:
			<ul style="margin-left: 2em;">
				<li>Math Library</li>
				<li>Direct3D9</li>
				<li>Direct3D9Ex</li>
				<li>Direct3D10</li>
				<li>DirectInput</li>
				<li>DirectSound</li>
				<li>DXGI</li>
				<li>Windows Multimedia</li>
				<li>Raw Input</li>
				<li>X3DAudio</li>
				<li>XAPO</li>
				<li>XAudio2</li>
				<li>XInput</li>
			</ul></p>
			
			<p>The following APIs have beta support, in a separate assembly:
			<ul style="margin-left: 2em;">
				<li>Direct3D 11</li>
				<li>Direct2D</li>
				<li>DirectWrite</li>
			</ul></p>
			
			<p>The following APIs have full support in the current code but have not been released:
			<ul style="margin-left: 2em;">
				<li>Direct3D 10.1</li>
			</ul></p>
		</div>
		
		<div class="paragraph">
			<h2>Notable Features</h2>
			<p><h3>Interoperability</h3>
				SlimDX has full support for sharing DirectX objects with other libraries.
				All SlimDX objects expose their native pointers for use by other code, and SlimDX can wrap native pointers with its own objects.
				This allows seamless cooperation with libraries such as DirectShow.NET, CUDA.NET, native code DirectX libraries, and more.
			</p><br />
			<p><h3>64-bit Systems and "Any CPU"</h3>
				SlimDX includes x64 bit assemblies, and is the <i>only</i> DirectX interface for .NET to do so.
				The redistributable and SDK installers automatically register the correct assemblies.
				Applications can also compile for the "Any CPU" architecture when using SlimDX, and the correct version will be selected.
				As a result, SlimDX based applications can smoothly target both x86-32 and x86-64 bit machines without the headaches introduced by other similar libraries.
				(Itanium IA64 is not a supported configuration, sorry.)
			</p>
		</div>
    </div>
</div>

<?php	
	require_once("footer.php");
?>

