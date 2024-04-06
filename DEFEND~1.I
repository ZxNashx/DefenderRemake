# 1 "defend~1.c" 1
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 1 "defend~1.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 2 "defend~1.c" 2
# 1 "./model.h" 1
# 1 "./defs.h" 1
# 20 "./defs.h"
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef int int16_t;
typedef unsigned int uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
# 4 "./model.h" 2
# 19 "./model.h"
typedef struct {
    int x, y;
    unsigned int lives;
    unsigned int score;



    int dx;
    int dy;
    unsigned int speed;
    int empty;
} Player;
# 43 "./model.h"
typedef struct {
    int x, y;
    unsigned short active;
    int dx;
    int dy;
    int empty;
} Alien;
# 60 "./model.h"
typedef struct {
    unsigned int x, y;
    unsigned int active;
    int dx;
} PlayerShot;
# 77 "./model.h"
typedef struct {
    int x, y;
    unsigned short active;
    int dx;
} AlienShot;
# 97 "./model.h"
typedef struct {
    Player player;
    Alien aliens[256 ];
    AlienShot alienShots[256 ];
    PlayerShot playerShots[256 ];
    int game_running;
    void (*currentSoundEffect)();
    int currentSoundEffectDuration;
    int isMuted;
} GameModel;



void initModel(GameModel *model);
void updateModel(GameModel *model);


void movePlayer(Player *player);
void moveAlien(Alien *alien);
void moveAlienShot(AlienShot *as);
void movePlayerShot(PlayerShot *ps);
# 3 "defend~1.c" 2
# 1 "./renderer.h" 1
# 1 "./model.h" 1
# 4 "./renderer.h" 2
# 15 "./renderer.h"
void clear_region(char *base, int x, int y, int width, int height);
# 25 "./renderer.h"
void renderPlayer(Player *player, char *base);
# 35 "./renderer.h"
void renderAlien(Alien *alien, char *base);
void renderShot(char *base, unsigned int x, unsigned int y);
# 46 "./renderer.h"
void render(GameModel *model, char *base);
# 4 "defend~1.c" 2
# 1 "./events.h" 1
# 1 "./model.h" 1
# 4 "./events.h" 2
# 14 "./events.h"
void move_left(GameModel *model);
# 24 "./events.h"
void move_right(GameModel *model);
# 34 "./events.h"
void move_up(GameModel *model);
# 44 "./events.h"
void move_down(GameModel *model);
# 54 "./events.h"
void shoot(GameModel *model);
# 63 "./events.h"
void quit_game(GameModel *model);
# 72 "./events.h"
void move_enemies(GameModel *model);
# 82 "./events.h"
void generate_alien_shot(GameModel *model);
# 91 "./events.h"
void generate_alien(GameModel *model);
# 100 "./events.h"
void player_shot_collides_with_alien(GameModel *model);
# 109 "./events.h"
void player_shot_out_of_screen(GameModel *model);
# 118 "./events.h"
void alien_shot_collides_with_player(GameModel *model);
# 127 "./events.h"
void alien_shot_out_of_screen(GameModel *model);
# 136 "./events.h"
int player_runs_out_of_lives(GameModel *model);
# 145 "./events.h"
void player_collides_with_alien(GameModel *model);

void freeze_player(GameModel *model);
void toggle_mute(GameModel *model);
# 5 "defend~1.c" 2
# 1 "./defs.h" 1
# 6 "defend~1.c" 2
# 1 "./raster.h" 1
# 15 "./raster.h"
void plot_pixel(char *base, int x, int y, int black);
# 24 "./raster.h"
void clear_black(char *base);
# 36 "./raster.h"
void draw_hline(char *base, int x1, int x2, int y);
# 50 "./raster.h"
void plot_bitmap(char *base, const unsigned int *bitmap, int x, int y, int width, int height);
# 65 "./raster.h"
void drawCircle(char *base, int xc, int yc, int x, int y);
# 79 "./raster.h"
void plot_circle(char *base, int xc, int yc, int r);
# 91 "./raster.h"
void plot_rectangle(char *base, int x1, int y1, int x2, int y2);
# 7 "defend~1.c" 2
# 1 "./input.h" 1
# 1 "./model.h" 1
# 3 "./input.h" 2


int input_available();

unsigned int read_input();
# 17 "./input.h"
void handle_input(GameModel *model, unsigned int input);
# 8 "defend~1.c" 2
# 1 "./bitmap.h" 1



extern unsigned int spaceship_bitmap[8];
extern unsigned int alien_bitmap[8];


unsigned int reverseBits(unsigned int num);
void mirrorBitmap(const unsigned int *bitmap, unsigned int *mirroredBitmap, unsigned int size);
# 9 "defend~1.c" 2
# 1 "./music.h" 1
# 1 "./defs.h" 1
# 4 "./music.h" 2
# 18 "./music.h"
typedef struct {
    int frequency;
    int duration;
} Note;


void start_music(int *currentNote, uint32_t *lastNoteTime, Note *song, int numNotes);


void play_note(int frequency);


void update_music(int *currentNote, uint32_t *lastNoteTime, uint32_t currentTime, Note *song, int numNotes);
# 10 "defend~1.c" 2
# 1 "./helper.h" 1
# 1 "./defs.h" 1
# 4 "./helper.h" 2



uint32_t get_time();
int hit_detection(int point_x, int point_y,
                        int box_x, int box_y,
                        int box_width, int box_height);
# 11 "defend~1.c" 2
# 1 "./psg.h" 1
# 1 "./defs.h" 1
# 4 "./psg.h" 2
# 10 "./psg.h"
void write_psg(int reg, uint8_t val);
uint8_t read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);
# 12 "defend~1.c" 2
# 1 "./effects.h" 1




void sound_playershot();


void sound_explosion();


void sound_spaceship_damage();


void sound_loss_of_life();



void no_sound_effect();
# 13 "defend~1.c" 2



char rawBackBuffer[32000  + 256];
char *backBuffer;
char *frontBuffer;
char *orig_buffer;

void wait_for_vertical_blank(uint32_t last_vblank) {
    uint32_t current_time;
    do {
        current_time = get_time();
    } while (current_time == last_vblank);
}

void swapBuffers(char **frontBuffer, char **backBuffer) {
    char *temp = *frontBuffer;
    *frontBuffer = *backBuffer;
    *backBuffer = temp;
}


int main() {
    GameModel model;


    uint32_t timeThen, timeNow, timeElapsed, lastMusicUpdate;
    int currentNote = 0;
    uint32_t lastNoteTime = 0;
    int numNotes;
    unsigned short soundEffectPlayTime = 0;
    int i;


    Note song[] = {
        {261 , 25}, {261 , 25}, {391 , 25}, {391 , 25}, {440 , 25}, {440 , 25}, {391 , 50},
        {349 , 25}, {349 , 25}, {329 , 25}, {329 , 25}, {294 , 25}, {294 , 25}, {261 , 50},

    };
    numNotes = sizeof(song) / sizeof(song[0]);



    backBuffer = rawBackBuffer;
    while(( ((uint32_t)backBuffer) & 255) != 0){
        backBuffer++;
    }

    orig_buffer = (void*)_trap_14_w((short)0x2) ;
    frontBuffer = (void*)_trap_14_w((short)0x2) ;
    (void)_trap_14_wllw((short)0x5,(long)(-1),(long)backBuffer,(short)(-1)) ;


    initModel(&model);

    start_music(&currentNote, &lastNoteTime, song, numNotes);
    lastMusicUpdate = get_time();


    model.currentSoundEffect = no_sound_effect;


    timeThen = get_time();


    do{
        timeNow = get_time();
        timeElapsed = timeNow - timeThen;


        if (input_available()) {
            char inputChar = read_input();
            handle_input(&model, inputChar);
        } else {
            freeze_player(&model);
        }


        if (timeElapsed >= 1) {
            updateModel(&model);


            if(model.currentSoundEffect != no_sound_effect &&
               soundEffectPlayTime < model.currentSoundEffectDuration &&
               !model.isMuted) {
                if(soundEffectPlayTime == 0){
                    model.currentSoundEffect();
                }
                soundEffectPlayTime++;
            } else {
                soundEffectPlayTime = 0;
                model.currentSoundEffect = no_sound_effect;
                model.currentSoundEffect();
            }

            clear_black(backBuffer);
            render(&model, backBuffer);
            (void)_trap_14_wllw((short)0x5,(long)(-1),(long)backBuffer,(short)(-1)) ;
            swapBuffers(&frontBuffer, &backBuffer);
            timeThen = timeNow;
            (void)_trap_14_w((short)0x25) ;

        }


        if (timeNow - lastMusicUpdate >= 14  && !model.isMuted) {
            update_music(&currentNote, &lastNoteTime, timeNow, song, numNotes);
            lastMusicUpdate = timeNow;
        }
    }while (model.game_running == 1 );


    stop_sound();
    (void)_trap_14_wllw((short)0x5,(long)(-1),(long)orig_buffer,(short)(-1)) ;
    return 0;
}
