#include "raylib.h"
#include <stdio.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);

    InitWindow(800, 450, "STRAIGHT PROGRAM");

    Font font = LoadFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf");

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_A))
            printf("JARED ROCKS\n");

        BeginDrawing();
        ClearBackground(BLANK);
        if (IsKeyDown(KEY_A))
            DrawTextEx(font, "I love u jared", (Vector2){190, 200}, 80, 10, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
