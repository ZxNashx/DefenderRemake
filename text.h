#ifndef TEXT_H
#define TEXT_H


/*
Function: create_button
Arguments:
    char *base: The start of the video memory.
    int x: x position of the button's top left corner.
    int y: y position of the button's top left corner.
    const char *label: The text label to be displayed on the button.
Description:
    Creates a button at the specified (x, y) coordinates with the provided label.
*/
void create_button(char *base, int x, int y, const char *label);

/*
Function: plot_pixel_scaled
Arguments:
    char *base: The start of the video memory.
    int x: x position of the pixel.
    int y: y position of the pixel.
    int color: The color of the pixel (1 for black, 0 for white).
    int scale: The scaling factor for the pixel size.
Description:
    Plots a single pixel at the specified (x, y) location with a specified color and scaling factor.
*/
void plot_pixel_scaled(char *base, int x, int y, int color, int scale);

/*
Function: plot_number
Arguments:
    char *base: The start of the video memory.
    int num: The number to be plotted.
    int x: x position where the number will start.
    int y: y position where the number will start.
    int scale: The scaling factor for the number's size.
Description:
    Plots a numeric value at the specified location with a given scale.
*/
void plot_number(char *base, int num, int x, int y, int scale);

/*
Function: plot_character
Arguments:
    char *base: The start of the video memory.
    char character: The character to be plotted.
    int x: x position of the character.
    int y: y position of the character.
    int scale: The scaling factor for the character's size.
Description:
    Plots a single character at the specified (x, y) location with a scaling factor.
*/
void plot_character(char *base, char character, int x, int y, int scale);

/*
Function: plot_string
Arguments:
    char *base: The start of the video memory.
    const char *string: The string to be plotted.
    int x: x position where the string will start.
    int y: y position where the string will start.
    int scale: The scaling factor for the string's size.
Description:
    Plots a string at the specified location with a given scale.
*/
void plot_string(char *base, const char *string, int x, int y, int scale);


#endif 
