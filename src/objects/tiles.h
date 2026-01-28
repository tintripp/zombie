#pragma once
#include "../cJSON.h"

// Dude... im thinking 8 is a better size. 16 for testing tho!
#define TILE_SIZE 16 

typedef enum TileType {
    TILE_AIR = 0,
    TILE_BRICK,
    TILE_SPIKE
} TileType;

typedef struct Tiles {
    TileType *arr;
    int w, h;

    char *json_str;
    cJSON *json;
} Tiles;

// futureproofing, it will return 0 on success
int tiles_load(Tiles *tiles, const char *filepath); 

void tiles_free(Tiles *tiles);
void tiles_draw(Tiles *tiles);

TileType tiles_get_at(Tiles *tiles, int row, int col);