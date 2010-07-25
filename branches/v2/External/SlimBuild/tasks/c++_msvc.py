from sbuild import *

def execute( build, state, **kwargs ):
	output = kwargs["output"]

	source_files = kwargs["source"]
	
	format = kwargs.get( "format", "app" ).lower()
	arch = kwargs.get( "arch", "x86" ).lower()
	
	features = kwargs.get( "features", "" ).lower().split()
	
	include_paths = kwargs.get( "include_paths", [] )
	library_paths = kwargs.get( "library_paths", [] )
	libraries = kwargs.get( "libraries", [] )
	
	if "clr" in features:
		assemblies = kwargs.get( "assemblies", [] )
	else:
		assemblies = []
		
	extension = "exe"
	if format == "dll":
		extension = "dll"
	
	if arch == "x64":
		compiler = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/amd64/cl.exe"
		linker = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/amd64/link.exe"
		mt = "C:/Program Files/Microsoft SDKs/Windows/v6.0A/Bin/x64/mt.exe"
	else:
		compiler = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/cl.exe"
		linker = "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/link.exe"
		mt = "C:/Program Files/Microsoft SDKs/Windows/v6.0A/Bin/mt.exe"

	dirty_files = []	
	object_files = []
	for source_file in source_files:
		if state.isFileDirty( source_file.identity ):
			object_file = FileReference( os.path.join( state.work_path, source_file.name + ".obj" ) )
			object_files.append( object_file )

			dirty_files.append( source_file.identity )

	compileCommand = [ compiler ]
	compileCommand.append( "/nologo" )

	if "clr" in features:
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
	
	compileCommand.append( "/Fo{0}/".format( state.work_path ) )
	for dirty_file in dirty_files:
		compileCommand.append( dirty_file )

	build.schedule( ScheduleItem( compileCommand ) )
	
	linkCommand = [ linker ]
	linkCommand.append( "/NOLOGO" )
	if format == "dll":
		linkCommand.append( "/DLL" )
	linkCommand.append( "/INCREMENTAL:NO" )
	linkCommand.append( "/DEBUG" )
	linkCommand.append( "/MANIFESTFILE:{0}.{1}.intermediate.manifest".format( output, extension ) )
	linkCommand.append( "/MANIFESTUAC:level='asInvoker' uiAccess='false'")
	linkCommand.append( "/MACHINE:{0}".format( arch ) );
	
	for path in library_paths:
		linkCommand.append( "/LIBPATH:{0}".format( path ) )
	
	linkCommand.append( "/OUT:{0}.{1}".format( output, extension ) )
	for object_file in object_files:
		linkCommand.append( object_file.identity )
	for library in libraries:
		linkCommand.append( library )
		
	build.schedule( ScheduleItem( linkCommand ) )
	
	manifestCommand = [ mt ]
	manifestCommand.append( "-nologo")
	manifestCommand.append( "-outputresource:{0}.{1};#2".format( output, extension ) )
	manifestCommand.append( "-manifest")
	manifestCommand.append( "{0}.{1}.intermediate.manifest".format( output, extension ) )
	build.schedule( ScheduleItem( manifestCommand ) )
