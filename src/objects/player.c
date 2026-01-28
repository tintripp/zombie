#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

void player_init(Player *player){
    player->sprite = LoadTexture("res/images/onionboy.png");
    player->dir = PLRDIR_RIGHT;

    player->anim_frame = 0;
    player->frame_offx = 4;
    player->frame_offy = 15;
    player->frame_w = 16;
    player->frame_h = 23;

    player->velocity = (Vector2){ 0, 0 };
    player->hitbox = (Rectangle){ 80, 30, 8, 8 }; 
    player->speed = 6;
}
void player_free(Player *player){
    UnloadTexture(player->sprite);
}

void player_event(Player *player){
    if (IsKeyPressed(KEY_W))
        player->velocity.y = -160;
}
void player_update(Player *player, Tiles *tiles){
    player->velocity.x += (
        IsKeyDown(KEY_D) - IsKeyDown(KEY_A)
    ) * player->speed;
    player->velocity.x *= 0.95;

    player->anim_frame += abs((int)player->velocity.x) * GetFrameTime() / 8;
    if (player->velocity.x < 0) player->dir = PLRDIR_LEFT;
    if (player->velocity.x > 0) player->dir = PLRDIR_RIGHT;

    //gravity
    player->velocity.y += 360 * GetFrameTime();
    
    player_move(player, tiles, Vector2Scale(player->velocity, GetFrameTime()));
}
void player_draw(Player *player){
    if (!round(player->velocity.x)){
        player->anim_frame = 0;
    }
    //soon 2 will be anim length -- make json parsing work
    int frame = ((int)player->anim_frame % 2); 

    DrawTextureRec(
        player->sprite, 
        (Rectangle){
            player->frame_w * frame, 0,
            player->frame_w * player->dir, player->frame_h
        }, 
        (Vector2){ 
            player->hitbox.x - player->frame_offx, 
            player->hitbox.y - player->frame_offy 
        }, 
        WHITE
    );
    
    //DrawRectangleRec(player->hitbox, PINK);
}

void player_move_axis(
    Player *player, 
    Tiles *tiles, 
    float *remainder, 
    float *hitbox_pos, 
    float *velocity, 
    float dv
) {
    float total = dv + *remainder;
    int amt = (int)total;
    *remainder = total - amt;

    int sign = (amt > 0) - (amt < 0);

    while (amt != 0){
        *hitbox_pos += sign;

        // this loops through every tile.. 
        // make a function to find only tiles the hitbox is in.
        bool collided = false;
        for (int r = 0; r < tiles->h; r++){
            for (int c = 0; c < tiles->w; c++){
                TileType tile = tiles_get_at(tiles, r, c);

                if (
                    tile == TILE_BRICK &&
                    CheckCollisionRecs(
                    player->hitbox,
                    (Rectangle){
                        c * TILE_SIZE, r * TILE_SIZE,
                        TILE_SIZE, TILE_SIZE,
                    }
                )) {
                    collided = true;
                    break;
                }

            }
            if (collided) break;
        }

        if (collided){
            *hitbox_pos -= sign;
            *velocity = 0;
            break;
        }

        amt -= sign;
    }

}

void player_move(Player *player, Tiles *tiles, Vector2 dv) {
    player_move_axis(player, tiles, 
        &player->remainder.x, 
        &player->hitbox.x, 
        &player->velocity.x, 
        dv.x
    );
    player_move_axis(player, tiles, 
        &player->remainder.y, 
        &player->hitbox.y, 
        &player->velocity.y, 
        dv.y
    );
}