#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#include "model.h"
#include "renderer.h"
#include "raster.h"
#include "defs.h"


int main() {
    char *base = (char *)Physbase();
    GameModel model;
    int i;

    initModel(&model);

    /* Center the player */
    model.player.x = SCREEN_WIDTH / 2;
    model.player.y = SCREEN_HEIGHT / 2;

    model.aliens[0].x = SCREEN_WIDTH / 2;
    model.aliens[0].y = model.player.y - 20; 
    model.aliens[0].active = 1; 
    model.aliens[1].x = SCREEN_WIDTH / 2;
    model.aliens[1].y = model.player.y - 40; 
    model.aliens[1].active = 1; 

    /* player & alien speeds */
    model.player.dx = 8; 
    model.aliens[0].dx = 4;
    model.aliens[1].dx = 12;

    /* start testing loop */
    while (model.game_running) {
        updateModel(&model);
        clear_black(base);
        render(&model, base);
		Vsync();
        if (model.aliens[0].x > SCREEN_WIDTH) {
            /* when the slowest one leaves the screen */
            model.game_running = false; 
        }
    }

    return 0;
}
