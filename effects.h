#ifndef EFFECTS_H
#define EFFECTS_H
/*
Function: sound_playershot
Description:
    Elicits the audio cue for a player's projectile discharge, enhancing the sensory feedback for firing actions.
*/
void sound_playershot();

/*
Function: sound_explosion
Description:
    Triggers the audio representation of an explosion, ideal for the dramatic effect of objects or enemies being destroyed.
*/
void sound_explosion();

/*
Function: sound_spaceship_damage
Description:
    Initiates the sound for spaceship damage, adding auditory realism to the experience of taking hits.
*/
void sound_spaceship_damage();

/*
Function: sound_game_over
Description:
    Conveys the game's conclusion through a distinctive audio signal, marking the end of a play session.
*/
void sound_game_over();

/*
Function: no_sound_effect
Description:
    Serves as an auditory placeholder in scenarios where silence is preferred or no specific sound effect is required.
*/
void no_sound_effect();

/*
Function: boundry_hit
Description:
    Produces a sound for boundary collisions, useful for notifying players of impacts with screen edges or obstacles.
*/
void boundry_hit();

#endif 