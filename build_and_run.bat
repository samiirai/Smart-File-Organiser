@echo off
cls
echo ==============================================
echo Compiling Smart File Management System...
echo ==============================================

if not exist "build" mkdir build

gcc src\main.c src\utils.c src\organizer.c src\duplicate.c src\integrity.c -o build\SmartFileTool.exe -ladvapi32

if %errorlevel% neq 0 (
    echo Build failed! Please check code for errors.
    pause
    exit /b %errorlevel%
)

echo Build Successful! Executable created in \build\SmartFileTool.exe
echo.
echo Launching Application...
echo ==============================================

cd build
SmartFileTool.exe
pause