REM Remove spaces from the root path.
set root=%1
set root=%root:"=%

if %2==x86 call "%root%external\nunit\bin\nunit-console-x86.exe" "%root%tests\SlimDX\bin\%2\%3\SlimDX.Tests.dll"
if %2==x64 call "%root%external\nunit\bin\nunit-console.exe" "%root%tests\SlimDX\bin\%2\%3\SlimDX.Tests.dll"