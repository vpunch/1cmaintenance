call "%~dp0settings2.bat"
set STOR=%STOR%\sql

setlocal enabledelayedexpansion

echo %DATE% %TIME% %~n0 START >> "%LOG%"

if not exist "%STOR%\" mkdir "%STOR%"

set I=0
:Next
if defined IB[%I%].DB (
    set DBS=%DBS% !IB[%I%].DB!
    set /a "I += 1"
    goto :Next
)

if not defined DBS (
    for /f %%D in ('psql -t -A -c "SELECT datname FROM pg_database WHERE datname NOT IN ('template0', 'template1', '%PGUSER%');"') do (
        set DBS=%%D !DBS!
    )
)

for %%D in (%DBS%) do (
    pg_dump -d %%D | 7z a -p"%PASS%" -si "%STOR%\%%D %MARK%.sql.7z"
    echo VACUUM FULL ANALYZE; REINDEX DATABASE %%D; | psql -d %%D
) >>"%LOG%" 2>&1

forfiles /p "%STOR%" /m *.7z /d -90 /c "cmd /c del @path"

echo %DATE% %TIME% %~n0 END >> "%LOG%"
