/* renderer.c - Implementation file for the Defender game rendering module */

#include "renderer.h"
#include "raster.h"
#include "bitmap.h"
#include "model.h"
#include "defs.h"

void clear_region(char *base, int x, int y, int width, int height) {
    int i,j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            plot_pixel(base, x + i, y + j, 1); 
        }
    }
}

void renderPlayer(Player *player, char *base) {
    plot_bitmap(base, spaceship_bitmap, player->x, player->y, BITMAP_WIDTH, BITMAP_HEIGHT);
}

void renderAlien(Alien *alien, char *base) {
    plot_bitmap(base, alien_bitmap, alien->x, alien->y, BITMAP_WIDTH, BITMAP_HEIGHT);
}

void renderShot(char *base, unsigned int x, unsigned int y) {
    plot_pixel(base, x, y, 0);
}

/* Render all things together */
void render(GameModel *model, char *base) {
    int i;
    renderPlayer(&model->player, base);

    for (i = 0; i < ENTITY_COUNT; i++) {
        if (model->aliens[i].active) {
            renderAlien(&model->aliens[i], base);
        }
    }
    for (i = 0; i < SHOT_COUNT; i++) {
        if (model->alienShots[i].active) {
            renderShot(base, model->alienShots[i].x, model->alienShots[i].y);
        }
        if (model->playerShots[i].active) {
            renderShot(base, model->playerShots[i].x, model->playerShots[i].y);
        }
    }
}
