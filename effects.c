#include "effects.h"
#include "psg.h"

/* Sound effect for player shooting */
void sound_playershot() {
    /* Set the tone for channel C to a specific frequency */
    set_tone(2, 500);  /* Channel C, arbitrary tuning value for example */

    /* Set the noise tuning to create a "hit" effect */
    set_noise(15);  /* Arbitrary noise tuning value */

    /* Enable both tone and noise on channel C */
    enable_channel(2, 1, 1); /* Channel C, tone on, noise on */

    /* Set the volume to a suitable level */
    set_volume(0, 10); /* Channel A, volume level (0 to 15) */

    /* Optionally, set an envelope to modify the sound over time */
    /* set_envelope(shape, sustain); */ /* Uncomment and modify as needed */
}

/* Sound effect for explosion */
void sound_explosion() {
    set_tone(2, 300);  /* Channel B, explosion tone */
    set_noise(10);     /* Noise for explosion effect */
    enable_channel(2, 1, 1);  /* Channel B, tone and noise on */
    set_volume(2, 12);        /* Channel B, higher volume for explosion */
    /* set_envelope(shape, sustain); */ /* Optionally modify the envelope */
}

/* Sound effect for spaceship damage */
void sound_spaceship_damage() {
    set_tone(2, 400);  /* Channel C, damage tone */
    set_noise(20);     /* Noise for damage effect */
    enable_channel(2, 1, 1);  /* Channel C, tone and noise on */
    set_volume(2, 8);         /* Channel C, medium volume for damage */
    /* set_envelope(shape, sustain); */ /* Optionally modify the envelope */
}

/* Sound effect for loss of life */
void sound_loss_of_life() {
    set_tone(0, 800);  /* Channel A, loss of life tone */
    enable_channel(0, 1, 0);  /* Channel A, tone on, noise off */
    set_volume(0, 15);        /* Channel A, full volume for impact */
    /* set_envelope(shape, sustain); */ /* Optionally modify the envelope */
}
