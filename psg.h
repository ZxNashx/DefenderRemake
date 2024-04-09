#ifndef PSG_H
#define PSG_H

#include "defs.h"


#define PSG_REGISTERS ((volatile uint8_t *)0xFFFF8800)

extern int isMuted;
extern uint8_t currentMixer;

/*
Function: write_psg
Arguments:
    int reg: The PSG register number to write to.
    uint8_t val: The value to write to the PSG register.
Description:
    Writes a byte value to a specified register of the PSG (Programmable Sound Generator).
*/
void write_psg(int reg, uint8_t val);

/*
Function: read_psg
Arguments:
    int reg: The PSG register number to read from.
Returns:
    uint8_t: The value read from the specified PSG register.
Description:
    Reads a byte value from a specified register of the PSG.
*/
uint8_t read_psg(int reg);

/*
Function: set_tone
Arguments:
    int channel: The channel (0-2) of the PSG to set the tone for.
    int tuning: The tuning value to set for the tone generator.
Description:
    Sets the tone frequency for a specified channel of the PSG.
*/
void set_tone(int channel, int tuning);

/*
Function: set_volume
Arguments:
    int channel: The channel (0-2) of the PSG to set the volume for.
    int volume: The volume level to set (0-15).
Description:
    Sets the volume for a specified channel of the PSG.
*/
void set_volume(int channel, int volume);

/*
Function: enable_channel
Arguments:
    int channel: The channel (0-2) of the PSG to enable or disable.
    int tone_on: Enable or disable the tone generator (1 to enable, 0 to disable).
    int noise_on: Enable or disable the noise generator (1 to enable, 0 to disable).
Description:
    Enables or disables the tone and/or noise generation for a specified channel of the PSG.
*/
void enable_channel(int channel, int tone_on, int noise_on);

/*
Function: stop_sound
Arguments: None.
Description:
    Stops all sound generation by the PSG.
*/
void stop_sound();

/*
Function: set_noise
Arguments:
    int tuning: The tuning value to set for the noise generator.
Description:
    Sets the noise frequency for the PSG noise generator.
*/
void set_noise(int tuning);

/*
Function: set_envelope
Arguments:
    int shape: The envelope shape to set.
    unsigned int sustain: The sustain level for the envelope.
Description:
    Sets the envelope shape and sustain level for the PSG.
*/
void set_envelope(int shape, unsigned int sustain);

#endif 