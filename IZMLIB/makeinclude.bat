@echo off
cd %~dp0

set INCLUDEDIR=include

if exist %INCLUDEDIR% (
    rmdir /S /Q %INCLUDEDIR%
)

mkdir %INCLUDEDIR%

xcopy /Y /S src\*.h %INCLUDEDIR%

