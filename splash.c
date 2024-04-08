#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>

#include "defs.h"
#include "raster.h"
#include "font.h"
#include "text.h"
#include "input.h"

#include "music.h"
#include "helper.h"
#include "psg.h"

#include "isr.h"
#include "splash.h"

int create_splash_screen(int score, int high_score) {
    int next;
    unsigned char key_scancode;
    const char *title;
    const char *subtitle;
    const char *player1;
    const char *player2;
    const char *quit;
    int titleLength, subtitleLength, player1Length, quitLength;
    int titleStartX, titleStartY, subtitleStartX, subtitleStartY;
    int player1X, player2X, quitX, buttonY, selection, input;
    int score_displayX, score_displayY, score_offset, score_dist;
    int randomNumber;

    start_music(0, menu_song_A, &currentNoteIndex_MenuA, &lastNoteTime_MenuA);
    start_music(1, menu_song_B, &currentNoteIndex_MenuB, &lastNoteTime_MenuB);

    /* Initialize variables */
    
    randomNumber = rand() % 10 + 1;
    title = "Defender";
    titleLength = 8;  
    titleStartX = (SCREEN_WIDTH - (titleLength * FONT_WIDTH * 2)) / 2;  
    titleStartY = SCREEN_HEIGHT / 4;

    if(high_score == 0 && randomNumber >= 5){
        subtitle = "Try to survive...";
        subtitleLength = 17; 
    }else if(high_score == 0){
        subtitle = "Current Objective: Survive";
        subtitleLength = 26;
    }else{
        subtitle = "Better luck next time...";
        subtitleLength = 24; 
    }

    if(high_score == score && score != 0){
        subtitle = "New High Score!";
        subtitleLength = 15; 
    }

    subtitleStartX = (SCREEN_WIDTH - (subtitleLength * FONT_WIDTH)) / 2;
    subtitleStartY = titleStartY + FONT_HEIGHT * 2 + 10;  
    buttonY = subtitleStartY + FONT_HEIGHT + 20; 

    /* Create Player 1 Button */
    player1 = "Player 1";
    player1Length = 8;
    player1X = (SCREEN_WIDTH - (player1Length * FONT_WIDTH + 20)) / 3;  
        /* Create Player 2 Button */
    player2 = "Player 2";
    player2X = 2 * (SCREEN_WIDTH - (player1Length * FONT_WIDTH + 20)) / 3; 

    /* Create Quit Button */
    quit = "Quit";
    quitLength = 4;
    quitX = (player1X + player2X) / 2;  

    /* show game score */
    score_displayX = 10;
    score_displayY = 10;
    score_offset = 120;
    score_dist = 16;

    clear_black(frontBuffer);
    clear_black(backBuffer);
    set_video_base(backBuffer);
    plot_string(frontBuffer, title, titleStartX, titleStartY, 2);
    plot_string(frontBuffer, subtitle, subtitleStartX, subtitleStartY, 1);
    create_button(frontBuffer, player1X, buttonY, player1);
    create_button(frontBuffer, player2X, buttonY, player2);
    create_button(frontBuffer, quitX, buttonY + 50, quit);
    plot_string(frontBuffer, "High Score: ", score_displayX, score_displayY, 1);
    plot_number(frontBuffer, high_score, score_displayX + score_offset, score_displayY, 1);
    plot_string(frontBuffer, "Current Score: ", score_displayX, score_displayY + score_dist, 1);
    plot_number(frontBuffer, score, score_displayX + score_offset, score_displayY + score_dist, 1);
    plot_string(frontBuffer, "By Axyl Carefoot-Schulz", 450, 300, 1);

    selection = 0;
    while (selection == 0) {
        if (render_request) {
            render_request = false;

            clear_black(backBuffer); /* add mouse clicking button*/
            plot_mouse(backBuffer);
            plot_string(backBuffer, title, titleStartX, titleStartY, 2);
            plot_string(backBuffer, subtitle, subtitleStartX, subtitleStartY, 1);
            create_button(backBuffer, player1X, buttonY, player1);
            create_button(backBuffer, player2X, buttonY, player2);
            create_button(backBuffer, quitX, buttonY + 50, quit);
            plot_string(backBuffer, "High Score: ", score_displayX, score_displayY, 1);
            plot_number(backBuffer, high_score, score_displayX + score_offset, score_displayY, 1);
            plot_string(backBuffer, "Current Score: ", score_displayX, score_displayY + score_dist, 1);
            plot_number(backBuffer, score, score_displayX + score_offset, score_displayY + score_dist, 1);
            plot_string(backBuffer, "By Axyl Carefoot-Schulz", 450, 300, 1);
            set_video_base(backBuffer);
            swapBuffers(&frontBuffer, &backBuffer);
        }

        selection = main_menu_input();
        /* Update Menu Music */
        if (menuMusicActive && music_update_request) {
            music_update_request = false;
            update_music(0, menu_song_A, &currentNoteIndex_MenuA, &lastNoteTime_MenuA, MENU_A_NOTECOUNT);
            /* Update for menu_song_B if required */
            update_music(1, menu_song_B, &currentNoteIndex_MenuB, &lastNoteTime_MenuB, MENU_B_NOTECOUNT);
        }
    }
    return selection;
}
