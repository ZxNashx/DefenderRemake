#include <stdio.h>
#include <osbind.h> 
#include "model.h"
#include "renderer.h"
#include "events.h"
#include "defs.h"
#include "raster.h"
#include "input.h"

/* Global game model */
GameModel model;

/* buffer size is 32k */
char rawBackBuffer[BUFFER_SIZE + 256];
char *backBuffer;
char *frontBuffer;

/* Function to get the current time from the system clock */
uint32_t get_time() {
    volatile long *pointerToTimer = (volatile long *)0x462;
    long timenow;
    long old_ssp;

    old_ssp = Super(0);      
    timenow = *pointerToTimer;  
    Super(old_ssp);       

    return timenow;    
}


void wait_for_vertical_blank(uint32_t last_vblank) {
    uint32_t current_time;

    do {
        current_time = get_time();
    } while (current_time == last_vblank);
}



/* Function to handle input */
void handle_input(GameModel *model, char inputChar) {

}

int main() {
    uint32_t timeThen, timeNow, timeElapsed;
    char *temp;

    backBuffer = (char *)((uint32_t)(rawBackBuffer + 255) & ~0xFF);
    frontBuffer = Physbase(); 
    Setscreen(-1, backBuffer, -1);

    initModel(&model);
    timeThen = get_time(); 

    while (model.game_running == true) {
        timeNow = get_time();
        timeElapsed = timeNow - timeThen; 

        if (timeElapsed > 0) {
            if (input_available()) {
                char inputChar = read_input();
                handle_input(&model, inputChar);
            }

            updateModel(&model);
            move_enemies(&model);
            move_player_shot(&model);
            move_aliens_shot(&model);
            player_shot_collides_with_alien(&model);

            render(&model, backBuffer);

            Setscreen(-1, backBuffer, -1);
            temp = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = temp;

            wait_for_vertical_blank(timeNow);

            timeThen = timeNow;
            break;
        }
    }
    
    Setscreen(-1, frontBuffer, -1);

    return 0;
}
