call "%~dp0\..\settings.bat"
set STOR=%STOR%\bin

if not exist "%STOR%\" mkdir "%STOR%"

echo %DATE% %TIME% %~n0 START >> "%LOG%"

set I=0
:Next
if defined IB[%I%].DB (
    call 7z a -p"%PASS%" "%STOR%\%%IB[%I%].NAME%% %MARK%.7z" "%%IB[%I%].DB%%"

    set /a "I += 1"
    goto :Next
)

forfiles /p "%STOR%" /m *.7z /d -30 /c "cmd /c del @path"

echo %DATE% %TIME% %~n0 END >> "%LOG%"
