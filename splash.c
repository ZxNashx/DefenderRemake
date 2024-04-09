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

/* cannot be defined locally */
char title_screen[BUFFER_SIZE];


int create_splash_screen(int score, int high_score, int player_2_score) {
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
    int randomNumber, adjustedValue;
    int mouse_drawn = true;

    /* make sure to start menu music*/

    start_music(0, menu_song_A, &currentNoteIndex_MenuA, &lastNoteTime_MenuA);
    start_music(1, menu_song_B, &currentNoteIndex_MenuB, &lastNoteTime_MenuB);

    /* Initialize variables */
    
    randomNumber = rand() % 10 + 1;
    title = "Defender";
    titleLength = 8;  
    titleStartX = (SCREEN_WIDTH - (titleLength * FONT_WIDTH * 2)) / 2;  
    titleStartY = SCREEN_HEIGHT / 4;

    /* set some fun messages for the player */
    if(high_score == 0 && randomNumber >= 5){
        subtitle = "Try to survive...";
        subtitleLength = 17; 
    }else if(high_score == 0){
        subtitle = "Current Objective: Survive";
        subtitleLength = 26;
    }else{
        subtitle = "GAME OVER: Better luck next time...";
        subtitleLength = 24; 
    }

    if(high_score == score && score != 0){
        subtitle = "New High Score!";
        subtitleLength = 15; 
    }

    if(player_2_score > 0){
        if(score > player_2_score){
            subtitle = "Player 1 wins!";
            subtitleLength = 14; 
        }else if(score < player_2_score){
            subtitle = "Player 2 wins!";
            subtitleLength = 14; 
        }else{
            subtitle = "Its a tie!";
            subtitleLength = 10; 
        }
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

    /* plot stuff onto the display*/
    set_video_base(frontBuffer);
    clear_black(backBuffer);
    plot_string(backBuffer, title, titleStartX, titleStartY, 2);
    plot_string(backBuffer, subtitle, subtitleStartX, subtitleStartY, 1);
    create_button(backBuffer, player1X, buttonY, player1);
    create_button(backBuffer, player2X, buttonY, player2);
    create_button(backBuffer, quitX, buttonY + 50, quit);
    plot_string(backBuffer, "High Score: ", score_displayX, score_displayY, 1);
    plot_number(backBuffer, high_score, score_displayX + score_offset, score_displayY, 1);
    plot_string(backBuffer, "Current Score: ", score_displayX, score_displayY + score_dist, 1);
    plot_number(backBuffer, score, score_displayX + score_offset, score_displayY + score_dist, 1);
    plot_string(backBuffer, "By Axyl Carefoot-Schulz", 450, 340, 1);
    plot_string(backBuffer, "Controls:", 10, 280, 1);
    plot_string(backBuffer, "Game: W,A,S,D to move, SPACE to shoot, Q to quit, M to mute.", 10, 300, 1);
    plot_string(backBuffer, "Menu: A: Singleplayer, B: 2-player, C: Quit", 10, 320, 1);

    /* copy the splash screen */
    copyBuffer(backBuffer, title_screen, 0, BUFFER_SIZE);
    copyBuffer(backBuffer, frontBuffer, 0, BUFFER_SIZE);

    selection = 0;
    while (selection == 0) {
        selection = main_menu_input();
        if (render_request) {
            render_request = false;
            /* an attempt to optimize was made */
            if(mouse_drawn){
                copyBuffer(title_screen, backBuffer, 0, BUFFER_SIZE);
            }
            mouse_drawn = plot_mouse(backBuffer, title_screen);
            set_video_base(backBuffer);
            swapBuffers(&frontBuffer, &backBuffer);
        }

        /* check mouse press with mouse_button_state */
        if (mouse_button_state == 250) {
            /* Check Player 1 button */
            if (mouse_x >= player1X && mouse_x <= player1X + (player1Length * FONT_WIDTH + 20) &&
                mouse_y >= buttonY && mouse_y <= buttonY + FONT_HEIGHT) {
                selection = 1;  
            }

            /* Check Player 2 button */
            if (mouse_x >= player2X && mouse_x <= player2X + (player1Length * FONT_WIDTH + 20) &&
                mouse_y >= buttonY && mouse_y <= buttonY + FONT_HEIGHT) {
                selection = 2;  
            }

            /* Check Quit button */
            if (mouse_x >= quitX && mouse_x <= quitX + (quitLength * FONT_WIDTH + 20) &&
                mouse_y >= buttonY + 50 && mouse_y <= buttonY + 50 + FONT_HEIGHT) {
                selection = 3;  
            }
        }

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
