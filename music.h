#ifndef MUSIC_H
#define MUSIC_H

#include "defs.h"

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


extern Note game_song_A[];
extern Note game_song_B[];

extern Note menu_song_A[];
extern Note menu_song_B[];

/* number of notes in each song */
#define GAME_A_NOTECOUNT 32
#define GAME_B_NOTECOUNT 16

#define MENU_A_NOTECOUNT 14
#define MENU_B_NOTECOUNT 14

void play_note(int channel, Note note);
void start_music(int channel, Note *song, int *currentNote, uint32_t *lastNoteTime);
void update_music(int channel, Note *song, int *currentNoteIndex, uint32_t *lastNoteTime, int numNotes);
extern int music_update_request;
#endif /* MUSIC_H */
