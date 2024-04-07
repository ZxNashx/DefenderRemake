    
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
    model->isMuted = true;
    model->time_alive = 0;

    /* default x direction*/
    model->player.speed = 4;
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
    if (model->time_alive % 700 == 0) {
        generate_alien(model);
    }

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

}

void movePlayer(GameModel *model) {
    /* Player will only move vertically */
    model->player.y += model->player.dy;
}

void moveAlien(GameModel *model, int alienIndex) {
    Alien *alien = &model->aliens[alienIndex];
    alien->x += alien->dx - (model->player.dx);
    alien->y += alien->dy;
}

void moveAlienShot(GameModel *model, int shotIndex) {
    AlienShot *as = &model->alienShots[shotIndex];
    as->x += as->dx  - (model->player.dx);
}

void movePlayerShot(GameModel *model, int shotIndex) {
    PlayerShot *ps = &model->playerShots[shotIndex];
    ps->x += 2*ps->dx  + (model->player.dx);
}
