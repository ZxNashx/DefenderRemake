#include <stdio.h>
#include <stdlib.h>
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
#include "text.h"

#include "splash.h"

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

int run_game() {

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
    unsigned short startingEnemyCount = 3;
    int i;

    /* Buffer alignment */
    backBuffer = rawBackBuffer;
    while(( ((uint32_t)backBuffer) & 255) != 0){
        backBuffer++;
    }

    frontBuffer = get_video_base(); 
    set_video_base(backBuffer);

    /* Game initialization */
    initModel(&model);

    start_music(0, song_A, &currentNoteA, &lastNoteTimeA);
    start_music(1, song_B, &currentNoteB, &lastNoteTimeB);
    lastMusicUpdate = get_time(); 


    model.currentSoundEffect = no_sound_effect;

    /* Game loop initialization */
    timeThen = get_time(); 
    stop_sound();


    for(i = 0; i < startingEnemyCount; i++){
        generate_alien(&model);
    }

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

            if(model.player.lives <= 0){
                model.game_running = false;
                /**/
                model.currentSoundEffect = sound_game_over;
                model.currentSoundEffectDuration = 10;

            }

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

            plot_number(backBuffer, model.player.map_x_position, 10, 10, 1);

            set_video_base(backBuffer);
            swapBuffers(&frontBuffer, &backBuffer);
            timeThen = timeNow;
            Vsync();

        }

        if (timeNow - lastMusicUpdate >= MUSIC_UPDATE_INTERVAL && !model.isMuted) {
            update_music(0, song_A, &currentNoteA, &lastNoteTimeA, timeNow, numNotesA); 
            update_music(1, song_B, &currentNoteB, &lastNoteTimeB, timeNow, numNotesB); 
            lastMusicUpdate = timeNow;
        }
    }while (model.game_running == true || !(model.currentSoundEffect = no_sound_effect));

    /* Cleanup and exit */
    stop_sound();

    return model.player.score;
}

int main(){
    int running = true;
    int splash_screen_result;
    int game_score = 0;
    int high_score = 0;
    orig_buffer = get_video_base();
    srand(get_time());

    while(running){

        /* set the new highscore */
        if(game_score > high_score){
            high_score = game_score;
        }
        splash_screen_result = create_splash_screen(game_score, high_score);
        /* check splashscreen result*/
        if(splash_screen_result == 1){
            /* singleplayer */
            running = true;
            game_score = run_game();
        }else if(splash_screen_result == 2){
            /* coop */
            running = true;
            game_score = run_game();
        }else{
            /* exit */
            running = false;
        }
    }

    set_video_base(orig_buffer);
    return 0;
}