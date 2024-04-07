#ifndef RASTER_H
#define RASTER_H
#include "defs.h"

/*
Function: plot_pixel
Arguments:
    char *base: The start of the video memory.
    int x: x position for the pixel to be plotted.
    int y: y position for the pixel to be plotted.
    int black: If you want the pixel to be black. 1 for black, 0 for white.
Description:
    Used to plot a single pixel on a x and y position.
*/
void plot_pixel(char *base, int x, int y, int black);

/*
Function: clear_black
Arguments:
    char *base: The start of the video memory.
Description:
    Sets the entire screen to black.
*/
void clear_black(char *base);

/*
Function: draw_hline
Arguments:
    char *base: The start of the video memory.
    int x1: Starting x position for the horizontal line.
    int x2: Ending x position for the horizontal line.
    int y: y position where the line will be drawn.
Description:
    Draws a horizontal line from (x1, y) to (x2, y).
*/
void draw_hline(char *base, int x1, int x2, int y);

/*
Function: plot_bitmap
Arguments:
    char *base: The start of the video memory.
    const unsigned int *bitmap: Pointer to the bitmap data.
    int x: x position where the bitmap will be plotted.
    int y: y position where the bitmap will be plotted.
    int width: Width of the bitmap.
    int height: Height of the bitmap.
Description:
    Plots a bitmap image (from bitmap.c) at the specified location.
*/
void plot_bitmap(char *base, const unsigned int *bitmap, int x, int y, int width, int height);


/*
Function: drawCircle
Arguments:
    char *base: The start of the video memory.
    int xc: x coordinate of the circle's center.
    int yc: y coordinate of the circle's center.
    int x: x coordinate of a point on the circle.
    int y: y coordinate of a point on the circle.
Description:
    Plots pixels at the eight octants of a circle centered at (xc, yc) with a point at (x, y).
    This function is a helper for the Bresenham's circle algorithm implemented in plot_circle.
*/
void drawCircle(char *base, int xc, int yc, int x, int y);


/*
Function: plot_circle
Arguments:
    char *base: The start of the video memory.
    int xc: x coordinate of the circle's center.
    int yc: y coordinate of the circle's center.
    int r: Radius of the circle.
Description:
    Plots a circle centered at (xc, yc) with radius r using Bresenham's circle drawing algorithm.
    This algorithm is efficient as it exploits the symmetry in a circle to plot all eight octants simultaneously.
*/
void plot_circle(char *base, int xc, int yc, int r);
/*
Function: plot_rectangle
Arguments:
    char *base: The start of the video memory.
    int x1: x position of the top left corner.
    int y1: y position of the top left corner.
    int x2: x position of the bottom right corner.
    int y2: y position of the bottom right corner.
Description:
    Plots a rectangle with corners at the specified coordinates.
*/
void plot_rectangle(char *base, int x1, int y1, int x2, int y2);

char * get_video_base();
extern void set_video_base_asm(unsigned int);
void set_video_base(char *base);
void fill_rect(char *base, int x, int y, int width, int height, int black);

#endif /* RASTER_H */
