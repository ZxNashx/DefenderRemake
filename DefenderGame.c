#include <stdio.h>
#include <osbind.h> // For TOS system calls
#include "model.h"
#include "renderer.h"
#include "events.h"
#include "defs.h"
#include "raster.h"

/* Global game model */
GameModel model;

char backBuffer[BUFFER_SIZE] __attribute__((aligned(256))); // Ensure 256-byte alignment
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
    frontBuffer = Physbase(); // Original frame buffer
    initModel(&model); // Initialize the game model
    model.game_running = true; // Set game running flag

    unsigned long lastTime = get_time();

    while (model.game_running) {
        // Poll for keyboard input (to be implemented)
        // e.g., if (key_pressed()) { handle_key_input(&model); }

        unsigned long currentTime = get_time();
        if (currentTime != lastTime) {
            lastTime = currentTime;

            updateModel(&model);
            move_enemies(&model);
            move_player_shot(&model);
            move_aliens_shot(&model);
            player_shot_collides_with_alien(&model);
            // ... additional event handling ...

            // Render to back buffer
            render(&model, backBuffer);

            // Flip buffers
            Setscreen(backBuffer, -1, -1);
            char *temp = frontBuffer;
            frontBuffer = backBuffer;
            backBuffer = temp;

            // Wait for the next vertical blank to start rendering
            wait_for_vertical_blank();
        }
    }

    // Restore original frame buffer on exit
    Setscreen(frontBuffer, -1, -1);

    return 0;
}
