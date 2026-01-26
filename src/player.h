#pragma once
#include "raylib.h"

typedef enum PlayerDirection {
    PLRDIR_RIGHT = 1,
    PLRDIR_LEFT = -1
} PlayerDirection;

typedef enum PlayerAnim { // int offsets to anims in spritesheet
    PLRANIM_FACEDOWN = 0,
    PLRANIM_FACEUP = 2
} PlayerAnim;

typedef struct Player Player;

struct Player{
    Texture sprite;
    Vector2 velocity;

    PlayerDirection dir;
    PlayerAnim anim;
    float anim_frame;

    float speed;
    float x, y;
    int w, h;
};

void player_init(Player *player);
void player_cleanup(Player *player);

void player_event(Player *player);
void player_update(Player *player);
void player_draw(Player *player);