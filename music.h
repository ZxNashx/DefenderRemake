#ifndef MUSIC_H
#define MUSIC_H

#include "defs.h"

/* number of notes in each song */
#define NUM_NOTES_IN_SONG_A 14
#define NUM_NOTES_IN_SONG_B 14

/* Define the structure for musical notes */
typedef struct {
    int frequency; /* Frequency of the note */
    int duration;  /* Duration of the note in milliseconds */
    int volume;    /* Volume of the note */
    int empty;
} Note;

/* Define note frequencies (simplified) */
#define C4 261
#define D4 294
#define E4 329
#define F4 349
#define G4 391
#define A4 440
#define B4 493
#define C5 523

/* Define musical note frequencies */
#define C     478
#define Cs    451
#define D     426
#define Ds    402
#define E     379
#define F     358
#define Fs    338
#define G     319
#define Gs    301
#define A     284
#define As    268
#define B     253


extern Note song_A[];
extern Note song_B[];

/*
q = quit, m = mute
run.g in atari ST to run
f12 to run fast
*/


void play_note(int channel, Note note);
void start_music(int channel, Note *song, int *currentNote, uint32_t *lastNoteTime);
void update_music(int channel, Note *song, int *currentNote, uint32_t *lastNoteTime, uint32_t currentTime, int numNotes);

#endif /* MUSIC_H */
