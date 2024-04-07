#ifndef TEXT_H
#define TEXT_H

#define FONT_WIDTH  8   
#define FONT_HEIGHT 8  
#define BITS_IN_BYTE 8


void plot_pixel_scaled(char *base, int x, int y, int color, int scale);
void plot_character(char *base, char character, int x, int y, int scale);
void plot_string(char *base, const char *string, int x, int y, int scale);
void create_button(char *base, int x, int y, const char *label);

#endif 
