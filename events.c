/* events.c */
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "model.h"
#include "bitmap.h"
#include "events.h"
void move_left(GameModel *model) {
    unsigned int tempBitmap[8];
    int i;

    /* Check if current dx is not already moving left (negative speed) */
    if (model->player.dx >= 0) {
        mirrorBitmap(spaceship_bitmap, tempBitmap, 8);
        for (i = 0; i < 8; i++) {
            spaceship_bitmap[i] = tempBitmap[i];
        }
    }

    /* Set dx to move left */
    model->player.dx = -model->player.speed;
    if (model->player.x < 0) {
        model->player.x = 0;
    }
}

/*
all dx/dy could be + or -, so they are
just added to the position
*/

void move_right(GameModel *model) {
    unsigned int tempBitmap[8];
    int i;

    /* Check if current dx is not already moving right (positive speed) */
    if (model->player.dx <= 0) {
        mirrorBitmap(spaceship_bitmap, tempBitmap, 8);
        for (i = 0; i < 8; i++) {
            spaceship_bitmap[i] = tempBitmap[i];
        }
    }

    /* Set dx to move right */
    model->player.dx = model->player.speed;
    if (model->player.x > SCREEN_WIDTH - BITMAP_WIDTH) {
        model->player.x = SCREEN_WIDTH - BITMAP_WIDTH;
    }
}

void freeze_player(GameModel *model){
	model->player.dy = 0;
}

/* Move player's ship downwards */
void move_down(GameModel *model) {
    /* Increase player's y-coordinate */
    model->player.dy = model->player.speed;
    /* Ensure the player doesn't move off-screen */
    if (model->player.y > SCREEN_HEIGHT) {
        model->player.y = SCREEN_HEIGHT;
    }
}

/* Move player's ship upwards */
void move_up(GameModel *model) {
    /* Decrease player's y-coordinate */
    model->player.dy = -model->player.speed;
    /* Ensure the player doesn't move off-screen */
    if (model->player.y < 0) {
        model->player.y = 0;
    }
}



/* Player shoots a projectile */
void shoot(GameModel *model) {
    /* Code to create and launch a bullet from the player's current position */
	int i;
	for(i = 0; i < SHOT_COUNT; i++){
		if(model->playerShots[i].active == false){
			/* unused playershot was found */
			model->playerShots[i].active = true;
			model->playerShots[i].x = model->player.x;
			model->playerShots[i].y = model->player.y;
			model->playerShots[i].dx = model->player.dx;
			break;
		}
	}
}

/* Quit the game */
void quit_game(GameModel *model) {
    /* Set game running status to false */
    model->game_running = false;
}

/* Move enemy ships */
void move_enemies(GameModel *model) {
    /* Iterate through each enemy and update their positions */

	int i;
	for(i = 0; i < ENTITY_COUNT; i++){
		if(model->aliens[i].active == true){

			/* check x-axis */
			if(model->aliens[i].x > model->player.x){
				model->aliens[i].dx = -1;				
			}else{
				model->aliens[i].dx = 1;
			}

			/* check y-axis */
			if(model->aliens[i].y > model->player.y){
				model->aliens[i].dy = -1;				
			}else{
				model->aliens[i].dy = 1;
			}
			model->aliens[i].x += model->aliens[i].dx;
			model->aliens[i].y += model->aliens[i].dy;
		}
	}

}

/* Move player's projectiles */
void move_player_shot(GameModel *model) {
    /* Iterate through player's shots and update their positions */
}

/* Move enemy's projectiles */
void move_aliens_shot(GameModel *model) {
    /* Iterate through alien shots and update their positions */
}

/* Generate a shot from an enemy */
void generate_alien_shot(GameModel *model) {
    /* Code to generate a new shot from an alien */
}

/* Generate a new enemy ship */
void generate_alien(GameModel *model) {
    /* Code to generate a new alien ship */
	int rand_x = rand() % 10;
	int rand_y = rand() % SCREEN_HEIGHT;
	int i;


	/*Subject to change*
	place alien either on left or right
	hand side of the screen
	*/
	if(rand_x > 5){
		/* left hand side */
		rand_x = -rand_x;
	}else{
		/* right hand side */
		rand_x = rand_x + SCREEN_WIDTH;
	}


	for(i = 0; i < 32; i++){
		if(model->aliens[i].active == false){
			model->aliens[i].active = true;
			model->aliens[i].x = rand_x;
			model->aliens[i].y = rand_y;
			break;
		}
	}

}

/* Handle collision between player's shot and an alien ship */
void player_shot_collides_with_alien(GameModel *model) {
    /* Check for collisions and handle accordingly */
}

/* Handle player's shot going out of the screen */
void player_shot_out_of_screen(GameModel *model) {
    /* Check if any shots are out of the screen and handle them */
}

/* Handle collision between alien's shot and player's ship */
void alien_shot_collides_with_player(GameModel *model) {
    /* Check for collisions and handle accordingly */
}

/* Handle alien's shot going out of the screen */
void alien_shot_out_of_screen(GameModel *model) {
    /* Check if any alien shots are out of the screen and handle them */
	int i;
    for(i = 0; i < SHOT_COUNT; i++){
    	if(model->alienShots[i].active == true && (
    		model->alienShots[i].x > SCREEN_WIDTH ||
    		model->alienShots[i].x < 0 ||
    		model->alienShots[i].y > SCREEN_HEIGHT ||
    		model->alienShots[i].y < 0)){
    		model->alienShots[i].active = false;
    	}
    }
}

/* Handle the player running out of lives */
int player_runs_out_of_lives(GameModel *model) {
    /* Check player's lives and handle game over logic */
    if(model->player.lives <= 0){
    	return true;
    }else{
    	return false;
    }
}

/* Handle collision between player's ship and an alien ship */
void player_collides_with_alien(GameModel *model) {
    /* Check for collisions and handle accordingly */
}



