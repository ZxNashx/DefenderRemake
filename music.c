#include "music.h"
#include "defs.h"
#include "psg.h"
#include "helper.h"

/* Song data */
Note song_A[] = {
    {C, 25, 10}, {Cs, 25, 10}, {G4, 25, 10}, {G4, 25, 10},
    {A4, 25, 10}, {A4, 25, 10}, {G4, 50, 10}, {F4, 25, 10},
    {F4, 25, 10}, {E4, 25, 10}, {E4, 25, 10}, {D4, 25, 10},
    {D4, 25, 10}, {C4, 50, 10}
};

/* Song data */
Note song_B[] = {
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
    *lastNoteTime = get_time();
    play_note(channel, song[*currentNote]);
}
/* Update a song on a specific channel */
void update_music(int channel, Note *song, int *currentNote, uint32_t *lastNoteTime, uint32_t currentTime, int numNotes) {
    uint32_t elapsedTime = currentTime - *lastNoteTime;

    if (elapsedTime >= song[*currentNote].duration) {
        *currentNote = (*currentNote + 1) % numNotes;
        *lastNoteTime = currentTime;
        play_note(channel, song[*currentNote]);
    }
}