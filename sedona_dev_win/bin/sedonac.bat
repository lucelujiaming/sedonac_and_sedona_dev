@echo off
set "CURRENT_DIR=%cd%"
java -Dsedona.home="%CURRENT_DIR%" -cp "%CURRENT_DIR%\lib\*"  sedonac/Main %1

