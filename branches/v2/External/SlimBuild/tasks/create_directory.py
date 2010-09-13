import os
import shutil

from sbuild import *

def execute( build, state, **kwargs ):
	if not kwargs.has_key("path"):
		return

	def delegate( log ):
		path = kwargs["path"]

		# rmtree will fail if the path to be removed does not exist.
		if kwargs.get( "purge", False ) == True and os.path.exists( path ):
			log( "purging directory {0}", path )
			shutil.rmtree( path )

		if not os.path.exists( path ):
			log( "creating directory {0}", path )
			
			# makedirs is documented to "become confused" if the path specified
			# contains parent directory references. To avoid this, we use an
			# absolute version of the desired path.
			os.makedirs( os.path.abspath( path ) )

	build.schedule( ScheduleItem( delegate ) )

	
