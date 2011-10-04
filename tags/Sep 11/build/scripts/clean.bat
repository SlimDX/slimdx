CALL "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat"
msbuild %~dp0../slimdx.proj /target:Clean /v:m
exit %ERRORLEVEL%
