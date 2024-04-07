/* events.c */
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "model.h"
#include "bitmap.h"
#include "effects.h"
#include "events.h"
#include "helper.h"
#include "psg.h"

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
            /* slight adjustment so it looks good */
            if(model->player.dx < 0){
                model->playerShots[i].x = model->player.x + 16;
            }else{
                model->playerShots[i].x = model->player.x;
            }
			model->playerShots[i].y = model->player.y + 6;
			model->playerShots[i].dx = model->player.dx;
			break;
		}
	}
	model->currentSoundEffect = sound_playershot;
	model->currentSoundEffectDuration = 3;
}

/* Quit the game */
void quit_game(GameModel *model) {
    /* Set game running status to false */
    model->game_running = false;
}

/** 
 * Function to move enemy ships towards the player.
 */
void move_enemies(GameModel *model) {
    int i;

    /** Iterate through each alien. */
    for(i = 0; i < ENTITY_COUNT; i++){
        if(model->aliens[i].active == true){
            /** Update x-axis movement */
            /** If the alien is to the right of the player, move left */
            if(model->aliens[i].x > model->player.x){
                model->aliens[i].dx = -1;
            } 
            /** If the alien is to the left of the player, move right */
            else if(model->aliens[i].x < model->player.x){
                model->aliens[i].dx = 1;
            } 
            /** If the alien is aligned with the player on the x-axis, don't move horizontally */
            else {
                model->aliens[i].dx = 0;
            }

            /** Update y-axis movement */
            /** If the alien is below the player, move up */
            if(model->aliens[i].y > model->player.y){
                model->aliens[i].dy = -1;
            } 
            /** If the alien is above the player, move down */
            else if(model->aliens[i].y < model->player.y){
                model->aliens[i].dy = 1;
            } 
            /** If the alien is aligned with the player on the y-axis, don't move vertically */
            else {
                model->aliens[i].dy = 0;
            }
        }
    }
}

void spaceship_damaged(GameModel *model){
    model->currentSoundEffect = sound_spaceship_damage;
    model->currentSoundEffectDuration = 3;
    model->player.lives -= 1;  /* Player loses a life */
    /* Deactivate all other shots */
    deactivate_all_shots(model);

}

void generate_alien_shot(GameModel *model) {
    int chance = rand() % 10; /* Generate a random number between 0 and 9 */
    int i, alienIndex;
    int foundActiveAlien = false;
    int deltaX;
    if (chance == 0) { /* 1 in 10 chance */
        /* Find an active alien randomly */
        for (i = 0; i < ENTITY_COUNT; i++) {
            alienIndex = rand() % ENTITY_COUNT;
            if (model->aliens[alienIndex].active) {
                foundActiveAlien = true;
                break;
            }
        }

        /* Only proceed if an active alien is found */
        if (foundActiveAlien) {
            /* Find an inactive alien shot */
            for (i = 0; i < SHOT_COUNT; i++) {
                if (model->alienShots[i].active == false) {

                    /* Set the shot active */
                    model->alienShots[i].active = true;

                    /* Position the shot at the chosen alien's location */
                    model->alienShots[i].x = model->aliens[alienIndex].x;
                    model->alienShots[i].y = model->aliens[alienIndex].y;

                    /* Calculate the direction of the shot towards the player */
                    deltaX = model->player.x - model->aliens[alienIndex].x;

                    /* Assign a velocity to the shot in the direction of the player */
                    model->alienShots[i].dx = deltaX < 0 ? -2 : 2;

                    break;
                }
            }
        }
    }
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

/** 
 * Function to handle collision between player's shot and an alien ship.
 */
void player_shot_collides_with_alien(GameModel *model) {
    int i, j;

    /** Iterate through each player shot. */
    for (i = 0; i < SHOT_COUNT; i++) {
        if (model->playerShots[i].active) {
            /** Iterate through each alien. */
            for (j = 0; j < ENTITY_COUNT; j++) {
                if (model->aliens[j].active) {
                    /** Check for collision. Assume aliens are rectangular with certain dimensions. */
                    if (hit_detection(model->playerShots[i].x, model->playerShots[i].y, 
                                            model->aliens[j].x, model->aliens[j].y, 
                                            BITMAP_WIDTH, BITMAP_HEIGHT)) {
                        /** Collision detected. */

                        /** Deactivate the alien. */
                        model->aliens[j].active = 0;

                        /** Deactivate the player's shot. */
                        model->playerShots[i].active = 0;

                        /** Update player's score. */
                        model->player.score += 1; 

                        /** Play collision sound if not muted. */
                        model->currentSoundEffect = sound_explosion;
                        model->currentSoundEffectDuration = 2;

                        /* spawn new alien */
                        generate_alien(model);

                    }
                }
            }
        }
    }
}


/** 
 * Function to handle player's shot going out of the screen.
 */
void player_shot_out_of_screen(GameModel *model) {
    int i;

    /** Iterate through each player's shot. */
    for (i = 0; i < SHOT_COUNT; i++) {
        if (model->playerShots[i].active) {
            /** Check if the shot is out of the screen's bounds. */
            if (model->playerShots[i].x >= SCREEN_WIDTH ||
                model->playerShots[i].y >= SCREEN_HEIGHT ||
                model->playerShots[i].x < 0 ||
                model->playerShots[i].y < 0) {
                /** Deactivate the shot if it is out of bounds. */
                model->playerShots[i].active = false;
            }
        }
    }
}


/* Handle collision between alien's shot and player's ship */
void alien_shot_collides_with_player(GameModel *model) {
    int i;

    for (i = 0; i < SHOT_COUNT; i++) {
        if (model->alienShots[i].active) {
            /* Assuming AlienShot and Player have width and height */
            if (hit_detection(model->alienShots[i].x, model->alienShots[i].y, 
                              model->player.x, model->player.y, 
                              BITMAP_WIDTH, BITMAP_HEIGHT)) {
                /* Collision detected, handle it */
                model->alienShots[i].active = false;  /* Deactivate this alien shot */
                spaceship_damaged(model);

                break;  /* Collision handled, no need to check further */
            }
        }
    }
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
    int i;

    for (i = 0; i < ENTITY_COUNT; i++) {
        if (model->aliens[i].active) {
            /* Assuming Alien has width and height same as player's ship */
            if (hit_detection(model->player.x, model->player.y, 
                              model->aliens[i].x, model->aliens[i].y, 
                              BITMAP_WIDTH, BITMAP_HEIGHT)) {
                /* Collision detected */
                model->aliens[i].active = false;  /* Deactivate the collided alien */
                spaceship_damaged(model);
                break;  /* Collision handled, no need to check further */
            }
        }
    }
}

void toggle_mute(GameModel *model) {
	model->isMuted = !model->isMuted;
    if(model->isMuted){
        stop_sound();
    }
}
