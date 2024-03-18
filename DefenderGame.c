#include <stdio.h>
#include <osbind.h> // For TOS system calls
#include "model.h"
#include "renderer.h"
#include "events.h"
#include "defs.h"
#include "raster.h"

/* Global game model */
GameModel model;

char backBuffer[BUFFER_SIZE] __attribute__((aligned(256))); 
char *frontBuffer;

/* Function to get the current time from the system clock */
unsigned long get_time() {
    long *timer = (long *)0x462;
    long old_ssp = Super(0);
    unsigned long timeNow = *timer;
    Super(old_ssp);
    return timeNow;
}

/* Function to wait for vertical blank */
void wait_for_vertical_blank() {
    static unsigned long last_vblank = 0;
    while (*((volatile unsigned long *)0x462) == last_vblank);
    last_vblank = *((volatile unsigned long *)0x462);
}

int main() {
    frontBuffer = Physbase(); 
    initModel(&model); 
    model.game_running = true; 

    unsigned long lastTime = get_time();

    while (model.game_running) {
        unsigned long currentTime = get_time();
        if (currentTime != lastTime) {
            lastTime = currentTime;

            updateModel(&model);
            move_enemies(&model);
            move_player_shot(&model);
            move_aliens_shot(&model);
            player_shot_collides_with_alien(&model);

            render(&model, backBuffer);

            Setscreen(backBuffer, -1, -1);
            char *temp = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = temp;

            wait_for_vertical_blank();
        }
    }

    Setscreen(frontBuffer, -1, -1);

    return 0;
}
