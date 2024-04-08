#include "music.h"
#include "defs.h"
#include "psg.h"
#include "helper.h"
#include "isr.h"


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
