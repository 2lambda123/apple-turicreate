:: Copyright 2017 - Refael Ackermann
:: Distributed under MIT style license
:: See accompanying file LICENSE at https://github.com/node4good/windows-autoconf
:: version: 1.15.4

@if not defined DEBUG_HELPER @ECHO OFF
setlocal
set "InstallerPath=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
if not exist "%InstallerPath%" set "InstallerPath=%ProgramFiles%\Microsoft Visual Studio\Installer"
if not exist "%InstallerPath%" goto :no-vswhere
:: Manipulate %Path% for easier " handeling
set Path=%Path%;%InstallerPath%
where vswhere 2> nul > nul
if errorlevel 1 goto :no-vswhere
set VSWHERE_REQ=-requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64
set VSWHERE_PRP=-property installationPath
set VSWHERE_LMT=-version "[15.0,16.0)"
vswhere -prerelease > nul
if "%~1"=="prerelase" set VSWHERE_WITH_PRERELASE=1
if not errorlevel 1 if "%VSWHERE_WITH_PRERELASE%"=="1" set "VSWHERE_LMT=%VSWHERE_LMT% -prerelease"
SET VSWHERE_ARGS=-latest -products * %VSWHERE_REQ% %VSWHERE_PRP% %VSWHERE_LMT%
for /f "usebackq tokens=*" %%i in (`vswhere %VSWHERE_ARGS%`) do (
    endlocal
    @rem comment out setting VCINSTALLDIR for Boost.build
    @rem set "VCINSTALLDIR=%%i\VC\"
    set "VS150COMNTOOLS=%%i\Common7\Tools\"
    exit /B 0
)

:no-vswhere
endlocal
echo could not find "vswhere"
exit /B 1
