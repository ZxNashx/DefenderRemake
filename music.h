#ifndef MUSIC_H
#define MUSIC_H

#include "defs.h"

/* Define note frequencies (simplified) */
#define C4 261
#define D4 294
#define E4 329
#define F4 349
#define G4 391
#define A4 440
#define B4 493
#define C5 523


/* Define the structure for musical notes */
typedef struct {
    int frequency;     /* Frequency of the note */
    int duration;      /* Duration of the note in milliseconds */
} Note;

/* Function to start playing music */
void start_music(int *currentNote, uint32_t *lastNoteTime, Note *song, int numNotes);

/* Function to play a specific note */
void play_note(int frequency);

/* Function to update the music based on the current time */
void update_music(int *currentNote, uint32_t *lastNoteTime, uint32_t currentTime, Note *song, int numNotes);


#endif /* MUSIC_H */
