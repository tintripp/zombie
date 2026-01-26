#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include <stdio.h>

void player_init(Player *player){
    player->sprite = LoadTexture("res/player.png");
    player->dir = PLRDIR_RIGHT;

    player->anim = PLRANIM_FACEDOWN;
    player->anim_frame = 0;

    player->velocity = (Vector2){ 0, 0 };
    player->speed = 50;
    player->x = 80;
    player->y = 30;
    player->w = 16;
    player->h = 22;
}
void player_cleanup(Player *player){
    UnloadTexture(player->sprite);
}

void player_event(Player *player){
    
}
void player_update(Player *player){
    Vector2 move_vec = (Vector2){
        IsKeyDown(KEY_D) - IsKeyDown(KEY_A), 
        IsKeyDown(KEY_S) - IsKeyDown(KEY_W)
    };
    player->velocity = Vector2Scale(
        Vector2Normalize(move_vec), player->speed
    );

    player->anim_frame += Vector2Length(player->velocity) * GetFrameTime() / 8;
    if (player->velocity.x < 0) player->dir = PLRDIR_LEFT;
    if (player->velocity.x > 0) player->dir = PLRDIR_RIGHT;
    if (player->velocity.y < 0) player->anim = PLRANIM_FACEUP;
    if (player->velocity.y > 0) player->anim = PLRANIM_FACEDOWN;

    player->x += (player->velocity.x) * GetFrameTime();
    player->y += (player->velocity.y) * GetFrameTime();
}
void player_draw(Player *player){
    //DrawRectangle(player->x, player->y, player->w, player->h, PINK);

    if (!Vector2Length(player->velocity)){
        player->anim_frame = 0;
    }
    //soon 2 will be anim length -- make json parsing work
    int frame = ((int)player->anim_frame % 2) + player->anim; 

    DrawTextureRec(
        player->sprite, 
        (Rectangle){
            player->w * frame, 0,
            player->w * player->dir, player->h
        }, 
        (Vector2){ player->x, player->y, }, 
        WHITE
    );
}