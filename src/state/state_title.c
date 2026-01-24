#include "state_title.h"
#include "raylib.h"
#include "../game.h"
#include <stdio.h>
#include <math.h>

void state_title_enter(Game *game, StateTitleData *data){
    data->px = 0;
    data->py = 0;

    printf("Welcome to title time\n");
}

void state_title_exit(Game *game, StateTitleData *data){
    printf("Left title state\n");
}

void state_title_do_event(Game *game, StateTitleData *data){
    if (IsKeyPressed(KEY_SPACE))
        printf("JARED ROCKS\n");
    if (IsKeyPressed(KEY_ENTER))
        game_state_change(game, STATE_PLAY);
}

void state_title_do_update(Game *game, StateTitleData *data){
    data->px += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * 2;
    data->py += (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * 2;
}

void state_title_do_draw(Game *game, StateTitleData *data){
    ClearBackground(GRAY);
    
    
    DrawRectangle(data->px, data->py, 64, 64, PINK);

    {
        double result = sin(GetTime());
        DrawTextEx(
            game->font, 
            "I love u jared", 
            (Vector2){data->px, (result)*90+data->py}, 
            30, 
            ((result + 1) / 2) * 24, WHITE
        );
    }
    
    DrawFPS(0,0);

}