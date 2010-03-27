from sbuild import *

def execute( build, state, **kwargs ):
	if build.env.hostPlatform == Environment.WINDOWS:
		build( "c++_msvc", **kwargs )
	else:
		build( "c++_g++", **kwargs )
	
