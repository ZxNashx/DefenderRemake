
/* raster.c */

#include "raster.h"
#include "defs.h"
#include "isr.h"
#include "bitmap.h"

#include <stdio.h>
#include <linea.h>
#include <osbind.h>

void swapBuffers(char **buffer1, char **buffer2) {
    char *temp = *buffer1;
    *buffer1 = *buffer2;
    *buffer2 = temp;
}

void copyBuffer(char *source, char *destination, int size) {
    int register i;

    /* Unroll loop to process eight items per iteration */
    for (i = 0; i < size; i += 8) {
        destination[i] = source[i];
        destination[i + 1] = source[i + 1];
        destination[i + 2] = source[i + 2];
        destination[i + 3] = source[i + 3];
        destination[i + 4] = source[i + 4];
        destination[i + 5] = source[i + 5];
        destination[i + 6] = source[i + 6];
        destination[i + 7] = source[i + 7];
    }
}

void plot_mouse(char * currentBuffer, char * title_screen) {
    /* Update mouse position based on deltas */
    mouse_x += mouse_dx;
    mouse_y += mouse_dy;

    /* Reset deltas */
    mouse_dx = 0;
    mouse_dy = 0;

    /* Boundary checks */
    if (mouse_x < 0) mouse_x = 0;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_x > SCREEN_WIDTH - BITMAP_WIDTH) mouse_x = SCREEN_WIDTH - BITMAP_WIDTH;
    if (mouse_y > SCREEN_HEIGHT - BITMAP_HEIGHT) mouse_y = SCREEN_HEIGHT - BITMAP_HEIGHT;

    /* Plot the mouse at the new position */
    plot_bitmap(currentBuffer, mouse_bitmap, mouse_x, mouse_y, BITMAP_WIDTH, BITMAP_HEIGHT);
}


char *get_video_base() {
    long old_ssp = Super(0);
    volatile unsigned char *frame_hi = (unsigned char *)0xFFFF8201;
    volatile unsigned char *frame_mi = (unsigned char *)0xFFFF8203;

    unsigned long frame_buffer = ((unsigned long)(*frame_hi) << 16) | ((unsigned long)(*frame_mi) << 8);

    Super(old_ssp);
    return (char *)frame_buffer;
}

void set_video_base(char *frameBuffer){
    long old_ssp = Super(0);
    set_video_base_asm(((long)frameBuffer) >> 8);
    Super(old_ssp);
}

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

void fill_rect(char *base, int x, int y, int width, int height, int black) {
    int row,col;
    for (row = y; row < y + height; row++) {
        for (col = x; col < x + width; col++) {
            plot_pixel(base, col, row, black);
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

