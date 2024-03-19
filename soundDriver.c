#include "psg.h"
#include <osbind.h> 

#define C4  262
#define G3  196
#define A3  220
#define F4  349
#define E4  330
#define D4  294

#define BEAT_DURATION 100 
/* Function to get the current time from the system clock */
unsigned long get_time() {
    return *((volatile unsigned long *)0x462);
}
void play_note(int note, int duration) {
    unsigned long end_time;

    enable_channel(0, 1, 0);


    set_volume(0, 15);


    end_time = get_time() + duration;
    while (get_time() < end_time);


    enable_channel(0, 0, 0);
}

int main() {
    int melody[] = {C4, C4, G3, G3, A3, A3, G3, F4, F4, E4, E4, D4, D4, C4};
    int beats[] = {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2};
    int i;
    for (i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        play_note(melody[i], beats[i] * BEAT_DURATION);
    }

    stop_sound();

    return 0;
}
