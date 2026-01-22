#!/bin/bash

WINDOWS=false
WIN_FLAGS=""

for arg in "$@"; do
    case $arg in
        -noconsole)
            WIN_FLAGS="$WIN_FLAGS -mwindows"
            ;;
        -win32)
            WINDOWS=true
            ;;        
        *)
            echo "Unknown option: $arg"
            ;;
    esac
done

RAYLIB="$HOME/raylib"

if [ "$WINDOWS" = true ]; then

    x86_64-w64-mingw32-gcc src/main.c \
        -I"$RAYLIB/src" \
        "$RAYLIB/build-mingw/raylib/libraylib.a" \
        -lopengl32 -lgdi32 -lwinmm $WIN_FLAGS

else

    gcc src/main.c \
        -I"$RAYLIB/src" \
        "$RAYLIB/src/libraylib.a" \
        -lGL -lm -lpthread -ldl -lrt -lX11

fi
