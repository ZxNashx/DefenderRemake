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
#include "events.h"

#include "splash.h"
#include "isr.h"

int run_game() {
    unsigned short soundEffectPlayTime = 0;
    unsigned short startingEnemyCount = 5;

    int i;
    initModel(&model);


    /* Game initialization */
    stop_sound();
    start_music(0, game_song_A, &currentNoteIndex_GameA, &lastNoteTime_GameA);
    start_music(1, game_song_B, &currentNoteIndex_GameB, &lastNoteTime_GameB);


    model.currentSoundEffect = no_sound_effect;

    for(i = 0; i < startingEnemyCount; i++){
        generate_alien(&model);
    }

    copyBitmap(spaceship_bitmap_alive, spaceship_bitmap, 8);

    /* Main game loop */
    do {
        handle_input(&model);
        if (gameMusicActive && music_update_request) {
            music_update_request = false;
            update_music(0, game_song_A, &currentNoteIndex_GameA, &lastNoteTime_GameA, GAME_A_NOTECOUNT);
            /* Update for menu_song_B if required */
            update_music(1, game_song_B, &currentNoteIndex_GameB, &lastNoteTime_GameB, GAME_B_NOTECOUNT);
        }

        if (render_request) {
            render_request = false;
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
               !isMuted) {
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
            set_video_base(backBuffer);
            swapBuffers(&frontBuffer, &backBuffer);
        }

    } while (model.game_running == true || !render_request);

    return model.player.score;
}



void initialize_buffers() {
    /* Buffer Alignment */
    if (backBuffer == NULL) {
        backBuffer = rawBackBuffer;
        while(((uint32_t)backBuffer & 255) != 0) {
            backBuffer++;
        }
    }

    /* Only set orig_buffer once */
    if (orig_buffer == NULL) {
        orig_buffer = get_video_base();
        frontBuffer = orig_buffer; 
    }

    /* Switching Buffers */
    if (get_video_base() != backBuffer) {
        set_video_base(backBuffer);
    } else {
        set_video_base(frontBuffer);
    }
}

int main(){
    int running = true;
    int splash_screen_result;
    int game_score = 0;
    int high_score = 0;
    isMuted = false;

    orig_buffer = NULL;
    backBuffer = NULL;

    /* isr setup */
    init_isr();
    srand(1234);
    while(running){
        mouse_x = SCREEN_WIDTH / 2;
        mouse_y = SCREEN_HEIGHT / 2;
        stop_sound();
        /* set the new highscore */
        if(game_score > high_score){
            high_score = game_score;
        }
        gameMusicActive = false;
        menuMusicActive = true;
        initialize_buffers();
        splash_screen_result = create_splash_screen(game_score, high_score);
        menuMusicActive = false;
        gameMusicActive = true;
        /* check splashscreen result*/
        if(splash_screen_result == 1){
            /* singleplayer */
            initialize_buffers();
            running = true;
            game_score = run_game();
        }else if(splash_screen_result == 2){
            initialize_buffers();
            /* coop */
            running = true;
            game_score = run_game();
        }else{
            /* exit */
            running = false;
        }
    }

    set_video_base(orig_buffer);
    stop_sound();
    clean_isr();
    return 0;
}