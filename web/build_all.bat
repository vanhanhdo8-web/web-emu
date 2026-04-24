@echo off
setlocal

call c:\Users\vanha\Downloads\emsdk\emsdk_env.bat
set PATH=C:\Program Files\CMake\bin;C:\Users\vanha\AppData\Local\Microsoft\WinGet\Packages\Ninja-build.Ninja_Microsoft.Winget.Source_8wekyb3d8bbwe;%PATH%

cd /d c:\Users\vanha\Downloads\antigravity-awesome-skills\CasioEmuAndroid\web

if not exist build mkdir build
cd build

echo === Running emcmake ===
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja > build_all.log 2>&1
if errorlevel 1 (
    echo CMAKE FAILED
    type build_all.log
    exit /b 1
)

echo === Running ninja ===
ninja -v >> build_all.log 2>&1
if errorlevel 1 (
    echo NINJA FAILED
    type build_all.log
    exit /b 1
)

echo === BUILD SUCCESS ===
type build_all.log

