#ifndef PSG_H
#define PSG_H

#include <stdint.h>

/* PSG register addresses */
#define PSG_REGISTERS ((volatile uint8_t *)0xFFFF8800)

/* Function prototypes */
void write_psg(int reg, uint8_t val);
uint8_t read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);

#endif /* PSG_H */
