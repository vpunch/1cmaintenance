call "%~dp0settings2.bat"

:: %1 file name
:: %2 file path
set DEST=%STOR%\log\%1.7z
if not exist "%DEST%" (7z a -ssw "%DEST%" "%CD%\%2")
