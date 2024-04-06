#ifndef DEFINITIONS_H  
#define DEFINITIONS_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

#define true 1
#define false 0

#define BITMAP_WIDTH 16
#define BITMAP_HEIGHT 8

#define BUFFER_SIZE 32000

/* These are very arbitrary. */
#define SHOT_COUNT 256
#define ENTITY_COUNT 256


typedef unsigned char uint8_t; 
typedef signed char int8_t;   
typedef int int16_t;         
typedef unsigned int uint16_t;  
typedef long int32_t;      
typedef unsigned long uint32_t; 

/* keys */
#define SCAN_CODE_LEFT_ARROW  0x4B
#define SCAN_CODE_RIGHT_ARROW 0x4D
#define SCAN_CODE_UP_ARROW    0x48
#define SCAN_CODE_DOWN_ARROW  0x50
#define SCAN_CODE_SPACE       0x39
#define MUSIC_UPDATE_INTERVAL 14

#define longs_buffer (SCREEN_WIDTH >> 5) * SCREEN_HEIGHT

/* Define PSG register base addresses */
#define PSG_REG_SELECT  0xff8800
#define PSG_REG_WRITE   0xff8802


#endif
