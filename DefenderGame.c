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

char rawBackBuffer[BUFFER_SIZE + 256];
char *backBuffer;
char *frontBuffer;

/* Function to get the current time from the system clock */
unsigned long get_time() {
    return *((volatile unsigned long *)0x462);
}

/* Function to wait for vertical blank */
void wait_for_vertical_blank() {
    static unsigned long last_vblank = 0;
    while (*((volatile unsigned long *)0x462) == last_vblank);
    last_vblank = *((volatile unsigned long *)0x462);
}

/* Function to handle input */
void handle_input(GameModel *model, char inputChar) {
    switch (inputChar) {
        case 'a':
            break;
        case 'd': 
            break;
    }
}

int main() {
    unsigned long lastTime = get_time();
    unsigned long currentTime;
    char *temp;

    backBuffer = (char *)((unsigned long)(rawBackBuffer + 255) & ~0xFF);
    frontBuffer = Physbase(); 

    initModel(&model); 
    model.game_running = true;

    init_input();  

    while (model.game_running) {
        currentTime = get_time();
        if (currentTime != lastTime) {
            lastTime = currentTime;

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

            Setscreen(backBuffer, -1, -1);
            temp = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = temp;

            wait_for_vertical_blank();
        }
    }

    Setscreen(frontBuffer, -1, -1);
    cleanup_input();  

    return 0;
}
