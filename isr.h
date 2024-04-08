#ifndef ISR_H
#define ISR_H

/* Define the vector number for VBL */
#define VBL_VECTOR 28
#define IKBD_VECTOR 70

/* Type definition for a Vector */
typedef void (*Vector)();

/* Function prototypes */
void init_isr();
void clean_isr();
Vector install_vector(int num, Vector vector);
void do_VBL_ISR();
void do_IKBD_ISR();
void clear_key_buffer();
void get_keys_pressed(char *keys, int maxKeys);
int is_key_pressed(char checkKey);
char scancode_to_char(unsigned char scancode);

extern unsigned int vbl_counter;
extern int render_request;
extern int gameMusicActive;
extern int menuMusicActive;
extern int currentNoteIndex_GameA;
extern int currentNoteIndex_GameB;
extern int currentNoteIndex_MenuA;
extern int currentNoteIndex_MenuB;
extern uint32_t lastNoteTime_GameA;
extern uint32_t lastNoteTime_GameB;
extern uint32_t lastNoteTime_MenuA;
extern uint32_t lastNoteTime_MenuB;
extern char key_buffer[KEY_BUFFER_SIZE];
extern int key_buffer_start;
extern int key_buffer_end;

/* Assembly function declarations */
extern void vbl_isr();
extern void ikbd_isr();

#define ACIA_STATUS_REGISTER (*(volatile unsigned char *)0xFFFFFC00)
#define ACIA_DATA_REGISTER (*(volatile unsigned char *)0xFFFFFC02)
#define MFP_IN_SERVICE_B_REGISTER (*(volatile unsigned char *)0xFFFA11)

#define ACIA_STATUS_RX_FULL 0x01 

#endif /* vbl isr */
