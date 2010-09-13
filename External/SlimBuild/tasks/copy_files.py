import os
import shutil

from sbuild import *

def execute( build, state, **kwargs ):
	if not kwargs.has_key("files"):
		return

	if not kwargs.has_key("destination"):
		return

	def delegate( log ):
		files = kwargs["files"]
		destination = kwargs["destination"]

		for source_file in files:
			log( "copying {0} to {1}.{2}", source_file.identity, destination, source_file.name )
			shutil.copy( source_file.identity, destination );

	build.schedule( ScheduleItem( delegate ) )

	
