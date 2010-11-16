REM @ECHO OFF
REM Run the generator from the current configuration
pushd "%~dp0\Bin\%1"
SlimDX.Generator.exe
popd






