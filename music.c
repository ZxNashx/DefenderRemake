#include "music.h"
#include "defs.h"
#include "psg.h"
#include "helper.h"
#include "isr.h"

/* Song data */
Note game_song_A[] = {
    {C, 25, 10}, {Cs, 25, 10}, {G4, 25, 10}, {G4, 25, 10},
    {A4, 25, 10}, {A4, 25, 10}, {G4, 50, 10}, {F4, 25, 10},
    {F4, 25, 10}, {E4, 25, 10}, {E4, 25, 10}, {D4, 25, 10},
    {D4, 25, 10}, {C4, 50, 10}
};

/* Song data */
Note game_song_B[] = {
    {C4, 25, 10}, {C4, 25, 10}, {G4, 25, 10}, {G4, 25, 10},
    {A4, 25, 10}, {A4, 25, 10}, {G4, 50, 10}, {F4, 25, 10},
    {F4, 25, 10}, {E4, 25, 10}, {E4, 25, 10}, {D4, 25, 10},
    {D4, 25, 10}, {C4, 50, 10}
};
Note menu_song_A[] = {
    {C, 25, 10}, {Cs, 25, 10}, {G4, 25, 10}, {G4, 25, 10},
    {A4, 25, 10}, {A4, 25, 10}, {G4, 50, 10}, {F4, 25, 10},
    {F4, 25, 10}, {E4, 25, 10}, {E4, 25, 10}, {D4, 25, 10},
    {D4, 25, 10}, {C4, 50, 10}
};

/* Song data */
Note menu_song_B[] = {
    {C4, 25, 10}, {C4, 25, 10}, {G4, 25, 10}, {G4, 25, 10},
    {A4, 25, 10}, {A4, 25, 10}, {G4, 50, 10}, {F4, 25, 10},
    {F4, 25, 10}, {E4, 25, 10}, {E4, 25, 10}, {D4, 25, 10},
    {D4, 25, 10}, {C4, 50, 10}
};


/* Play a note on a specific channel */
void play_note(int channel, Note note) {
    set_tone(channel, note.frequency);
    enable_channel(channel, 1, 0);
    set_volume(channel, note.volume);

}

/* Start playing a song on a specific channel */
void start_music(int channel, Note *song, int *currentNote, uint32_t *lastNoteTime) {
    *currentNote = 0;
    *lastNoteTime = vbl_counter;
    play_note(channel, song[*currentNote]);
}

/* Update music function */
void update_music(int channel, Note *song, int *currentNoteIndex, uint32_t *lastNoteTime, int numNotes) {
    uint32_t elapsedTime = vbl_counter  - *lastNoteTime;

    if (elapsedTime >= song[*currentNoteIndex].duration) {
        *currentNoteIndex = (*currentNoteIndex + 1) % numNotes;
        *lastNoteTime = vbl_counter;
        play_note(channel, song[*currentNoteIndex]);
    }
}
