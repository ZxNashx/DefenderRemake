#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"

/*
Function: clear_region
Arguments:
    char *base: The start of the video memory.
    int x, y: Coordinates where the clearing starts.
    int width, height: Width and height of the region to clear.
Description:
    Clears a specific region on the screen.
*/
void clear_region(char *base, int x, int y, int width, int height);

/*
Function: renderPlayer
Arguments:
    Player *player: Pointer to the player structure.
    char *base: The start of the video memory.
Description:
    Renders the player's spaceship on the screen.
*/
void renderPlayer(Player *player, char *base);

/*
Function: renderAlien
Arguments:
    Alien *alien: Pointer to the alien structure.
    char *base: The start of the video memory.
Description:
    Renders an alien's spaceship on the screen.
*/
void renderAlien(Alien *alien, char *base);

/*
Function: render
Arguments:
    GameModel *model: Pointer to the game model.
    char *base: The start of the video memory.
Description:
    Renders the entire game model including players, aliens, and other elements.
*/
void render(GameModel *model, char *base);

#endif /* RENDERER_H */
