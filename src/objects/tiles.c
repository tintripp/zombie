#include "raylib.h"
#include "../cJSON.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TileType tiles_deduce_type(char *type){
    if (strcmp(type, "brick") == 0) return TILE_BRICK;
    if (strcmp(type, "spike") == 0) return TILE_SPIKE;
    return TILE_AIR;    
}

TileType tiles_get_at(Tiles *tiles, int row, int col){
    if (row < 0 || row >= tiles->h || col < 0 || col >= tiles->w)
        return TILE_AIR;
    return tiles->arr[row * tiles->w + col];
}

int tiles_load(Tiles *tiles, const char *filepath){
    tiles->json_str = LoadFileText(filepath);
    if (!tiles->json_str){
        printf("Could not open the file!!");
        return 1;
    }

    tiles->json = cJSON_Parse(tiles->json_str);
    if (!tiles->json){
        printf("Could not parse the file!! %s", cJSON_GetErrorPtr());
        free(tiles->json_str);
        return 1;
    }

    int width = cJSON_GetObjectItem(tiles->json, "width")->valueint;
    int height = cJSON_GetObjectItem(tiles->json, "height")->valueint;

    TileType *tile_arr = calloc(width * height, sizeof(TileType));

    cJSON *json_arr = cJSON_GetObjectItem(tiles->json, "tiles");

    for (int i = 0; i < cJSON_GetArraySize(json_arr); i++){
        cJSON *tile = cJSON_GetArrayItem(json_arr, i);
        int r = cJSON_GetObjectItem(tile, "y")->valueint;
        int c = cJSON_GetObjectItem(tile, "x")->valueint;

        cJSON *type = cJSON_GetObjectItem(tile, "t");
        if (!type || !type->valuestring) return 1;
        char *type_str = type->valuestring;
        
        //printf("%s\n", type_str);

        tile_arr[r * width + c] = tiles_deduce_type(type_str);
    }

    // finally, assign.
    tiles->w = width;
    tiles->h = height;
    tiles->arr = tile_arr;

    return 0;
}
void tiles_free(Tiles *tiles){
    cJSON_Delete(tiles->json);
    free(tiles->json_str);
}

void tiles_draw(Tiles *tiles){
    for (int r = 0; r < tiles->h; r++){
        for (int c = 0; c < tiles->w; c++){
            TileType tile = tiles_get_at(tiles, r, c);

            if (tile == TILE_BRICK)
                DrawRectangle(
                    c * TILE_SIZE, r * TILE_SIZE, 
                    TILE_SIZE, TILE_SIZE, 
                    RED
                );
            if (tile == TILE_SPIKE)
                DrawRectangle(
                    c * TILE_SIZE, r * TILE_SIZE, 
                    TILE_SIZE, TILE_SIZE, 
                    BLUE
                );
        }
    }
}