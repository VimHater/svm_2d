#!/bin/env bash
mkdir -p wasm_build/
cd wasm_build/

em++ -o index.html ../src/main.cpp -Wall -std=c++23 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I ../build/external/raylib-master/src/ -I ../build/external/src/external -L. -L ../build/external/raylib-master/src/ -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file ../build/external/raylib-master/src/shell.html ../build/external/raylib-master/src/web/libraylib.web.a -DPLATFORM_WEB -s EXPORTED_FUNCTIONS=["_free","_malloc","_main"] -s EXPORTED_RUNTIME_METHODS=ccall
