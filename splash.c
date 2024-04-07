#include "defs.h"
#include "raster.h"
#include "font.h"
#include "text.h"
#include "input.h"


int create_splash_screen() {
    char *videoBase; 
    const char *title;
    const char *subtitle;
    const char *player1;
    const char *player2;
    const char *quit;
    int titleLength, subtitleLength, player1Length, quitLength;
    int titleStartX, titleStartY, subtitleStartX, subtitleStartY;
    int player1X, player2X, quitX, buttonY, selection, input;

    /* Initialize variables */
    videoBase = get_video_base(); 
    title = "Defender";
    titleLength = 8;  
    titleStartX = (SCREEN_WIDTH - (titleLength * FONT_WIDTH * 2)) / 2;  
    titleStartY = SCREEN_HEIGHT / 4;

    subtitle = "Try to survive...";
    subtitleLength = 17;
    subtitleStartX = (SCREEN_WIDTH - (subtitleLength * FONT_WIDTH)) / 2;
    subtitleStartY = titleStartY + FONT_HEIGHT * 2 + 10;  
    buttonY = subtitleStartY + FONT_HEIGHT + 20;  

    /* Clear screen */
    clear_black(videoBase);

    /* Plot title and subtitle */
    plot_string(videoBase, title, titleStartX, titleStartY, 2);
    plot_string(videoBase, subtitle, subtitleStartX, subtitleStartY, 1);

    /* Create Player 1 Button */
    player1 = "Player 1";
    player1Length = 8;
    player1X = (SCREEN_WIDTH - (player1Length * FONT_WIDTH + 20)) / 3;  
    create_button(videoBase, player1X, buttonY, player1);

    /* Create Player 2 Button */
    player2 = "Player 2";
    player2X = 2 * (SCREEN_WIDTH - (player1Length * FONT_WIDTH + 20)) / 3; 
    create_button(videoBase, player2X, buttonY, player2);

    /* Create Quit Button */
    quit = "Quit";
    quitLength = 4;
    quitX = (player1X + player2X) / 2;  
    create_button(videoBase, quitX, buttonY + 50, quit);

    /* Loop indefinitely */
    /* Input handling loop */
    while (selection == 0) {
        /* Wait for and then process user input */
        input = read_input(); /* Assuming read_input() is a function that gets the input */
        selection = main_menu_input(input);

        /* React based on the input */
        switch (selection) {
            case 1:
                /* Code for Player 1 option */

            case 2:

            case 3:
                /* Code for Quit option */
                return selection;

        }
    }


    return 0;
}
