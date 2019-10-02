call "%~dp0\..\settings.bat"
set STOR=%STOR%\dt

setlocal enabledelayedexpansion

echo %DATE% %TIME% %~n0 START >> "%LOG%"

if not exist "%STOR%\" mkdir "%STOR%"

set I=0
:Next
if defined IB[%I%].NAME (
    1cv8 DESIGNER /IBName "!IB[%I%].NAME!" /N "!IB[%I%].USR!" /P "!IB[%I%].PASS!" /DumpIB "!IB[%I%].NAME! %MARK%.dt"
    7z a -p"%PASS%" "%STOR%\!IB[%I%].NAME! %MARK%.dt.7z" "%CD%\!IB[%I%].NAME! %MARK%.dt"
    del "!IB[%I%].NAME! %MARK%.dt"

    1cv8 DESIGNER /IBName "!IB[%I%].NAME!" /N "!IB[%I%].USR!" /P "!IB[%I%].PASS!" /IBCheckAndRepair -ReIndex -LogAndRefsIntegrity -IBCompression -RecalcTotals

    set /a "I += 1"
    goto :Next
)

forfiles /p "%STOR%" /m *.7z /d -90 /c "cmd /c del @path"

echo %DATE% %TIME% %~n0 END >> "%LOG%"
