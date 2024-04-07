#ifndef FONT_H
#define FONT_H

#include "defs.h"

extern const uint8_t font[];     /* 8x8 system font */

#define FONT_HEIGHT 8
#define CHAR_BEL    7
#define CHAR_TAB    9
#define CHAR_LF    10
#define CHAR_VT    11
#define CHAR_FF    12
#define CHAR_CR    13
#define CHAR_DEL  127

#define IS_PRINTABLE(i) ((i) >= ' ' && (i) <= '~')
#define GLYPH_START(i) (font + (((i) - ' ') << 3))


#define FONT_WIDTH  8   

#endif
