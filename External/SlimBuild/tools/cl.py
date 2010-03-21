def find( options ):
	if "x64" in options:
		return "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/amd64/cl.exe"
	return "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/cl.exe"