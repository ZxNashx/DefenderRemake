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
    unsigned short soundEffectPlayTime = 0;
    unsigned short startingEnemyCount = 3;

    int i;
    initModel(&model);
    frontBuffer = get_video_base();
    clear_black(frontBuffer);
    clear_black(backBuffer); 
    set_video_base(backBuffer);
    /* Game initialization */

    model.currentSoundEffect = no_sound_effect;

    for(i = 0; i < startingEnemyCount; i++){
        generate_alien(&model);
    }

    copyBitmap(spaceship_bitmap_alive, spaceship_bitmap, 8);

    /* Main game loop */
    do {
        handle_input(&model);
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

int main(){
    int running = true;
    int splash_screen_result;
    int game_score = 0;
    int high_score = 0;
    isMuted = false;

    /* isr setup */
    init_isr();

    orig_buffer = get_video_base();
    srand(0);



    /* Buffer alignment */
    backBuffer = rawBackBuffer;
    while(( ((uint32_t)backBuffer) & 255) != 0){
        backBuffer++;
    }

    while(running){
        stop_sound();
        /* set the new highscore */
        if(game_score > high_score){
            high_score = game_score;
        }
        gameMusicActive = false;
        menuMusicActive = true;
        splash_screen_result = create_splash_screen(game_score, high_score);
        menuMusicActive = false;
        gameMusicActive = true;
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
    stop_sound();
    clean_isr();
    return 0;
}