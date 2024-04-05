#include <stdio.h>
#include <osbind.h>
#include "model.h"
#include "renderer.h"
#include "events.h"
#include "defs.h"
#include "raster.h"
#include "input.h"
#include "bitmap.h"
#include "music.h"
#include "helper.h"


/* Global game model */
GameModel model;

/* buffer size is 32k */
char rawBackBuffer[BUFFER_SIZE + 256];
char *backBuffer;
char *frontBuffer;

void wait_for_vertical_blank(uint32_t last_vblank) {
    uint32_t current_time;
    do {
        current_time = get_time();
    } while (current_time == last_vblank);
}
void swapBuffers(char **frontBuffer, char **backBuffer) {
    char *temp = *frontBuffer;
    *frontBuffer = *backBuffer;
    *backBuffer = temp;
}

int main() {
    /* Declaration of variables */
    uint32_t timeThen, timeNow, timeElapsed, lastMusicUpdate;
    unsigned long *orig_buffer = Physbase();
    int currentNote = 0;       
    uint32_t lastNoteTime = 0;
    int numNotes;

    /* Song data */
    Note song[] = {
        {C4, 25}, {C4, 25}, {G4, 25}, {G4, 25}, {A4, 25}, {A4, 25}, {G4, 50},
        {F4, 25}, {F4, 25}, {E4, 25}, {E4, 25}, {D4, 25}, {D4, 25}, {C4, 50},

    };
    numNotes = sizeof(song) / sizeof(song[0]);

    /* Buffer alignment */
    backBuffer = rawBackBuffer;
    while(( ((uint32_t)backBuffer) & 255) != 0){
        backBuffer++;
    }

    frontBuffer = Physbase(); 
    Setscreen(-1, backBuffer, -1);

    /* Game initialization */
    initModel(&model);
    start_music(&currentNote, &lastNoteTime, song, numNotes);
    lastMusicUpdate = get_time();   

    /* Game loop initialization */
    timeThen = get_time(); 
    clear_black(frontBuffer);
    clear_black(backBuffer);
    
    /* Main game loop */
    while (model.game_running == true) {
        timeNow = get_time();
        timeElapsed = timeNow - timeThen; 

        /* Input handling */
        if (input_available()) {
            char inputChar = read_input();
            handle_input(&model, inputChar);
        } else {
            freeze_player(&model);
        }

        /* Game logic and rendering */
        if (timeElapsed >= 1) {
            updateModel(&model);
            clear_black(backBuffer);
            render(&model, backBuffer);
            Setscreen(-1, backBuffer, -1);
            swapBuffers(&frontBuffer, &backBuffer);
            timeThen = timeNow;
            Vsync();
        }

        /* Music update */
        if (timeNow - lastMusicUpdate >= MUSIC_UPDATE_INTERVAL) {
            update_music(&currentNote, &lastNoteTime, timeNow, song, numNotes); 
            lastMusicUpdate = timeNow;
        }
    }

    /* Cleanup and exit */
    stop_sound();
    Setscreen(-1, orig_buffer, -1);
    return 0;
}