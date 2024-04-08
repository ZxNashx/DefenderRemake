#include <stdio.h>
#include <osbind.h>

#include "defs.h"
#include "model.h"
#include "isr.h"
#include "music.h"
#include "events.h"

#include "bitmap.h"
#include "raster.h"

void init_isr(){
    orig_vector_vbl = install_vector(VBL_VECTOR, vbl_isr);
    orig_vector_ikbd = install_vector(IKBD_VECTOR, ikbd_isr);
    vbl_counter = 0;
    render_request = false;
    music_update_request = false;
    
}

void do_VBL_ISR() {
    music_update_request = true;
    render_request = true;
    vbl_counter++;
}

void clean_isr(){
    install_vector(VBL_VECTOR, orig_vector_vbl);
    install_vector(IKBD_VECTOR, orig_vector_ikbd);

}

/* code from lab 8*/
Vector install_vector(int num, Vector vector){
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;

    Super(old_ssp);
    return orig;
}


void clear_key_buffer() {
    /* Clears the key buffer */
    key_buffer_start = key_buffer_end;
}


void do_IKBD_ISR() {
    signed char data_byte;
    int next;

    /* Check if data is available in the ACIA data register */
    if (ACIA_STATUS_REGISTER & ACIA_STATUS_RX_FULL) {
        /* Read a byte from the ACIA data register */
        data_byte = ACIA_DATA_REGISTER;
        if (mouse_packet_state == 0) {
            /* First byte of mouse packet (header) */
            mouse_button_state = data_byte;
            mouse_packet_state = 1;
        } else if (mouse_packet_state == 1) {
            /* Second byte of mouse packet (X movement) */
            mouse_dx_accumulator += (signed char)data_byte;
            mouse_packet_state = 2;
        } else if (mouse_packet_state == 2) {
            /* Third byte of mouse packet (Y movement) */
            mouse_dy_accumulator += (signed char)data_byte;
            mouse_packet_state = 0;
            
            /* Update global mouse_dx and mouse_dy */
            mouse_dx = mouse_dx_accumulator;
            mouse_dy = mouse_dy_accumulator;

            /* Reset accumulators for next packet */
            mouse_dx_accumulator = 0;
            mouse_dy_accumulator = 0;
        }
        /* Calculate next position in the buffer */
        next = (key_buffer_end + 1) % KEY_BUFFER_SIZE;
        /* If the buffer is full, move the start to make room */
        if (next == key_buffer_start) {
            key_buffer_start = (key_buffer_start + 1) % KEY_BUFFER_SIZE;
        }

        /* Store the new key and update the buffer end pointer */
        key_buffer[key_buffer_end] = scancode_to_char(data_byte);
        key_buffer_end = next;
    }

    MFP_IN_SERVICE_B_REGISTER &= ~0x40;
}


void get_keys_pressed(char *keys, int maxKeys) {
    int i;
    int index;
    int count = 0;

    /* Check each key in the buffer */
    for (i = key_buffer_start; i != key_buffer_end; i = (i + 1) % KEY_BUFFER_SIZE) {
        index = (i + KEY_BUFFER_SIZE - 1) % KEY_BUFFER_SIZE; /* Adjust index to get current key */
        keys[count] = key_buffer[index];
        count++;

        /* Break if the maximum number of keys is reached */
        if (count >= maxKeys) {
            break;
        }
    }

    /* Fill remaining space in the keys array with '\0' */
    for (i = count; i < maxKeys; i++) {
        keys[i] = '\0';
    }
}

int is_key_pressed(char checkKey) {
    int lastKeyIndex;

    /* Calculate the index of the last key pressed */
    lastKeyIndex = key_buffer_end - 1;
    if (lastKeyIndex < 0) {
        lastKeyIndex += KEY_BUFFER_SIZE;
    }

    /* Check if the last key in the buffer matches checkKey */
    if (key_buffer[lastKeyIndex] == checkKey) {
        /* If the key matches checkKey, it was the last key pressed */
        return true; /* Return 1 to indicate the key was pressed */
    }

    /* If the last key does not match, it was not pressed */
    return false; /* Return 0 to indicate the key was not pressed */
}


char scancode_to_char(unsigned char scancode) {
    /* Converts scancode to character based on the Atari ST keyboard layout,
     * (Copied from course folder) */
    switch (scancode) {
        case 0x1E: return 'a';
        case 0x30: return 'b';
        case 0x2E: return 'c';
        case 0x20: return 'd';
        case 0x12: return 'e';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x17: return 'i';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x32: return 'm';
        case 0x31: return 'n';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x10: return 'q';
        case 0x13: return 'r';
        case 0x1F: return 's';
        case 0x14: return 't';
        case 0x16: return 'u';
        case 0x2F: return 'v';
        case 0x11: return 'w';
        case 0x2D: return 'x';
        case 0x15: return 'y';
        case 0x2C: return 'z';
        case 0x1E41: return 'A';
        case 0x3042: return 'B';
        case 0x2E43: return 'C';
        case 0x2044: return 'D';
        case 0x1245: return 'E';
        case 0x2146: return 'F';
        case 0x2247: return 'G';
        case 0x2348: return 'H';
        case 0x1749: return 'I';
        case 0x244A: return 'J';
        case 0x254B: return 'K';
        case 0x264C: return 'L';
        case 0x324D: return 'M';
        case 0x314E: return 'N';
        case 0x184F: return 'O';
        case 0x1950: return 'P';
        case 0x1051: return 'Q';
        case 0x1352: return 'R';
        case 0x1F53: return 'S';
        case 0x1454: return 'T';
        case 0x1655: return 'U';
        case 0x2F56: return 'V';
        case 0x1157: return 'W';
        case 0x2D58: return 'X';
        case 0x1559: return 'Y';
        case 0x2C5A: return 'Z';
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x29: return '`';
        case 0x2B: return '\\';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x27: return ';';
        case 0x28: return '\'';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';
        case 0x39: return ' ';
        case 0x1C: return '\r'; /* Return */
        case 0x0F: return '\t'; /* Tab */
        case 0x01: return '\x1b'; /* Escape */
        case 0x48: return 'w';
        case 0x50: return 's'; 
        case 0x4B: return 'a'; 
        case 0x4D: return 'd'; 
        default: return '\0'; 
    }
}
