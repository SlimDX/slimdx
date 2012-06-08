@echo off
call "%VS100COMNTOOLS%/vsvars32.bat"
msbuild "%~dp0\Build.msbuild"
pause