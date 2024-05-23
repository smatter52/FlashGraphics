/* Joe Huffman */
/* September 18, 1990 */
/* Oxonics 2021 mods for FG->Openvg>Opengl>egl->X11 (Progress ?) */

#ifndef __FG_H
#define __FG_H    1

// lose the DOS stuff
#define _FAR
#define _far
#define _cdecl
#define _near


#if __cplusplus
extern "C" {
#endif

// Debugging LED
#define LedPin 26       // GPIO pin
#ifdef LedPin
void led_on() ;
void led_off() ;
#endif

 
/* Definition of basic coordinate system                */

/************************************
 * Coordinate system (right-handed):
 *
 *           Y2 +
 *              |
 *              |
 *              |
 *           Y1 +-----------+
 *              X1          X2
 *
 * Where:
 *      X1 <= X2
 *      Y1 <= Y2
 */

typedef int fg_coord_t;    /* data type for all coordinates                */

/*****************************
 * Coordinate box.
 *      box[FG_X1] = x coordinate of left edge
 *      box[FG_Y1] = y coordinate of bottom edge
 *      box[FG_X2] = x coordinate of right edge
 *      box[FG_Y2] = y coordinate of top edge
 */

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef fg_coord_t fg_box_t[4];
typedef fg_coord_t _FAR *fg_pbox_t;             /* pointer to a box         */
typedef fg_coord_t const _FAR *fg_const_pbox_t; /* pointer to a const box   */
typedef fg_coord_t fg_line_t[4];
typedef fg_coord_t _FAR *fg_pline_t;            /* pointer to a line        */
typedef fg_coord_t const _FAR *fg_const_pline_t;/* pointer to a const line  */
typedef unsigned short fg_pattern_t[16];        /* fill pattern data        */
typedef unsigned short _FAR *fg_ppattern_t;     /* Pointer to a pattern type*/

#define FG_X1 0
#define FG_Y1 1
#define FG_X2 2
#define FG_Y2 3

// No of cursors supported. Cursor(0) is blank ie. hide cursor
#define MAX_CURSOR 4

/* Midpoint of 2 coordinates    */
#define fg_coord_midpoint(x1,x2)   (((x1) + (x2)) / 2)

/* Determine # of pixels high a box is  */
#define fg_box_height(b)        ((b)[FG_Y2] - (b)[FG_Y1] + 1)

/* Determine # of pixels wide a box is  */
#define fg_box_width(b) ((b)[FG_X2] - (b)[FG_X1] + 1)

/* The number of bytes to allocate for a matrix with a bounding box 'b'. */
#define fg_matrix_size(b) (sizeof(char)*((b)[FG_X2]+1+7)/8*((b)[FG_Y2]+1))

/* The number of pixels in a box 'b'.  Helpful for calculating memory for
a fg_readbox. */
#define fg_box_area(b) (((long)fg_box_width(b))*((long)fg_box_height(b)))

/* Fill in the coordinates of a line. */
#define fg_make_line(l,x1,y1,x2,y2) ((l)[FG_X1]=(x1),(l)[FG_Y1]=(y1),\
(l)[FG_X2]=(x2),(l)[FG_Y2]=(y2))

/* Fill in the coordinates of a box. */
#define fg_make_box(b,x1,y1,x2,y2) ((b)[FG_X1]=(x1),(b)[FG_Y1]=(y1),\
(b)[FG_X2]=(x2),(b)[FG_Y2]=(y2))

/****** Return TRUE if line is horizontal ******/
#define fg_line_horiz(line) ((line)[FG_Y1] == (line)[FG_Y2])

/****** Return TRUE if line is vertical ******/
#define fg_line_vert(line)      ((line)[FG_X1] == (line)[FG_X2])

/* Determine if line is 0 length    */
#define fg_line_zerolength(ln)\
    ((ln)[FG_X1] == (ln)[FG_X2] && (ln)[FG_Y1] == (ln)[FG_Y2])

/* Copy boxes. */
#define fg_box_cpy(to,from) ((fg_pbox_t)fg_line_cpy((to),(from)))

/* Change the definition of a FG_COLOR. */
/* As in 'fg_setcolornum(FG_WHITE, 7);' */
#define fg_setcolornum(old_color,new_num) ((old_color) = (new_num))

#define fg_displaybox  fg.displaybox

/* Change the motion algorithm.  */
/* 0 is linear, 1 is non-linear.  All other values reserved. */
// #define fg_msm_motion(a)  (fg.msm_motion = a)
// void fg_msm_motion(unsigned char) ;

// Rotation values:
#define FG_ROT0   0
#define FG_ROT90  1
#define FG_ROT180 2
#define FG_ROT270 3

/* *************************
 * Mouse button defines.
 * Status of mouse has these bits set if that button is depressed.
 * 1 if down 0 if up.
*/

#define FG_MSM_LEFT   1
#define FG_MSM_RIGHT  2
#define FG_MSM_MIDDLE 4
#define FG_MSM_ALL	 8

typedef struct fg_msm_cursor
{
  char _FAR *matrix;
  fg_box_t box;
  fg_coord_t hot_x, hot_y;
} fg_msm_cursor_t;

typedef struct fg_font
{
  char _far * fontptr;  /* First 128 characters.  */
  char _far * fontptr2; /* Second 128 characters. */
  fg_box_t charbox;
  fg_coord_t baseline;  /* Distance from bottom of char to baseline. */
} fg_font_t;

typedef unsigned char fg_color_t;

typedef unsigned int fg_handle_t;

typedef struct fg_palval      // addition
{
   unsigned char r ;
   unsigned char g ;
   unsigned char b ;
   unsigned char a ;
} fg_palval_t ;

typedef struct fg_save_
{
   unsigned long x ; unsigned long y ;
   unsigned long w ; unsigned long h ;
   unsigned char *data ;
} fg_save_t ;

typedef struct fg_keypress
{ unsigned int cnt ;
  unsigned int keycode ;
  unsigned int keysym ;
} fg_keypress_t ;

typedef struct fg_buttonpress
{ unsigned int cntl ;
  unsigned int cntm ;
  unsigned int cntr ;
  unsigned int bmap ;
  unsigned int px ;
  unsigned int py ;
} fg_buttonpress_t ;

typedef struct fg_motionnotify
{ unsigned int cnt ;
  unsigned int bmap ;
  unsigned int px ;
  unsigned int py ;
} fg_motionnotify_t ;

typedef struct fg_line_param
{ float array[4] ;
  int cnt ;
} fg_line_param_t ;

#define MAX_SAVE 10

/* Defines for the type of display encountered  */
#define FG_NULL     0    /* all graphics are routed to bit bucket        */

/* The following correspond to BIOS video modes:                             */
#define FG_VGA12        0x12 /* IBM VGA in 640*480, 16 colors                */
#define FG_VESA2         0x102 /* VESA mode 0x102, 800 x 600, 16 colors.     */
#define FG_VESA3         0x103 /* VESA mode 0x103, 800 x 600, 256 colors.    */

/* Used for filling outlines of pixels, see fg_outlinefill().           */
#define FG_FILL_ON_RIGHT 1  /* Don't change these without careful       */
#define FG_FILL_ON_LEFT  0  /* consideration of the source code. See    */
                            /* the static function delete_excess.       */

// Use fg_init to set the display window size in lieu of setting
// a Bios video mode.
// Colour palette is 256 of R:8 G:8 B:8 Alpha:8

// Event looper needs to be regularily to handle X11 event queue
void event_looper() ;

// Function protoypes as declared in code
int fg_init(int screen_x, int screen_y) ;
void fg_term(void) ;
void fg_msm_flush() ;
void fg_msm_showcursor(int index) ;
void fg_msm_hidecursor(void) ;
void fg_msm_term(void) ;
void fg_msm_setcursor(fg_msm_cursor_t *fcur, fg_color_t colf, fg_color_t colb);
void fg_msm_cursorfree(unsigned int index) ;
void fg_msm_cursorfreeall(void) ;
unsigned int fg_msm_getpress(unsigned int *but_num, fg_coord_t *x_p,
                             fg_coord_t *y_p) ;
unsigned int fg_msm_getstatus(fg_coord_t *x_p, fg_coord_t *y_p) ;
int _bios_keybrd(int flag) ;    // read key press

void fg_drawarc (fg_color_t,int,int,fg_coord_t,fg_coord_t,
                  fg_coord_t,int,int,fg_const_pbox_t);
void fg_drawline(fg_color_t,int,int,int,fg_const_pline_t);
void fg_drawlinep(fg_color_t,int,int,int,fg_const_pline_t);
void fg_drawmatrix  (fg_color_t,int,int,int,fg_coord_t,
                  fg_coord_t,unsigned char *, fg_const_pbox_t,fg_const_pbox_t);
void fg_fillbox(fg_color_t, int, int, fg_const_pbox_t);
void fg_flush(int flag);
void fg_putc(fg_color_t,int,int,int,fg_coord_t,
                  fg_coord_t,char,fg_const_pbox_t);
void fg_readbox(fg_const_pbox_t, fg_color_t _FAR *);
void fg_setlinepattern(int, int);
void fg_writebox(fg_const_pbox_t, const fg_color_t _FAR *);

void fg_free(void _FAR *p);
fg_handle_t fg_save(fg_const_pbox_t);
void fg_restore (fg_handle_t);
void fg_remove(fg_handle_t indxp);

void fg_drawthickline(fg_color_t,int,int,int,fg_const_pline_t,
                      fg_const_pbox_t,int);
void fg_msm_setcurpos(fg_coord_t,fg_coord_t);
void fg_getpalette(fg_color_t color_num, fg_color_t  *red,
                    fg_color_t  *green, fg_color_t  *blue);
void fg_drawellipse(fg_color_t,int,int,fg_coord_t,fg_coord_t,
                    fg_coord_t, fg_coord_t,int,int,fg_const_pbox_t);
void fg_fill(fg_coord_t,fg_coord_t,fg_color_t,fg_color_t);
void fg_fillpattern(fg_coord_t,fg_coord_t,fg_color_t,fg_color_t,int);
void fg_setpalette(fg_color_t color_num, fg_color_t red,
                     fg_color_t green, fg_color_t blue, fg_color_t alpha);
void fg_drawroundbox(fg_color_t col,int mode, int mask, int linetype,
                 fg_const_pbox_t box, int rw, int rh) ;
void fg_fillroundbox(fg_color_t col,int mode, int mask, fg_const_pbox_t box,
                     int rw, int rh) ;
void fg_fillellipse(fg_color_t col,int mode, int mask, fg_coord_t x ,fg_coord_t y,
                    fg_coord_t xradius, fg_coord_t yradius, int startangle,
                    int endangle, fg_const_pbox_t box) ;
void fg_drawlineclip(fg_color_t col, int mode, int mask, int linetype,
                     fg_const_pline_t line, fg_const_pbox_t clip) ;
void fg_drawline(fg_color_t col, int mode, int mask, int linetype,
                     fg_const_pline_t line) ;
fg_color_t fg_readdot(fg_coord_t x, fg_coord_t y) ;
void fg_drawbox (fg_color_t, int, int, int, fg_const_pbox_t, fg_const_pbox_t);

/* ************************************************* */
/* Collect global variables into a single structure. */
struct fg_state
{

#define FG_LINE_MAX     12
  unsigned short int linetype[FG_LINE_MAX];
#define FG_COLOR_MAX    256
  fg_palval_t palval_tab[FG_COLOR_MAX];   // The color palette
  fg_keypress_t key_press ;                // Event_loop return data
  fg_buttonpress_t button_press ;
  fg_motionnotify_t motion_notify ;
  fg_box_t charbox;
  fg_box_t displaybox;
  long ncolormap;
  int nsimulcolor;
//  int numpages;
  float aspect_ratio;   // screen aspect ratio
  char text_rows, attribute, text_mode;

#define FG_FILL_SOLID         0
#define FG_FILL_BSLASH        1
#define FG_FILL_SLASH         2
#define FG_FILL_HATCH         3
#define FG_FILL_LINE          4
#define FG_FILL_THICK_X       5
#define FG_FILL_THIN_X        6
#define FG_FILL_SCALE         7
#define FG_FILL_WIDEDOT       8
#define FG_FILL_CLOSEDOT      9
#define FG_FILL_DIAMOND       10
#define FG_FILL_USER_DEFINED  11
#define FG_FILL_PATTERN_MAX   12

fg_pattern_t filltype[FG_FILL_PATTERN_MAX];


};  // end of fg_state  **



// extern struct fg_state fg;

// Not currently suported
/*
void fg_drawdot (fg_color_t,int,int,fg_coord_t,fg_coord_t);
void fg_blit(fg_const_pbox_t, fg_coord_t, fg_coord_t,int,int);
unsigned _cdecl _FAR fg_msm_getrelease(unsigned _FAR *,fg_coord_t _FAR *,
               fg_coord_t _FAR *);
void _cdecl _FAR fg_msm_setarea(fg_const_pbox_t);
void _cdecl _FAR fg_msm_setratio(unsigned,unsigned);

int _cdecl _FAR fg_box_enclose(fg_const_pbox_t b1, fg_const_pbox_t b2);
int _cdecl _FAR fg_pt_inbox(fg_const_pbox_t clip,fg_coord_t x,fg_coord_t y);
int _cdecl _FAR fg_getfillside(const fg_coord_t _FAR *p,unsigned int vertices);
unsigned _cdecl _FAR fg_linepixels (fg_const_pline_t line);
fg_pline_t _cdecl _FAR fg_line_cpy(fg_pline_t to, fg_const_pline_t from);
int _cdecl _FAR fg_lineclip(fg_const_pbox_t clip, fg_const_pline_t fline,
            fg_pline_t lin);
void _cdecl _FAR fg_setenv_variable (const char _FAR *new_string);
void _cdecl _FAR fg_fillboxdissolve(fg_color_t color, int mode, int mask,
                    fg_const_pbox_t box, unsigned int count,
                    int (_cdecl _FAR *func_p)(void));
void _cdecl _FAR fg_writeboxdissolve(fg_const_pbox_t box,
                    const fg_color_t _FAR *p, unsigned int count,
                    int (_cdecl _FAR *func_p)(void));
void _cdecl _FAR fg_fillboxpattern(fg_color_t color, int mode, int mask,
                       fg_const_pbox_t b,int pattern);
void _cdecl _FAR fg_drawdotpattern(fg_color_t color,int mode,int mask,
                  fg_coord_t x, fg_coord_t y, int pattern);
int _cdecl _FAR fg_fillpolygonpattern (fg_color_t color, int mode, int mask,
                  unsigned int vertices, const fg_coord_t _FAR *polygon,
                  fg_const_pbox_t clipbox,int pattern);
int _cdecl _FAR fg_fillpolygon (fg_color_t color, int mode, int mask,
                  unsigned int vertices, const fg_coord_t _FAR *polygon,
                  fg_const_pbox_t clipbox);
void _cdecl _FAR fg_free_handle (fg_handle_t);
void _cdecl _FAR fg_setfillpattern(int, fg_ppattern_t);
void _cdecl _FAR fg_drawlinepattern(fg_color_t,int,int,int,fg_const_pline_t);
void _cdecl _FAR fg_drawlineclip (fg_color_t color, int mode, int mask, 
                  int fg_line_type, fg_const_pline_t line, 
                  fg_const_pbox_t clip);
void _cdecl _FAR fg_drawlinepatternclip (fg_color_t color, int mode, int mask,
                  int pattern, fg_const_pline_t line, fg_const_pbox_t clip);

void _cdecl _FAR fg_drawpolygon (fg_color_t color, int mode, int mask, int
                  line_type, unsigned int vertices, const fg_coord_t _FAR 
                  *polygon, fg_const_pbox_t clipbox);
void _cdecl _FAR fg_filloutline (fg_color_t color, int mode, int mask, 
                  const fg_coord_t _FAR *out_line, fg_coord_t _FAR *buffer,
                  unsigned int pixels, int fill_side, fg_const_pbox_t clipbox);
void _cdecl _FAR fg_filloutlinepattern(fg_color_t color, int mode, int mask, 
                  const fg_coord_t _FAR *out_line, fg_coord_t _FAR *buffer,
                  unsigned int pixels, int fill_side, fg_const_pbox_t clipbox,
                  int pattern);
void _cdecl _FAR fg_puts (fg_color_t,int,int,int,fg_coord_t,fg_coord_t,
                  char _FAR *, fg_const_pbox_t);
void _cdecl _FAR fg_adjustxy (int, int, fg_coord_t _FAR *, fg_coord_t _FAR *,
                  fg_const_pbox_t);
void _cdecl _FAR fg_traverseline (int line_type, fg_const_pline_t ln_ptr, 
                  fg_coord_t _FAR *pt_pairs);
int _cdecl _FAR fg_boxclip(fg_const_pbox_t clip, fg_const_pbox_t box_in,
                 fg_pline_t box_out);
*/

/* Writing modes. Since XOR is not supported this modifies the alpha blend */
#define FG_MODE_XOR   125
#define FG_MODE_SET   255

/* Line types   */
#define    FG_LINE_SOLID         0
#define    FG_LINE_LONG_DASH     1
#define    FG_LINE_MEDIUM_DOTTED 2
#define    FG_LINE_DASH_DOTTED   3
#define    FG_LINE_MEDIUM_DASHED 4
#define    FG_LINE_DASH_W_2_DOTS 5
#define    FG_LINE_SHORT_DASH    6
#define    FG_LINE_DENSE_DOTTED  7
#define    FG_LINE_SPARSE_DOTTED 8
#define    FG_LINE_USER_DEFINED  9
#define    FG_LINE_FG_RESERVED1  10
#define    FG_LINE_FG_RESERVED2  11

/* Values for color     */
#define FG_BLACK        fg.color[0]
#define FG_BLUE         fg.color[1]
#define FG_GREEN        fg.color[2]
#define FG_CYAN         fg.color[3]
/* Cyan is the same as BLUE_GREEN. */
#define FG_BLUE_GREEN   fg.color[3]
#define FG_RED          fg.color[4]
#define FG_MAGENTA      fg.color[5]
/* Purple is the same as magenta. */
#define FG_PURPLE       fg.color[5]
#define FG_YELLOW       fg.color[6]
#define FG_WHITE        fg.color[7]



#if __cplusplus
}
#endif

#endif  /* ifndef __FG_H */

