#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

/*
Function: move_left
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Moves the player's ship to the left by decreasing its x-coordinate.
    Ensures the ship doesn't move off-screen.
*/
void move_left(GameModel *model);

/*
Function: move_right
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Moves the player's ship to the right by increasing its x-coordinate.
    Ensures the ship doesn't move off-screen.
*/
void move_right(GameModel *model);

/*
Function: move_up
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Moves the player's ship upwards by decreasing its y-coordinate.
    Ensures the ship doesn't move off-screen.
*/
void move_up(GameModel *model);

/*
Function: move_down
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Moves the player's ship downwards by increasing its y-coordinate.
    Ensures the ship doesn't move off-screen.
*/
void move_down(GameModel *model);

/*
Function: shoot
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Triggers the player's ship to shoot a projectile.
    Manages the creation and launch of the bullet from the player's current position.
*/
void shoot(GameModel *model);

/*
Function: quit_game
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Sets the game's running status to false, effectively quitting the game.
*/
void quit_game(GameModel *model);

/*
Function: move_enemies
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Updates the positions of enemy ships, moving them towards the player's ship.
*/
void move_enemies(GameModel *model);

void spaceship_damaged(GameModel *model);

/*
Function: generate_alien_shot
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Generates a new shot from an alien ship.
*/
void generate_alien_shot(GameModel *model);

/*
Function: generate_alien
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Generates a new alien ship, placing it at a random position.
*/
void generate_alien(GameModel *model);

/*
Function: player_shot_collides_with_alien
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Handles the collision between the player's shot and an alien ship.
*/
void player_shot_collides_with_alien(GameModel *model);

/*
Function: player_shot_out_of_screen
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Checks if the player's shots are out of the screen and handles them appropriately.
*/
void player_shot_out_of_screen(GameModel *model);

/*
Function: alien_shot_collides_with_player
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Handles the collision between an alien's shot and the player's ship.
*/
void alien_shot_collides_with_player(GameModel *model);

/*
Function: alien_shot_out_of_screen
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Checks if the alien's shots are out of the screen and handles them appropriately.
*/
void alien_shot_out_of_screen(GameModel *model);

/*
Function: player_collides_with_alien
Arguments:
    GameModel *model: Pointer to the game model.
Description:
    Handles the collision between the player's ship and an alien ship.
*/
void player_collides_with_alien(GameModel *model);

void freeze_player(GameModel *model);
void toggle_mute();
void keep_player_in_bounds(GameModel *model);
#endif /* EVENTS_H */
