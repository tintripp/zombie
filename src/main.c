#include "raylib.h"
#include <stdio.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);

    InitWindow(800, 450, "STRAIGHT PROGRAM");

    // LoadFont("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_A))
            printf("JARED ROCKS\n");

        BeginDrawing();
        ClearBackground(BLANK);
        if (IsKeyDown(KEY_A))
            DrawText("I love u jared", 190, 200, 80, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
