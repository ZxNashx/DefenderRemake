#include "input.h"
#include "model.h"
#include "defs.h"
#include "events.h"
#include "isr.c"

#include <osbind.h>
int main_menu_input() {
    if (is_key_pressed('a') || is_key_pressed('A')) {
        return 1;
    } else if (is_key_pressed('b') || is_key_pressed('B')) {
        return 2;
    } else if (is_key_pressed('c') || is_key_pressed('C')) {
        return 3;
    } else if (is_key_pressed('q') || is_key_pressed('Q')) {
        return 3; 
    } else {
        return 0; /* Default input */
    }
}


void handle_input(GameModel *model) {
    if (is_key_pressed('a') || is_key_pressed('A')) {
        /* make ship face left */
        move_left(model);
    }else if (is_key_pressed('d') || is_key_pressed('D')) {
        /* make ship face right */
        move_right(model);
    }else if (is_key_pressed('w') || is_key_pressed('W')) {
        /* move ship upwards */
        move_up(model);
    }
    else if (is_key_pressed('s') || is_key_pressed('S')) {
        /* move ship downwards */
        move_down(model);
    }
    else if (is_key_pressed(' ') || is_key_pressed('x') || is_key_pressed('X')) {
        /* Shoot in the direction facing */
        shoot(model);
    }
    else if (is_key_pressed('q') || is_key_pressed('Q')) {
        /* Quit the game */
        quit_game(model);
    }
    else if (is_key_pressed('e') || is_key_pressed('E')) {
        /* Spawn an enemy */
        generate_alien(model);
    }else{
        freeze_player(model);
    }
}

void global_input(unsigned int input){
    unsigned char highByte = (input >> 8); 
    unsigned char lowByte = input & 0xFF;

    if (lowByte == 'm' || lowByte == 'M') {
        /* mute the game or unmute the game */
        toggle_mute();
    }
}
