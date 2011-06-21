@echo off
call "%VS100COMNTOOLS%/vsvars32.bat"
msbuild Build.msbuild
pause