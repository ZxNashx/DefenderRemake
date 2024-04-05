#include "input.h"
#include "model.h"
#include "defs.h"
#include "events.h"
#include <osbind.h>

int input_available() {
    return Cconis();
}
unsigned int read_input() {
    if (input_available()) {
        return Cnecin();  
    }
    return 0;
}


void handle_input(GameModel *model, unsigned int input) {
    unsigned char highByte = (input >> 8); 
    unsigned char lowByte = input & 0xFF;

    if (lowByte == 'a' || lowByte == 'A') {
        /* make ship face left */
        move_left(model);
    }
    else if (lowByte == 'd' || lowByte == 'D') {
        /* make ship face right */
        move_right(model);
    }
    else if (lowByte == 'w' || lowByte == 'W') {
        /* move ship upwards */
        move_up(model);
    }
    else if (lowByte == 's' || lowByte == 'S') {
        /* move ship downwards */
        move_down(model);
    }
    else if (highByte == SCAN_CODE_SPACE || 
        lowByte == 'x' ||
        lowByte == 'X') {
        /* shoot in in direction facing */
        shoot(model);
    }
    else if (lowByte == 'q' || lowByte == 'Q') {
        quit_game(model);
    }
    while(read_input() != 0){
        /* flush the input buffer */
    }
}