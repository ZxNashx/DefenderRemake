#include "model.h"
#include "defs.h"
#include "events.h"

void initModel(GameModel *model) {
    int i;
    model->player.x = 320; 
    model->player.y = 200; 
    
    model->player.dy = 0;
    model->player.max_lives = 3;
    model->player.lives = model->player.max_lives; 
    model->player.score = 0;
    model->game_running = true;
    model->time_alive = 0;
    model->player.map_x_position = 0;

    /* default x direction*/
    model->player.speed = 5;
    model->player.dx = model->player.speed;

    /* initialize all the arrays in the game model */

    for (i = 0; i < ENTITY_COUNT; i++) {
        model->aliens[i].x = 0;
        model->aliens[i].y = 0;
        model->aliens[i].dx = 0;
        model->aliens[i].dy = 0;
        model->aliens[i].active = false;
    }
    for (i = 0; i < SHOT_COUNT; i++) {
        model->playerShots[i].x = 0;
        model->playerShots[i].y = 0;
        model->playerShots[i].active = false;
        model->playerShots[i].dx = 0;
    }
    for (i = 0; i < SHOT_COUNT; i++) {
        model->alienShots[i].x = 0;
        model->alienShots[i].y = 0;
        model->alienShots[i].active = false;
        model->alienShots[i].dx = 0;
    }
}

void updateModel(GameModel *model) {
    int i;

    model->time_alive++;
    
    movePlayer(model);

    for (i = 0; i < ENTITY_COUNT; i++) {
        if (model->aliens[i].active) {
            moveAlien(model, i);
        }
    }

    for (i = 0; i < SHOT_COUNT; i++) {
        if (model->alienShots[i].active) {
            moveAlienShot(model, i);
        }
    }

    for (i = 0; i < SHOT_COUNT; i++) {
        if (model->playerShots[i].active) {
            movePlayerShot(model, i);
        }
    }

    /* updates */
    move_enemies(model);
    player_shot_out_of_screen(model);
    player_shot_collides_with_alien(model);
    generate_alien_shot(model);
    alien_shot_collides_with_player(model);
    player_collides_with_alien(model);
    keep_player_in_bounds(model);

    /* change later*/
    if(model->player.score == 5){
        generate_alien(model);
        generate_alien(model);
        model->player.score++;
    }else if(model->player.score == 10){
        generate_alien(model);
        generate_alien(model);
        generate_alien(model);
        model->player.score++;
    }
}

void movePlayer(GameModel *model) {
    /* Update player's vertical position */
    int new_y = model->player.y + model->player.dy;
    /* Ensure the player doesn't move off-screen */
    if (new_y < BITMAP_HEIGHT) {
        new_y = BITMAP_HEIGHT;
    } else if (new_y + BITMAP_HEIGHT > SCREEN_HEIGHT - BITMAP_HEIGHT) {
        new_y = SCREEN_HEIGHT - 2 * BITMAP_HEIGHT;
    }

    /* Set the updated position */
    model->player.y = new_y;

    /* Update player's horizontal position */
    model->player.map_x_position += model->player.dx;
}


void moveAlien(GameModel *model, int alienIndex) {
    Alien *alien = &model->aliens[alienIndex];
    alien->x += alien->dx - (model->player.dx);
    alien->y += alien->dy;
}

void moveAlienShot(GameModel *model, int shotIndex) {
    AlienShot *as = &model->alienShots[shotIndex];

    as->x += as->dx - model->player.dx;
    /* some extra difficulty*/
    if (model->player.score >= 3) {
        if (as->y < model->player.y) {
            as->y += 1;
        } else if (as->y > model->player.y) {
            as->y -= 1;
        }
    }
}


void movePlayerShot(GameModel *model, int shotIndex) {
    PlayerShot *ps = &model->playerShots[shotIndex];
    ps->x += 2*ps->dx  + (model->player.dx);
}
