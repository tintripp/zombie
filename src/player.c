#include "player.h"

void player_init(Player *player){
    player->x = 0;
    player->y = 0;
    player->sprite = LoadImage("res/player.png");
    player->speed = 120;
}
void player_cleanup(Player *player){
    UnloadImage(player->sprite);
}

void player_event(Player *player){
    
}
void player_update(Player *player){
    Vector2 move_vec = (Vector2){
        IsKeyDown(KEY_D) - IsKeyDown(KEY_A), 
        IsKeyDown(KEY_S) - IsKeyDown(KEY_W)
    };

    player->x += (move_vec.x) * GetFrameTime() * player->speed;
    player->y += (move_vec.y) * GetFrameTime() * player->speed;
}
void player_draw(Player *player){
    DrawRectangle(player->x, player->y, 64, 64, PINK);
}