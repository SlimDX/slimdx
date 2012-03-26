@echo off

setlocal
set error=0

call :CompileShader SimpleFontEffect vs VS
call :CompileShader SimpleFontEffect ps PS

call :CompileShader ClippingFontEffect vs VS
call :CompileShader ClippingFontEffect ps PS

call :CompileShader SpriteEffect vs VS
call :CompileShader SpriteEffect ps PS

echo.

if %error% == 0 (
    echo Shaders compiled ok
) else (
    echo There were shader compilation errors!
)

endlocal
exit /b

:CompileShader
set fxc="%DXSDK_DIR%/utilities/bin/x64/fxc" /nologo %1.fx /T%2_4_0_level_9_1 /Zpc /Qstrip_reflect /Qstrip_debug /E%3 /FoCompiled\%1_%3.fxo
echo.
echo %fxc%
%fxc% || set error=1
exit /b
