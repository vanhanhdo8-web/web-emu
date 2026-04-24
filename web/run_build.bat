@echo off
call c:\Users\vanha\Downloads\emsdk\emsdk_env.bat >nul 2>&1
set PATH=C:\Users\vanha\AppData\Local\Microsoft\WinGet\Packages\Ninja-build.Ninja_Microsoft.Winget.Source_8wekyb3d8bbwe;%PATH%
cd /d c:\Users\vanha\Downloads\antigravity-awesome-skills\CasioEmuAndroid\web\build
echo === START BUILD === > build_out.log 2>&1
echo PATH=%PATH% >> build_out.log 2>&1
ninja -j4 >> build_out.log 2>&1
echo === END BUILD === >> build_out.log 2>&1

