call "%~dp0settings2.bat"
set STOR=%STOR%\bin

echo %DATE% %TIME% %~n0 START >> "%LOG%"

:: Позаботится о существовании папки
pg_basebackup -w -F tar -z -D "%STOR%\%MARK%"

echo %DATE% %TIME% %~n0 END >> "%LOG%"
