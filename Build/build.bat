@echo off
chcp 65001 >nul
setlocal

:: ============================================
::  CppStudy 一键编译脚本
::  使用 MSBuild 编译 CppStudy.sln
:: ============================================

:: MSBuild 路径 (VS2022 Community)
set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

:: 解决方案路径
set SLN="%~dp0CppStudy.sln"

:: 编译配置 (Debug / Release)
if "%1"=="" (
    set CONFIG=Debug
) else (
    set CONFIG=%1
)

:: 编译平台 (x64 / x86 / ARM / ARM64)
if "%2"=="" (
    set PLATFORM=x64
) else (
    set PLATFORM=%2
)

echo ============================================
echo  CppStudy Build Script
echo  Configuration: %CONFIG%
echo  Platform:      %PLATFORM%
echo ============================================
echo.

:: 检查 MSBuild 是否存在
if not exist %MSBUILD% (
    echo [ERROR] MSBuild not found at %MSBUILD%
    echo Please check your Visual Studio installation.
    echo You can also run this from "Developer Command Prompt for VS 2022".
    exit /b 1
)

:: 检查解决方案文件是否存在
if not exist %SLN% (
    echo [ERROR] Solution file not found: %SLN%
    exit /b 1
)

:: 执行编译
echo Building...
echo.
%MSBUILD% %SLN% /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /m /v:minimal /nologo

if %ERRORLEVEL% equ 0 (
    echo.
    echo ============================================
    echo  Build succeeded! [%CONFIG% ^| %PLATFORM%]
    echo ============================================
) else (
    echo.
    echo ============================================
    echo  Build failed! [Error code: %ERRORLEVEL%]
    echo ============================================
)

exit /b %ERRORLEVEL%
