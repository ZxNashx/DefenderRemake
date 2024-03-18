#include "psg.h"

/* Write a value to a PSG register */
void write_psg(int reg, uint8_t val) {
    if (reg < 0 || reg > 15) {
        return; // Invalid register number
    }
    PSG_REGISTERS[reg << 1] = val;
}

/* Read a value from a PSG register */
uint8_t read_psg(int reg) {
    if (reg < 0 || reg > 15) {
        return 0; // Invalid register number
    }
    return PSG_REGISTERS[reg << 1];
}

/* Set the tone for a given channel */
void set_tone(int channel, int tuning) {
    if (channel < 0 || channel > 2) {
        return; // Invalid channel number
    }
    int regOffset = channel * 2;
    write_psg(regOffset, tuning & 0xFF);      // Fine tuning
    write_psg(regOffset + 1, (tuning >> 8));  // Coarse tuning
}

/* Set the volume for a given channel */
void set_volume(int channel, int volume) {
    if (channel < 0 || channel > 2 || volume < 0 || volume > 15) {
        return; // Invalid parameters
    }
    write_psg(8 + channel, volume);
}

/* Enable or disable tone/noise for a channel */
void enable_channel(int channel, int tone_on, int noise_on) {
    /* check to se if it is a valid channel, [0,2]*/
    if (channel < 0 || channel > 2) {
        return;
    }
    uint8_t mixer = read_psg(7); // Mixer control register
    mixer &= ~(0x11 << channel); // Clear bits for channel
    if (!tone_on) {
        mixer |= (0x10 << channel); // Disable tone
    }
    if (!noise_on) {
        mixer |= (0x01 << channel); // Disable noise
    }
    write_psg(7, mixer);
}

/* Stop all PSG sound production */
void stop_sound() {
    for (int i = 0; i < 3; ++i) {
        set_volume(i, 0); // Mute all channels
    }
}

/* Set the noise register tuning */
void set_noise(int tuning) {
    if (tuning < 0 || tuning > 31) {
        return; // Invalid tuning
    }
    write_psg(6, tuning); // Noise generator control register
}

/* Set the PSG envelope shape and sustain */
void set_envelope(int shape, unsigned int sustain) {
    if (shape < 0 || shape > 15) {
        return; // Invalid envelope shape
    }
    // Envelope period low byte
    write_psg(11, sustain & 0xFF);
    // Envelope period high byte
    write_psg(12, (sustain >> 8) & 0xFF);
    // Envelope shape
    write_psg(13, shape);
}
