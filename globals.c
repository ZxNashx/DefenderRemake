#include "defs.h"
#include "isr.h"
#include "music.h"
#include "psg.h"
#include "model.h"


GameModel model;

unsigned int vbl_counter = 0;
int render_request = 0;
int gameMusicActive = false;
int menuMusicActive = false;
int currentNoteIndex_GameA = 0;
int currentNoteIndex_GameB = 0;
int currentNoteIndex_MenuA = 0;
int currentNoteIndex_MenuB = 0;
uint32_t lastNoteTime_GameA = 0;
uint32_t lastNoteTime_GameB = 0;
uint32_t lastNoteTime_MenuA = 0;
uint32_t lastNoteTime_MenuB = 0;
char key_buffer[KEY_BUFFER_SIZE];
int key_buffer_start = 0;
int key_buffer_end = 0;

Vector orig_vector_vbl;
Vector orig_vector_ikbd;

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

/* Global variable to keep track of the current state of the mixer register */
uint8_t currentMixer = 0x3F;  /* All three channels disabled initially */
int isMuted;
