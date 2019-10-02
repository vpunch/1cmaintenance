call "%~dp0settings.bat"
set STOR=%STOR%\elog

setlocal enabledelayedexpansion

echo %DATE% %TIME% %~n0 START >> "%LOG%"

if not exist "%STOR%\" mkdir "%STOR%"

set I=0
:Next
if defined IB[%I%].NAME (
    1cv8 DESIGNER /IBName "!IB[%I%].NAME!" /N "!IB[%I%].USR!" /P "!IB[%I%].PASS!" /Out "%LOG%" -NoTruncate /ReduceEventLogSize %MARK:~0,10% -saveAs "!IB[%I%].NAME! %MARK%.lgd"
    7z a -p"%PASS%" "%STOR%\!IB[%I%].NAME! %MARK%.lgd.7z" "%CD%\!IB[%I%].NAME! %MARK%.lgd"
    del "!IB[%I%].NAME! %MARK%.lgd"

    set /a "I += 1"
    goto :Next
)

forfiles /p "%STOR%" /m *.7z /d -360 /c "cmd /c del @path"

echo %DATE% %TIME% %~n0 END >> "%LOG%"
