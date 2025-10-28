#!/bin/bash
set echo on

mkdir -p ../bin

cFilenames=$(find . -type f -name "*.c")

assembly="tests"
compilerFlags="-g -fdeclspec -fPIC"
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../bin/ -lengine.lib -Wl,-rpath,."
defines="-D_DEBUG -DRCIMPORT"

echo "Building $assembly..."
echo clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags