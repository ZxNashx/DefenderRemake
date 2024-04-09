#ifndef INPUT_H
#define INPUT_H
#include "model.h"


/*
Function: handle_input
Arguments:
    GameModel *model: Pointer to the GameModel structure representing the current state of the game.
    unsigned int input: The input from the keyboard. Consists of an ASCII value in the low byte and a scan code in the high byte.
Description:
    Processes keyboard input for controlling the game. It interprets both ASCII characters and scan codes to handle various actions like quitting the game or responding to directional inputs. Specifically, it stops the game if 'Q' or 'q' is pressed. Other controls are managed by interpreting the scan codes, especially for non-ASCII keys like arrow keys.
*/
void handle_input(GameModel *model);

/*
Function: main_menu_input
Returns:
    int: The result or choice made by the player in the main menu.
Description:
    Handles user input in the main menu of the game. This function captures and processes the player's keyboard inputs to navigate through menu items like starting the game, changing settings, or exiting. The return value indicates the player's choice.
*/
int main_menu_input();

/*
Function: global_input
Arguments: None.
Description:
    Processes global keyboard inputs that are applicable throughout the game or application, regardless of the current state or screen. This may include inputs like volume control, pause, or other global commands.
*/
void global_input();

#endif 