CALL "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat"
msbuild %~dp0../slimdx.proj /target:build /property:Configuration=%1;Platform=%2 /v:m
exit %ERRORLEVEL%
