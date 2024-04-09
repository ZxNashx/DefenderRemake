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

/*
Function: play_note
Arguments:
    int channel: The PSG channel (0-2) on which to play the note.
    Note note: The note structure containing the frequency and duration of the note.
Description:
    Plays a single note on the specified channel of the PSG. The note is defined by its frequency and duration.
*/
void play_note(int channel, Note note);

/*
Function: start_music
Arguments:
    int channel: The PSG channel (0-2) to start playing music on.
    Note *song: Pointer to an array of notes constituting the song.
    int *currentNote: Pointer to an integer tracking the index of the current note in the song.
    uint32_t *lastNoteTime: Pointer to a variable tracking the time at which the last note was played.
Description:
    Starts playing a musical piece on a specified channel, beginning from the first note. It updates the current note index and the last note time.
*/
void start_music(int channel, Note *song, int *currentNote, uint32_t *lastNoteTime);

/*
Function: update_music
Arguments:
    int channel: The PSG channel (0-2) where music is being played.
    Note *song: Pointer to an array of notes constituting the song.
    int *currentNoteIndex: Pointer to an integer tracking the index of the current note in the song.
    uint32_t *lastNoteTime: Pointer to a variable tracking the time since the last note was played.
    int numNotes: The total number of notes in the song.
Description:
    Updates the musical playback on a specified channel. It progresses through the song based on the current note index and the time elapsed since the last note was played, looping over if necessary.
*/
void update_music(int channel, Note *song, int *currentNoteIndex, uint32_t *lastNoteTime, int numNotes);


extern int music_update_request;
#endif /* MUSIC_H */
