from sbuild import *

def execute( build, state, **kwargs ):
	script = kwargs["script"]
	build.run( script )
	
