:: System proxy switch script for windows by vibiu.
:: Usage:
:: - System mode:
::      vopen system 127.0.0.1 1080(defualt=1090)
:: - Pac mode:
::      vopen auto "file:\\\C:\demo.pac"
:: - Direct mode:
::      vopen direct
@echo off

setlocal EnableDelayedExpansion
call :main %*
endlocal
goto :eof


:main ** [ret]
setlocal EnableDelayedExpansion
set command=%~1

if "%command%" equ "system" (
    echo [INFO]: proxy using system mode.
    call :enable_system_proxy %~2 %~3
) else if "%command%" equ "auto" (
    echo [INFO]: proxy using auto mode.
    call :auto_script_proxy %~2
) else if "%command%" equ "direct" (
    echo [INFO]: proxy using direct mode.
    call :direct_system_proxy
) else if "%command%" equ "status" (
    echo [INFO]: reading proxy status.
    echo "%command%"
) else (
    echo [WARNNING]: unknow command.
    echo please choose from "system", "auto", "direct".
    echo system:
    echo     "host" "port"
    echo auto:
    echo     "pacpath"
    echo direct:
)

if "%ret%" equ "0" (
    ipconfig /flushdns > nul
    echo [INFO]: opration finished.
)
endlocal & set ret=0
goto :eof


:enable_system_proxy host port [ret]
setlocal EnableDelayedExpansion
if "%~1" equ "" (set host="127.0.0.1") else (set host=%~1)
if "%~1" equ "" (set port="1090") else (set port=%~2)
echo [INFO]: check if port %port% is been used...
echo [WARNNING]: enable system http proxy on [%host%:%port%].
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "ProxyServer" ^
/t REG_SZ /d "http://%host%:%port%" /f 
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "ProxyEnable" ^
/t REG_DWORD /d 00000001 /f
endlocal & set ret=0
goto :eof


:auto_script_proxy pacpath [ret]
setlocal EnableDelayedExpansion
if "%~1" equ "" (
    set pacpath="file:\\\%cd%\pac"
) else (set pacpath=%~1)
echo [INFO]: pac script path is: "%pacpath%"
echo [WARNNING]: system proxy will use a proxy autoconfiguration script.
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "ProxyEnable" ^
/t REG_DWORD /d 00000000 /f
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "AutoConfigURL" ^
/t REG_SZ /d "%pacpath%" /f
endlocal & set ret=0
goto :eof


:direct_system_proxy [ret]
setlocal EnableDelayedExpansion
echo [WARNNING] system proxy automatically detect setting will be unset.
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "AutoDetect" ^
/t REG_DWORD /d 00000000 /f
echo [WARNNING] system proxy will be disabled.
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "ProxyEnable" ^
/t REG_DWORD /d 00000000 /f

setlocal ENABLEEXTENSIONS
set KEY_NAME="HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings"
set VALUE_NAME=AutoConfigURL
FOR /F "usebackq skip=2 tokens=1-3" %%A IN (`REG QUERY %KEY_NAME% /v %VALUE_NAME% 2^>nul`) DO (
    if not "%%A" equ "" (
        echo [WARNNING] system autoconfiguration script path will be deleted from  windows registery.
        reg delete "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v "AutoConfigURL" /f
    )
)
endlocal

endlocal & set ret=0
goto :eof
