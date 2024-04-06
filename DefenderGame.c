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
#include "psg.h"
#include "effects.h"

/* buffer size is 32k */
char rawBackBuffer[BUFFER_SIZE + 256];
char *backBuffer;
char *frontBuffer;
char *orig_buffer;

void swapBuffers(char **frontBuffer, char **backBuffer) {
    char *temp = *frontBuffer;
    *frontBuffer = *backBuffer;
    *backBuffer = temp;
}


int main() {
    GameModel model;

    /* Declaration of variables */
    uint32_t timeThen, timeNow, timeElapsed, lastMusicUpdate;
    int currentNoteA = 0, currentNoteB = 0;
    uint32_t lastNoteTimeA = 0, lastNoteTimeB = 0;
    int numNotesA = NUM_NOTES_IN_SONG_A;
    int numNotesB = NUM_NOTES_IN_SONG_B;
    int elapsedA;
    int elapsedB;
    unsigned short soundEffectPlayTime = 0;
    int i;



    /* Buffer alignment */
    backBuffer = rawBackBuffer;
    while(( ((uint32_t)backBuffer) & 255) != 0){
        backBuffer++;
    }

    orig_buffer = Physbase();
    frontBuffer = Physbase(); 
    Setscreen(-1, backBuffer, -1);

    /* Game initialization */
    initModel(&model);

    start_music(0, song_A, &currentNoteA, &lastNoteTimeA);
    start_music(1, song_B, &currentNoteB, &lastNoteTimeB);
    lastMusicUpdate = get_time(); 


    model.currentSoundEffect = no_sound_effect;

    /* Game loop initialization */
    timeThen = get_time(); 
    stop_sound();

    /* Main game loop */
    do{
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

            /* sound play update */
            if(model.currentSoundEffect != no_sound_effect && 
               soundEffectPlayTime < model.currentSoundEffectDuration &&
               !model.isMuted) {
                if(soundEffectPlayTime == 0){
                    model.currentSoundEffect();
                }
                soundEffectPlayTime++; /* time increment, e.g., time since last frame */
            } else {
                soundEffectPlayTime = 0;
                model.currentSoundEffect = no_sound_effect;
                model.currentSoundEffect();
            }

            clear_black(backBuffer);
            render(&model, backBuffer);
            Setscreen(-1, backBuffer, -1);
            swapBuffers(&frontBuffer, &backBuffer);
            timeThen = timeNow;
            Vsync();

        }

        if (timeNow - lastMusicUpdate >= MUSIC_UPDATE_INTERVAL && !model.isMuted) {
            update_music(0, song_A, &currentNoteA, &lastNoteTimeA, timeNow, numNotesA); 
            update_music(1, song_B, &currentNoteB, &lastNoteTimeB, timeNow, numNotesB); 

            lastMusicUpdate = timeNow;
        }
    }while (model.game_running == true);

    /* Cleanup and exit */
    stop_sound();
    Setscreen(-1, orig_buffer, -1);
    return 0;
}
