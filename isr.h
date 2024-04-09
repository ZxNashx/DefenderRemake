#ifndef ISR_H
#define ISR_H

/* Define the vector number for VBL */
#define VBL_VECTOR 28
#define IKBD_VECTOR 70

/* Type definition for a Vector */
typedef void (*Vector)();

/*
Function: init_isr
Arguments: None.
Description:
    Initializes the interrupt service routines (ISRs) for the game. This typically involves setting up VBL (vertical blank interrupt) and other necessary interrupts.
*/
void init_isr();

/*
Function: clean_isr
Arguments: None.
Description:
    Cleans up and restores the original state of the ISRs when the game is finished or the ISR functionality is no longer required.
*/
void clean_isr();

/*
Function: install_vector
Arguments:
    int num: The interrupt number for which the vector is being installed.
    Vector vector: The function pointer to the new ISR.
Returns:
    Vector: The original ISR which was replaced.
Description:
    Installs a new interrupt service routine for a specific interrupt vector, returning the original ISR for later restoration if needed.
*/
Vector install_vector(int num, Vector vector);

/*
Function: do_VBL_ISR
Arguments: None.
Description:
    The ISR function to be executed on each vertical blank interrupt. Typically handles time-critical tasks like screen refresh or animation updates.
*/
void do_VBL_ISR();

/*
Function: do_IKBD_ISR
Arguments: None.
Description:
    The ISR function for handling the keyboard input from the Atari ST's IKBD (Intelligent Keyboard). Processes the keyboard scan codes to manage game input.
*/
void do_IKBD_ISR();

/*
Function: clear_key_buffer
Arguments: None.
Description:
    Clears the buffer that stores the keys pressed, typically used to reset the keyboard state.
*/
void clear_key_buffer();

/*
Function: get_keys_pressed
Arguments:
    char *keys: Array to store the keys pressed.
    int maxKeys: The maximum number of keys to read.
Description:
    Populates the provided array with the scan codes of the keys currently pressed, up to the specified maximum number.
*/
void get_keys_pressed(char *keys, int maxKeys);

/*
Function: is_key_pressed
Arguments:
    char checkKey: The key to check for being pressed.
Returns:
    int: 1 if the specified key is pressed, 0 otherwise.
Description:
    Checks if a specific key, represented by its scan code, is currently pressed.
*/
int is_key_pressed(char checkKey);

/*
Function: scancode_to_char
Arguments:
    unsigned char scancode: The scan code to convert to a character.
Returns:
    char: The corresponding ASCII character of the scan code, if available.
Description:
    Converts a keyboard scan code to its corresponding ASCII character, considering the current keyboard layout and state.
*/
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
extern Vector orig_vector_vbl;
extern Vector orig_vector_ikbd;

extern int mouse_x;
extern int mouse_y;
extern int mouse_dx;
extern int mouse_dy;

extern int mouse_dx_accumulator;
extern int mouse_dy_accumulator;
extern unsigned char mouse_button_state;
extern int mouse_packet_state;

/* Assembly function declarations */
extern void vbl_isr();
extern void ikbd_isr();
extern void disable_interrupts();
extern void enable_interrupts();

#define ACIA_STATUS_REGISTER (*(volatile unsigned char *)0xFFFFFC00)
#define ACIA_DATA_REGISTER (*(volatile unsigned char *)0xFFFFFC02)
#define MFP_IN_SERVICE_B_REGISTER (*(volatile unsigned char *)0xFFFA11)

#define ACIA_STATUS_RX_FULL 0x01 

#endif /* vbl isr */
