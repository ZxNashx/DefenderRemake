#include "effects.h"
#include "psg.h"

void sound_playershot() {
    /* Set an envelope for a quick attack and decay */
    int envelopeShape = 0x09; /* Attack and Decay, no Sustain, no Repeat */
    unsigned int envelopeSustain = 0; /* No sustain */
    /* Set a medium-high pitch tone for the 'pew' sound */
    set_tone(2, 800); /* Channel C, frequency for 'pew' sound */

    /* Enable tone and optionally noise on channel C */
    enable_channel(2, 1, 0); /* Channel C, tone on, noise off or low */

    /* Set the volume for a quick but noticeable presence */
    set_volume(2, 12); /* Channel C, moderately high volume */
    set_envelope(envelopeShape, envelopeSustain);
}

void no_sound_effect() {
    /* Disable both tone and noise for channel C */
    enable_channel(2, 0, 0); /* Channel C, tone off, noise off */

    /* Optionally, you can also set the volume of the channel to 0 */
    set_volume(2, 0); /* Channel C, volume level to 0 */
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
    set_volume(2, 15);         /* Channel C, medium volume for damage */
    /* set_envelope(shape, sustain); */ /* Optionally modify the envelope */
}

/* Sound effect for loss of life */
void sound_game_over() {
    set_tone(0, 800);  /* Channel A, loss of life tone */
    enable_channel(0, 1, 0);  /* Channel A, tone on, noise off */
    set_volume(0, 12);        /* Channel A, full volume for impact */
    /* set_envelope(shape, sustain); */ /* Optionally modify the envelope */
}
