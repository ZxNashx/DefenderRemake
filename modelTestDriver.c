#include <stdio.h>

#include "model.h"
#include "events.h"
#include "defs.h"


/*
provided option to just print the player if nothing was changed to overall model
*/

void print_player(GameModel *model){
    printf("Player:\nx=%d\ny=%d\nlives=%d\nscore=%d\ndx=%d\ndy=%d\n",
           model->player.x, model->player.y, model->player.lives, model->player.score,
           model->player.dx, model->player.dy);
}

/*
print_model will print all the data
in the current game model. 
*/

void print_model(GameModel *model){
    int i;
    printf("Model Snapshot\n");
    print_player(model);
    printf("Aliens:\n");
    for (i = 0; i < ENTITY_COUNT; i++) {
        if(model->aliens[i].active)
            printf("Alien %d: x=%d, y=%d, active=%d, dx=%d, dy=%d\n", i, 
                   model->aliens[i].x, model->aliens[i].y, model->aliens[i].active,
                   model->aliens[i].dx, model->aliens[i].dy);
    }

    printf("Player Shots:\n");
    for (i = 0; i < SHOT_COUNT; i++) {
        if(model->playerShots[i].active)
            printf("Player Shot %d: x=%d, y=%d, active=%d, dx=%d\n", i,
                   model->playerShots[i].x, model->playerShots[i].y, model->playerShots[i].active,
                   model->playerShots[i].dx);
    }

    printf("Alien Shots:\n");
    for (i = 0; i < SHOT_COUNT; i++) {
        if(model->alienShots[i].active)
            printf("Alien Shot %d: x=%d, y=%d, active=%d, dx=%d, dy=%d\n", i,
                   model->alienShots[i].x, model->alienShots[i].y, model->alienShots[i].active,
                   model->alienShots[i].dx, model->alienShots[i].dy);
    }
}

int main(){
    GameModel model;
    initModel(&model);


    /* center player */
    model.player.x = SCREEN_WIDTH / 2;
    model.player.y = SCREEN_HEIGHT / 2;
    model.player.dx = 5;
    model.player.dy = -5;

    print_model(&model);

    printf("\nTesting player movement\n");

    /* move player using all the prototype movement functions */

    move_left(&model);
    print_player(&model);
    move_right(&model);
    print_player(&model);
    move_up(&model);
    print_player(&model);
    move_down(&model);
    print_player(&model);

    printf("\nTesting player shooting\n");
    shoot(&model);
    print_model(&model);

    printf("\nTesting enemy movements and interactions\n(before)\n");
    
    /* generate 3 aliens for testing */
    generate_alien(&model);
    generate_alien(&model);
    generate_alien(&model);
    print_model(&model);
    printf("\nTesting enemy movements and interactions\n(after)\n");
    move_enemies(&model);
    move_player_shot(&model);
    move_aliens_shot(&model);
    generate_alien_shot(&model);
    print_model(&model);



    /* incomplete */

    printf("\nTesting collision scenarios\n");
    player_shot_collides_with_alien(&model);
    alien_shot_collides_with_player(&model);
    player_collides_with_alien(&model);
    print_model(&model);

    printf("\nTesting game end conditions\n");
    player_runs_out_of_lives(&model);
    print_model(&model);

    return 0;
}
