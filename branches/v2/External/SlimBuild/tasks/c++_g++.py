from sbuild import *

def execute( build, state, **kwargs ):
	objects = []
	for source in kwargs["source"]:
		object = FileReference( os.path.join( state.work_path, source.name + ".o" ) )
		objects.append( object )

		command = [ "g++" ]
		command.append( "-c" )
		command.append( "-o" )
		command.append( object.identity )
		command.append( source.identity )
		build.schedule( ScheduleItem( command ) )
	
	linkerCommand = [ "g++" ]
	linkerCommand.append( "-o" )
	linkerCommand.append( kwargs["output"] )
	for object in objects:
		linkerCommand.append( object.identity )
	build.schedule( ScheduleItem( linkerCommand ) )


