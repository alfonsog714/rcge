REM Build script for the engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=engine
SET compilerFlags=-g -shared -Wvarargs -Wall -Werror
REM -Wall -Werror
SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
SET linkerFlags=-L%VULKAN_SDK%/Lib -luser32 -lvulkan-1
SET defines=-D_DEBUG -DRCEXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%. . ."
clang %defines% %includeFlags% %compilerFlags% %cFilenames% -o ../bin/%assembly%.dll %linkerFlags%