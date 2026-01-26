#pragma once
#include "raylib.h"

typedef struct Player Player;

struct Player{
    int x, y, speed;
    Image sprite;
};

void player_init(Player *player);
void player_cleanup(Player *player);

void player_event(Player *player);
void player_update(Player *player);
void player_draw(Player *player);