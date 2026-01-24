#include "game.h"

int main(void) {
    Game g;
    game_init(&g);
    game_loop(&g);

    return 0;
}
