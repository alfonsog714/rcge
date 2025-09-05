REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get list of all the .c files
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=testbed
SET compilerFlags=-g
SET includeFlags=-Isrc -I../engine/src/
SET linkerFlags=-L../bin/ -lengine.lib
SET defines=-D_DEBUG -DRCIMPORT

ECHO "Building %assembly%. . ."
clang %defines% %includeFlags% %compilerFlags% %cFilenames% -o ../bin/%assembly%.exe %linkerFlags%