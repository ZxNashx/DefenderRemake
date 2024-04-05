#include <stdio.h>
#include <osbind.h> 
#include "model.h"
#include "renderer.h"
#include "events.h"
#include "defs.h"
#include "raster.h"
#include "input.h"
#include "raster.h"
#include "bitmap.h"
#include "defs.h"
/* Global game model */
GameModel model;

/* buffer size is 32k */
char rawBackBuffer[BUFFER_SIZE + 256];
char *backBuffer;
char *frontBuffer;

/* Function to get the current time from the system clock */
uint32_t get_time() {
    uint32_t *pointerToTimer = (volatile uint32_t *)0x462;
    uint32_t timenow;
    uint32_t old_ssp;

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

int main() {

    uint32_t timeThen, timeNow, timeElapsed;
    char *temp;
    unsigned long *orig_buffer = Physbase();
    /*backBuffer = (char *)((uint32_t)(rawBackBuffer + 255) & 255);*/
    short isFront = true;


    backBuffer = rawBackBuffer;
    while(( ((uint32_t)backBuffer)& 255) != 0){
        backBuffer++;
    }

    /*backBuffer = (char *)  (rawBackBuffer + (256 -  (((uint32_t)rawBackBuffer)) & 255))));*/
    frontBuffer = Physbase(); 

    Setscreen(-1, backBuffer, -1);

    initModel(&model);
    timeThen = get_time(); 



    while (model.game_running == true) {
        timeNow = get_time();
        timeElapsed = timeNow - timeThen; 

        if (timeElapsed >= 1) {
            if (input_available()) {
                char inputChar = read_input();
                handle_input(&model, inputChar);
            }

            updateModel(&model);

            if(isFront == true){
                clear_black(frontBuffer);
                isFront = false;
                render(&model, frontBuffer);
                Setscreen(-1, frontBuffer, -1);
            }else{
                clear_black(backBuffer);
                isFront = true;
                render(&model, backBuffer);
                Setscreen(-1, backBuffer, -1);
            }


            Vsync();

            timeThen = timeNow;
        }
    }

    
    Setscreen(-1, orig_buffer, -1);

    return 0;
}
