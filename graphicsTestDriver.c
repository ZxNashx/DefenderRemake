#include "raster.h"
#include "bitmap.h"
#include "defs.h"

#include <osbind.h>

int main() {
    char *base = (char *)Physbase();

    /* Position objects around the screen */

    int midX = SCREEN_WIDTH / 2;
    int midY = SCREEN_HEIGHT / 2;
    int spaceship_x = 50;
    int spaceship_y = 50;
    int alien_x = SCREEN_WIDTH - 50;
    int alien_y = SCREEN_HEIGHT - 50;

    /* Clear the screen */
    clear_black(base);

    /* Call raster functions to draw onto the screen*/
    draw_hline(base, 10, 100, midY - 20);
    plot_circle(base, midX, midY, 20);
    plot_bitmap(base, spaceship_bitmap, spaceship_x, spaceship_y, 16, 8);
    plot_bitmap(base, alien_bitmap, alien_x, alien_y, 16, 8);

    return 0;
}

