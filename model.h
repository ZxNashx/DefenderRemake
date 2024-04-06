#ifndef MODEL_H
#define MODEL_H

#include "defs.h"

/* Define structures for various game objects */

/*
Struct: Player
Description:
    Represents the player's spaceship in the game.
Fields:
    unsigned int x, y: X and Y coordinates of the player.
    unsigned int lives: Number of lives the player has.
    unsigned int score: Player's score in the game.
    int dx: Horizontal velocity of the player.
    int dy: Vertical velocity of the player.
*/
typedef struct {
    int x, y;  
    unsigned int lives; 
    unsigned int score; 
    int dx; /* x velocity,
    used for speed of aliens

     */
    int dy; /* y velocity */
    unsigned int speed;
    int empty;
} Player;

/*
Struct: Alien
Description:
    Represents an alien spaceship in the game.
Fields:
    unsigned int x, y: X and Y coordinates of the alien.
    unsigned int active: Status flag indicating if the alien is active.
    int dx: Horizontal velocity of the alien.
    int dy: Vertical velocity of the alien.
    int empty: Padding to make struct size even.
*/
typedef struct {
    int x, y;   
    unsigned short active; 
    int dx; 
    int dy; 
    int empty; 
} Alien;

/*
Struct: PlayerShot
Description:
    Represents a shot fired by the player.
Fields:
    unsigned int x, y: X and Y coordinates of the shot.
    unsigned int active: Status flag indicating if the shot is active.
    int dx: Horizontal velocity of the shot.
*/
typedef struct {
    unsigned int x, y;
    unsigned int active;
    int dx;
} PlayerShot;

/*
Struct: AlienShot
Description:
    Represents a shot fired by an alien.
Fields:
    unsigned int x, y: X and Y coordinates of the shot.
    unsigned int active: Status flag indicating if the shot is active.
    int dx: Horizontal velocity of the shot.
    int dy: Vertical velocity of the shot.
    int empty: Padding to make struct size even.
*/
typedef struct {
    int x, y;
    unsigned short active;
    int dx;
} AlienShot;

/*
Struct: GameModel
Description:
    Represents the overall game model, including all game objects.
Fields:
    Player player: The player's spaceship.
    Alien aliens[ENTITY_COUNT]: Array of alien spaceships.
    AlienShot alienShots[SHOT_COUNT]: Array of shots fired by aliens.
    PlayerShot playerShots[SHOT_COUNT]: Array of shots fired by the player.
    int game_running: Flag indicating if the game is currently running.
    void (*currentSoundEffect)(): Pointer to function for current sound effect.
    int currentSoundEffectDuration: Duration of the current sound effect in milliseconds.
    int isMuted: Determine if you play sound/
*/
typedef struct {
    Player player;
    Alien aliens[ENTITY_COUNT];
    AlienShot alienShots[SHOT_COUNT];
    PlayerShot playerShots[SHOT_COUNT];
    int game_running;
    void (*currentSoundEffect)(); 
    int currentSoundEffectDuration;  
    int isMuted;
} GameModel;


/* Function prototypes for initializing and updating the game model */
void initModel(GameModel *model);
void updateModel(GameModel *model);

/* Function prototypes for moving various game objects */
void movePlayer(Player *player);
void moveAlien(Alien *alien);
void moveAlienShot(AlienShot *as);
void movePlayerShot(PlayerShot *ps);

#endif /* MODEL_H */
