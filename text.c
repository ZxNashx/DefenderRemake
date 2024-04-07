#include "defs.h"
#include "font.h"
#include "raster.h"

void create_button(char *base, int x, int y, const char *label) {
    int padding;  /* Padding around the text */
    int textLength;
    int buttonWidth, buttonHeight;
    int textX, textY;
    int i; /* Loop counter */

    /* Initialize variables */
    padding = 4;
    textLength = 0;

    /* Manually calculate the length of the label */
    for (i = 0; label[i] != '\0'; i++) {
        textLength++;
    }

    buttonWidth = textLength * FONT_WIDTH + padding * 2;
    buttonHeight = FONT_HEIGHT + padding * 2;

    /* Draw the rectangle around the text */
    plot_rectangle(base, x, y, x + buttonWidth, y + buttonHeight);

    /* Plot the label in the center of the button */
    textX = x + padding;
    textY = y + padding / 2;
    plot_string(base, label, textX, textY, 1);
}


void plot_pixel_scaled(char *base, int x, int y, int color, int scale) {
    int dx,dy;
    for (dy = 0; dy < scale; dy++) {
        for (dx = 0; dx < scale; dx++) {
            plot_pixel(base, x + dx, y + dy, color);
        }
    }
}

void plot_character(char *base, char character, int x, int y, int scale) {
    const uint8_t *char_bitmap = font + (character - 32) * FONT_HEIGHT;
    uint8_t row, j, i;

    for (j = 0; j < FONT_HEIGHT; j++) {
        row = char_bitmap[j];
        for (i = 0; i < FONT_WIDTH; i++) {
            if (row & (1 << (BITS_IN_BYTE - 1 - i))) {
                plot_pixel_scaled(base, x + i * scale, y + j * scale, 0, scale);
            }
        }
    }
}

void plot_string(char *base, const char *string, int x, int y, int scale) {
    while (*string) {
        plot_character(base, *string, x, y, scale);
        x += FONT_WIDTH * scale;
        string++;
    }
}
