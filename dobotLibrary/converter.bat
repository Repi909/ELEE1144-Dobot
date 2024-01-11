@echo off
set "batdir=%~dp0"
pushd "%batdir%"
:loop:
echo hex: Entering hex to get dec
echo dec: Entering dec to get hex
echo mod: Entering amount and dividing amount to get mod and 2s complement of mod
echo cls: Clears the console
set /p ans=

if %ans% == hex (
goto hex 
) else (
if %ans% == dec (
goto dec
) else (
if %ans% == cls (
cls
goto loop
) else (
if %ans% == mod (
goto mod
)
)
)
)

:hex:
echo Enter hex e.g. 000
set /p HEX=
set /a DEC=0x%HEX%
echo HEX=%HEX%
echo DEC=%DEC%
echo.
goto loop

:dec:
echo Enter dec e.g. 65
set /p DEC=
cmd /C exit %DEC%
set "HEX=%=ExitCode%"
for /f "tokens=* delims=0" %%Z in ("%HEX%") do set "HEX=%%Z"
echo DEC=%DEC% 
echo HEX=%HEX%
echo.
goto loop

:mod:
set /a mod=0
echo Enter DEC or HEX ('0x00' format) numbers, after enter 'd' to complete addition.
:modnum:
set /p inputnummod=

echo %inputnummod% | findstr /i /c:"0x" >nul
if %errorlevel% equ 1 goto skipcon
set /a inputnummod=%inputnummod%
echo DEC TRANSLATION=%inputnummod%
echo.
:skipcon:

if %inputnummod% == d goto startmod
set /a mod=%mod%+%inputnummod%
goto modnum
:startmod:
set /a counter=0
echo Enter moddiv
rem set /p MODdiv=
set /a MODdiv=256
:modredo:
set /a counter=%counter%+1
set /a mod=%mod%-%moddiv%
if %mod% GTR -1 goto modredo
set /a mod=%mod%+%moddiv%
echo ans=%mod%
set /a modtcans=256-%mod%
echo 2s complement of %mod%: %modtcans%
goto loop