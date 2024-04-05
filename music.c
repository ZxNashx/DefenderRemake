#include "music.h"
#include "defs.h"
#include "psg.h"
#include "helper.h"

/* Play a note */
void play_note(int frequency) {
    set_tone(0, frequency);
    enable_channel(0, 1, 0);
    set_volume(0, 15);
}

/* Start playing music */
void start_music(int *currentNote, uint32_t *lastNoteTime, Note *song, int numNotes) {
    *currentNote = 0;
    *lastNoteTime = get_time();
    play_note(song[*currentNote].frequency);
}

/* Update the music */
void update_music(int *currentNote, uint32_t *lastNoteTime, uint32_t currentTime, Note *song, int numNotes) {
    if (currentTime - *lastNoteTime >= song[*currentNote].duration) {
        *currentNote = (*currentNote + 1) % numNotes;
        *lastNoteTime = currentTime;
        play_note(song[*currentNote].frequency);
    }
}
