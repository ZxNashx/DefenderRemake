
/* raster.c */

#include "raster.h"
#include "defs.h"

#include <stdio.h>
#include <linea.h>
#include <osbind.h>

void plot_pixel(char *base, int x, int y, int black) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        char *pixel_byte = base + y * 80 + (x >> 3);
        unsigned char pixel_bit = 1 << (7 - (x & 7));

        if (black == true) {
            *pixel_byte |= pixel_bit;
        } else {
            *pixel_byte &= ~pixel_bit;
        }
    }
}


/* magic */
void clear_black(char *base) {
    unsigned int i;
    for (i = 0; i < longs_buffer; i++) {
        ((unsigned long*)base)[i] = 0xFFFFFFFF;
    }
}


void draw_hline(char *base, int x1, int x2, int y) {
    int x;  /* Declare variable at the start of the function */
    if (y >= 0 && y < SCREEN_HEIGHT) {
        if (x1 > x2) {  
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (x = x1; x <= x2; x++) {
            plot_pixel(base, x, y, 0); /* Draw each pixel in the line */
        }
    }
}

void draw_vline(char *base, int y1, int y2, int x) {
    int y;
    int temp;

    if (x >= 0 && x < SCREEN_WIDTH) {
        if (y1 > y2) {  
            temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for (y = y1; y <= y2; y++) {
            if (y >= 0 && y < SCREEN_HEIGHT) {
                plot_pixel(base, x, y, 0); /* Draw each pixel in the line */
            }
        }
    }
}


void plot_bitmap(char *base, const unsigned int *bitmap, int x, int y, int width, int height) {
    int j, i;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (bitmap[j] & (1 << (width - 1 - i))) {
                plot_pixel(base, x + i, y + j, 0);
            }
        }
    }
}


/* Function to plot pixels at the eight regions of the circle */
void drawCircle(char *base, int xc, int yc, int x, int y) {
    plot_pixel(base, xc + x, yc + y, 0);
    plot_pixel(base, xc - x, yc + y, 0);
    plot_pixel(base, xc + x, yc - y, 0);
    plot_pixel(base, xc - x, yc - y, 0);
    plot_pixel(base, xc + y, yc + x, 0);
    plot_pixel(base, xc - y, yc + x, 0);
    plot_pixel(base, xc + y, yc - x, 0);
    plot_pixel(base, xc - y, yc - x, 0); 
}

/* Function for circle-generation using Bresenham's algorithm 
from: https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ 

I would like to play with this later on
*/
void plot_circle(char *base, int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    /* the initial points */
    drawCircle(base, xc, yc, x, y);

    while (y >= x) {
        /* for each pixel we will draw all eight pixels */
        x++;

        /* Check for decision parameter and update d, x, y */
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        /* Call function to draw the circle using new parameters */
        drawCircle(base, xc, yc, x, y);
    }
}

void plot_rectangle(char *base, int x1, int y1, int x2, int y2) {
    int y;

    /* Draw the top and bottom horizontal lines of the rectangle */
    draw_hline(base, x1, x2, y1);
    draw_hline(base, x1, x2, y2);

    /* Draw the vertical sides of the rectangle */
    draw_vline(base, y1,y2, x1);
    draw_vline(base, y1,y2, x2);
}

uint16_t *get_video_base(){

}
