#ifndef RASTER_H
#define RASTER_H
#include "defs.h"

extern char* backBuffer;
extern char* frontBuffer;
extern char* orig_buffer;
extern char rawBackBuffer[BUFFER_SIZE + 256];


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
/*void clear_black(char *base);*/

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

/*
Function: get_video_base
Arguments: None.
Returns:
    char *: A pointer to the start of the current video memory (frame buffer).
Description:
    Retrieves the address of the current frame buffer being used for video output.
*/
char * get_video_base();

/*
Function: set_video_base_asm
Arguments:
    unsigned int base: The 24-bit address to set as the new video base.
Description:
    Assembly function to set the new video base address for the frame buffer. This is an assembly implementation to ensure atomic operation and precise timing.
*/
extern void set_video_base_asm(unsigned int);

/*
Function: clear_black
Arguments:
    char *base: The start of the video memory to be cleared.
Description:
    Sets the entire screen to black by writing to the video memory starting from 'base'.
*/
extern void clear_black(char * base);

/*
Function: set_video_base
Arguments:
    char *base: The start of the video memory to be set as the frame buffer.
Description:
    Sets the frame buffer start address to 'base'. This determines where the video output will read the graphics data from.
*/
void set_video_base(char *base);

/*
Function: fill_rect
Arguments:
    char *base: The start of the video memory.
    int x: x position of the top left corner of the rectangle.
    int y: y position of the top left corner of the rectangle.
    int width: Width of the rectangle.
    int height: Height of the rectangle.
    int black: If you want the rectangle to be black. 1 for black, 0 for white.
Description:
    Fills a rectangle with the specified dimensions and color at the given position.
*/
void fill_rect(char *base, int x, int y, int width, int height, int black);

/*
Function: swapBuffers
Arguments:
    char **frontBuffer: Pointer to the address of the current front buffer.
    char **backBuffer: Pointer to the address of the current back buffer.
Description:
    Swaps the front and back buffers. This is used in double-buffering to update the frame shown on the screen with the newly rendered frame.
*/
void swapBuffers(char **frontBuffer, char **backBuffer);

/*
Function: plot_mouse
Arguments:
    char *base: The start of the video memory.
    char *title_screen: The memory location of the title screen data.
Description:
    Plots the mouse pointer on the screen using the title screen data as a reference for the mouse graphic.
Returns:
    int: true / false for whether or not the mouse moved.
*/
int plot_mouse(char * base, char * title_screen);

/*
Function: copyBuffer
Arguments:
    char *source: Pointer to the source memory to copy from.
    char *destination: Pointer to the destination memory to copy to.
    int start: The starting index from where to begin copying.
    int size: The number of elements to copy.
Description:
    Copies a buffer from the source to the destination starting at the specified index and copying the given number of elements.
*/
void copyBuffer(char *source, char *destination, int start, int size);


#endif /* RASTER_H */
