#include <osbind.h> 
#include <stdio.h>

#include "psg.h"
#include "effects.h"
#include "music.h"


/* Twinkle Twinkle Little Star notes with shorter durations for a faster tempo */
Note song[] = {
    {C4, 25}, {C4, 25}, {G4, 25}, {G4, 25}, {A4, 25}, {A4, 25}, {G4, 50},
    {F4, 25}, {F4, 25}, {E4, 25}, {E4, 25}, {D4, 25}, {D4, 25}, {C4, 50},
};


uint32_t get_time() {
    uint32_t *pointerToTimer = (volatile uint32_t *)0x462;
    uint32_t timenow;
    uint32_t old_ssp;

    old_ssp = Super(0);      
    timenow = *pointerToTimer;  
    Super(old_ssp);       

    return timenow;    
}

/* Function to implement a delay in milliseconds */
void delay_milliseconds(uint32_t milliseconds) {
    uint32_t start = get_time();
    uint32_t end = start + milliseconds;

    while (get_time() < end) {
        /* Do nothing, just wait */
    }
}

/* Function to play a note for a given duration */
void play_note(int frequency, int duration) {
    set_tone(0, frequency);  /* Set the frequency of the note */
    enable_channel(0, 1, 0); /* Enable the channel */
    set_volume(0, 15);       /* Set maximum volume */

    delay_milliseconds(duration); /* Wait for the duration of the note */

    stop_sound(); /* Stop the sound after the duration */
}

/* Function to play the song */
void play_song(Note *song, int length) {
    int i;
    stop_sound(); /* Ensure all channels are stopped before starting */
    for (i = 0; i < length; ++i) {
        play_note(song[i].frequency, song[i].duration);
    }
}



/* Include your delay_seconds and get_time function prototypes here */

int main() {
    int songLength = sizeof(song) / sizeof(song[0]);

    /* Testing Player Shot Sound */
    printf("Playing Player Shot Sound\n");
    stop_sound();
    sound_playershot();
    delay_milliseconds(250);
    stop_sound();

    /* Testing Explosion Sound */
    printf("Playing Explosion Sound\n");
    stop_sound();
    sound_explosion();
    delay_milliseconds(250);
    stop_sound();

    /* Testing Spaceship Damage Sound */
    printf("Playing Spaceship Damage Sound\n");
    stop_sound();
    sound_spaceship_damage();
    delay_milliseconds(250);
    stop_sound();

    /* Testing Loss of Life Sound */
    printf("Playing Loss of Life Sound\n");
    stop_sound();
    sound_loss_of_life();
    delay_milliseconds(250);
    stop_sound();

    printf("Playering a song\n");
    play_song(song, songLength);

    return 0;
}
