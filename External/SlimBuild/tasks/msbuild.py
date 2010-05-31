import string

from sbuild import *

def execute( build, state, **kwargs ):
	#TODO: Should we use dictionaries for properties instead of
	#      making the user specify the KVP directly.
	properties = kwargs.get( "properties", [] )

	if build.env.hostPlatform == Environment.WINDOWS:
		for project in kwargs["projects"]:
			command = [ "msbuild" ]
			command.append( "/nologo" )
			
			if len(properties) > 0:
				command.append( "/p:{0}".format( string.join( properties, ';' ) ) )

			command.append( project.fullPath )
	
	build.schedule( ScheduleItem( command ) )
	
