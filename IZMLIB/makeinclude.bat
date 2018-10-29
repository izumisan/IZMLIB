@echo off
cd /d %~dp0

echo Make include directory...

set INCLUDEDIR=include

if exist %INCLUDEDIR% (
    rmdir /S /Q %INCLUDEDIR%
)

mkdir %INCLUDEDIR%

xcopy /Y /S src\*.h %INCLUDEDIR%

