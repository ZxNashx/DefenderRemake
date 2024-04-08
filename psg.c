#include "defs.h"
#include "psg.h"

#include <stdio.h>
#include <osbind.h>

/* Global variable to keep track of the current state of the mixer register */
static uint8_t currentMixer = 0x3F;  /* All three channels disabled initially */
int isMuted;


/* Function to write a value to a PSG register */
void write_psg(int reg, uint8_t val) {
    long old_ssp;

    /* Switch to supervisor mode */
    old_ssp = Super(0);

    /* Write register number to PSG register select */
    *(volatile uint8_t*)PSG_REG_SELECT = reg;

    /* Write value to PSG register write */
    *(volatile uint8_t*)PSG_REG_WRITE = val;

    /* Switch back to user mode */
    Super(old_ssp);
}
/* Function to set the tone (frequency) of a channel */
void set_tone(int channel, int tuning) {
    int fineTune = tuning & 0x0F;   /* Lower 4 bits */
    int coarseTune = (tuning >> 4) & 0x0F; /* Upper 4 bits */

    /* Write to fine and coarse tune registers of the channel */
    write_psg(channel * 2, fineTune);
    write_psg(channel * 2 + 1, coarseTune);
}

/* Function to set the volume of a channel */
void set_volume(int channel, int volume) {
    /* Volume register for each channel is at 8, 9, and 10 */
    if(isMuted){
        write_psg(8 + channel, 0x0); /* Volume is 4 bits */
    }else{
        write_psg(8 + channel, volume & 0x0F); /* Volume is 4 bits */
    }
    
}

/* Function to enable/disable channel */
void enable_channel(int channel, int tone_on, int noise_on) {
    /* Modify only the relevant bits for the specified channel */
    if (tone_on) {
        currentMixer &= ~(1 << channel); /* Enable tone for channel */
    } else {
        currentMixer |= (1 << channel); /* Disable tone for channel */
    }

    if (noise_on) {
        currentMixer &= ~(1 << (channel + 3)); /* Enable noise for channel */
    } else {
        currentMixer |= (1 << (channel + 3)); /* Disable noise for channel */
    }

    /* Update the mixer control register */
    write_psg(7, currentMixer);
}

/** 
 * Function to stop all sound and reset PSG settings 
 */
void stop_sound() {
    /* Reset tone and noise frequencies to default for all channels */
    int channel;
    for (channel = 0; channel < 3; channel++) {
        set_tone(channel, 0);  /* Reset tone frequency */
        set_volume(channel, 0); /* Mute volume */
    }

    /* Reset noise frequency */
    set_noise(0);

    /* Reset envelope */
    set_envelope(0, 0);

    /* Disable tone and noise for all channels */
    currentMixer = 0x3F; /* All bits set to disable tones and noises */
    write_psg(7, currentMixer);
}


/* Function to set noise tuning */
void set_noise(int tuning) {
    write_psg(6, tuning & 0x1F); /* Noise tuning is 5 bits */
}

/* Function to set the envelope */
void set_envelope(int shape, unsigned int sustain) {
    write_psg(11, sustain & 0xFF); /* Lower byte of sustain */
    write_psg(12, (sustain >> 8) & 0xFF); /* Upper byte of sustain */
    write_psg(13, shape & 0x0F); /* Envelope shape is 4 bits */
}

