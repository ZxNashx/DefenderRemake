#ifndef TEXT_H
#define TEXT_H


/* Function Prototypes */
void create_button(char *base, int x, int y, const char *label);
void plot_pixel_scaled(char *base, int x, int y, int color, int scale);
void plot_number(char *base, int num, int x, int y, int scale);
void plot_character(char *base, char character, int x, int y, int scale);
void plot_string(char *base, const char *string, int x, int y, int scale);

#endif 
