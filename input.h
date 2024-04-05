#ifndef INPUT_H
#define INPUT_H
#include "model.h"

int input_available();

unsigned int read_input();

/*
Function: handle_input
Arguments:
    GameModel *model: Pointer to the GameModel structure representing the current state of the game.
    unsigned int input: The input from the keyboard. Consists of an ASCII value in the low byte and a scan code in the high byte.
Description:
    Processes keyboard input for controlling the game. It interprets both ASCII characters and scan codes to handle various actions like quitting the game or responding to directional inputs. Specifically, it stops the game if 'Q' or 'q' is pressed. Other controls are managed by interpreting the scan codes, especially for non-ASCII keys like arrow keys.
*/
void handle_input(GameModel *model, unsigned int input);



#endif 