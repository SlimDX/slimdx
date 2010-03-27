from sbuild import *

def execute( build, state, **kwargs ):
	if kwargs.has_key("include_dirs"):
		include_paths = kwargs["include_dirs"]
	else:
		include_paths = []
	
	if kwargs.has_key("library_dirs"):
		library_paths = kwargs["library_dirs"]
	else:
		library_paths = []
		
	if kwargs.has_key("libraries"):
		libraries = kwargs["libraries"]
	else:
		libraries = []
	
	if kwargs.has_key("assemblies"):
		assemblies = kwargs["assemblies"]
	else:
		assemblies = []
		
	if kwargs["arch"] == "x64":
		compiler = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/amd64/cl.exe"
		linker = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/amd64/link.exe"
		mt = "C:/Program Files/Microsoft SDKs/Windows/v6.0A/Bin/x64/mt.exe"
	else:
		compiler = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/cl.exe"
		linker = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/link.exe"
		mt = "C:/Program Files/Microsoft SDKs/Windows/v6.0A/Bin/mt.exe"
	
	object_files = []
	for source_file in kwargs["source"]:
		object_file = FileReference( os.path.join( state.work_path, source_file.name + ".obj" ) )
		object_files.append( object_file )
		
		if state.isFileDirty( source_file.identity ):
			compileCommand = [ compiler ]
			compileCommand.append( "/nologo" )
		
			compileCommand.append( "/clr" )
			compileCommand.append( "/c" )
			
			compileCommand.append( "/EHa" )
			compileCommand.append( "/W3" )
			compileCommand.append( "/Zi" )
			compileCommand.append( "/Od" )
			compileCommand.append( "/MDd" )
			
			for path in include_paths:
				compileCommand.append( "/I{0}".format( path ) )
			
			for path in assemblies:
				compileCommand.append( "/FU{0}".format( path ) )
				
			compileCommand.append( "/Fo{0}".format( object_file.identity ) )
			compileCommand.append( source_file.identity )
			build.schedule( ScheduleItem( compileCommand ) )
	
	linkCommand = [ linker ]
	linkCommand.append("/NOLOGO")
	linkCommand.append("/DLL")
	linkCommand.append("/INCREMENTAL:NO")
	linkCommand.append("/DEBUG")
	linkCommand.append("/MANIFESTFILE:%s.dll.intermediate.manifest" % kwargs["output"] )
	linkCommand.append("/MANIFESTUAC:level='asInvoker' uiAccess='false'")
	linkCommand.append("/MACHINE:%s" % kwargs["arch"]);
	
	for path in library_paths:
		linkCommand.append( "/LIBPATH:{0}".format( path ) )
	
	linkCommand.append( "/OUT:{0}.dll".format( kwargs["output"] ) )
	for object_file in object_files:
		linkCommand.append( object_file.identity )
	for library in libraries:
		linkCommand.append( library )
		
	build.schedule( ScheduleItem( linkCommand ) )
	
	manifestCommand = [ mt ]
	manifestCommand.append("-nologo")
	manifestCommand.append("-outputresource:%s.dll;#2" % kwargs["output"] )
	manifestCommand.append("-manifest")
	manifestCommand.append("%s.dll.intermediate.manifest" % kwargs["output"] )
	build.schedule( ScheduleItem( manifestCommand ) )
	

