#ifndef HELPER_H
#define HELPER_H

#include "defs.h"
#include "model.h"

/*
Function: get_time
Returns:
    uint32_t: The current time in a specific time unit (e.g., milliseconds).
Description:
    Retrieves the current time, typically used for timing events or animations in the game. The time is returned in a standardized unit such as milliseconds.
*/
uint32_t get_time();

/*
Function: hit_detection
Arguments:
    int point_x, point_y: Coordinates of the point to check for collision.
    int box_x, box_y: Top-left coordinates of the rectangular box.
    int box_width, box_height: Width and height of the rectangular box.
Returns:
    int: 1 if the point is within the box (hit detected), 0 otherwise.
Description:
    Checks if a specified point lies within a given rectangular area. This is typically used for collision detection, determining if a game object (represented by the point) has collided with another object (represented by the box).
*/
int hit_detection(int point_x, int point_y, 
                        int box_x, int box_y, 
                        int box_width, int box_height);

/*
Function: deactivate_all_shots
Arguments:
    GameModel *model: Pointer to the GameModel structure representing the current state of the game.
Description:
    Deactivates or clears all shots (projectiles) currently active in the game model. This might be used when resetting the game state or transitioning between levels.
*/
void deactivate_all_shots(GameModel *model);

#endif /* HELPER_H */
