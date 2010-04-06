CALL "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat"
msbuild %~dp0../slimdx.proj /m /target:build /property:Configuration=Debug;Platform=x86
msbuild %~dp0../slimdx.proj /m /target:build /property:Configuration=Release;Platform=x86
msbuild %~dp0../slimdx.proj /m /target:build /property:Configuration=Debug;Platform=x64
msbuild %~dp0../slimdx.proj /m /target:build /property:Configuration=Release;Platform=x64
