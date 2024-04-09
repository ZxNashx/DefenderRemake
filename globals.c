#include "defs.h"
#include "isr.h"
#include "music.h"
#include "psg.h"
#include "model.h"

char *backBuffer;
char *frontBuffer;
char *orig_buffer;
/* buffer size is 32k */
char rawBackBuffer[BUFFER_SIZE + 256];


GameModel model;

unsigned int vbl_counter = 0;
int render_request = 0;
int music_update_request = 0;
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
unsigned int time_since_last_enemy = 0;
int mouse_dx = 0;
int mouse_dy = 0;
int mouse_x = 0;
int mouse_y = 0;

int mouse_packet_state = 0;
unsigned char mouse_button_state;

Vector orig_vector_vbl;
Vector orig_vector_ikbd;

/* Song data */
Note game_song_A[] = {
    {C, 30, 0, 0}, {Gs, 25, 10, 0}, {F, 25, 10, 0}, {C, 25, 10, 0},{F, 25, 10, 0}, {Gs, 25, 10, 0}, {F, 25, 10, 0}, {C, 25, 10, 0},
    {C, 30, 0, 0}, {Gs, 25, 10, 0}, {F, 25, 10, 0}, {Cs, 25, 10, 0},{F, 25, 10, 0}, {Gs, 25, 10, 0}, {F, 25, 10, 0}, {Cs, 25, 10, 0},
    {C, 30, 0, 0}, {F, 25, 10, 0}, {Cs, 25, 10, 0}, {B, 25, 10, 0},{Cs, 25, 10, 0}, {F, 25, 10, 0}, {Cs, 25, 10, 0}, {B, 25, 10, 0},
    {C, 30, 0, 0}, {C, 25, 10, 0}, {E, 25, 10, 0}, {G, 25, 10, 0},{E, 25, 10, 0}, {C, 25, 10, 0}, {E, 25, 10, 0}, {G, 25, 10, 0}
};

/* Song data */
Note game_song_B[] = {
    {F, 8000, 5, 0},{F, 8000, 5, 0},{F, 8000, 5, 0},{F, 8000, 5, 0},
    {Cs, 8000, 5, 0},{Cs, 8000, 5, 0},{Cs, 8000, 5, 0},{Cs, 8000, 5, 0},
    {As, 8000, 5, 0},{As, 8000, 5, 0},{As, 8000, 5, 0},{As, 8000, 5, 0},
    {C, 8000, 5, 0},{C, 8000, 5, 0},{C, 8000, 5, 0},{C, 8000, 5, 0}
};

Note menu_song_A[] = {
    {C, 25, 10, 0}, {Cs, 25, 10, 0}, {G4, 25, 10, 0}, {G4, 25, 10, 0},
    {A4, 25, 10, 0}, {A4, 25, 10, 0}, {G4, 50, 10, 0}, {F4, 25, 10, 0},
    {F4, 25, 10, 0}, {E4, 25, 10, 0}, {E4, 25, 10, 0}, {D4, 25, 10, 0},
    {D4, 25, 10, 0}, {C4, 50, 10, 0}
};

/* Song data */
Note menu_song_B[] = {
    {C4, 25, 10, 0}, {C4, 25, 10, 0}, {G4, 25, 10, 0}, {G4, 25, 10, 0},
    {A4, 25, 10, 0}, {A4, 25, 10, 0}, {G4, 50, 10, 0}, {F4, 25, 10, 0},
    {F4, 25, 10, 0}, {E4, 25, 10, 0}, {E4, 25, 10, 0}, {D4, 25, 10, 0},
    {D4, 25, 10, 0}, {C4, 50, 10, 0}
};

/* Global variable to keep track of the current state of the mixer register */
uint8_t currentMixer = 0x3F;  /* All three channels disabled initially */
int isMuted = false;
