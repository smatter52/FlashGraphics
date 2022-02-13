/* Graphics editor - piced - include file "icon.h" */

#ifdef MEMDEBUG
 #include "mem.h"
#else 
 #include "no_mem.h"
#endif

typedef unsigned long ulong;

#define XMAX 640
#define YMAX 480


#define BLOCK_STR   "Û"  /* block string */
#define DEL         8       /* delete char */
#define CSIZE       1       /* normal character height */

#define KEY_RETURN        0x000d
#define KEY_LEFT          0x4b00
#define KEY_RIGHT         0x4d00
#define KEY_BACK          0x0e08
#define KEY_DEL           0x5300
#define KEY_HOME          0x4700
#define KEY_END           0x4f00
#define KEY_ESC           0x011b
#define KEY_UP            0x4800
#define KEY_DOWN          0x5000
#define KEY_PG_UP         0x4900
#define KEY_PG_DN         0x5100
#define KEY_INS           0x5200
#define KEY_RIGHT_MOUSE   0x0002
#define KEY_LEFT_MOUSE    0x0001
#define KEY_F1            0x3B00
#define KEY_F2            0x3C00
#define KEY_F3            0x3D00
#define KEY_F4            0x3E00
#define KEY_F5            0x3F00
#define KEY_F6            0x4000
#define KEY_F7            0x4100
#define KEY_F8            0x4200
#define KEY_F9            0x4300
#define KEY_F10           0x4400

#define MSM_CURSORS 3            /* number of mouse cursors */
#define MAX_ICON_GRP (YMAX/12)   /* max number of gels in an Icon group */

/* Graphic element structure */

#define gel_rect     0
#define gel_circle   1
#define gel_line     2
#define gel_vline    3
#define gel_hline    4
#define gel_text     5
#define gel_fill     6
#define gel_bar      7
#define gel_mouse    8
#define gel_input    9
#define gel_menu     10
#define gel_put      11
#define gel_plot     12
#define gel_password 13

struct umenu { int  x,y,x1,y1;     /* user pop up menu structure */
               char *text[20];
             };

struct plot  { int x,y,x1,y1,time,index;   /* EMS plot data 1 minute */
               char unit[10] ;
               struct bar { float val;
                            int  stat;
                          } bar[60];
             };

struct font
{
           char file[15];          /* font file name */
            int Width,             /* Width of each Character */
                Height;            /* Height of each Character */
           char *font_set;         /* a pointer to the Character set */
};

struct gel {  /* structure for graphic element linked list */
     unsigned char  type;            /* type of element */
              int x,y,x1,y1;       /* coordinates of element */
     unsigned char  col;             /* colour of element */
     unsigned char  fill;            /* filled area flag 1 = filled */
     unsigned char  flag;            /* flag for delete and undelete */
              int   icon;            /* icon group no.,  0=not an icon */
              int   state;           /* state for colour mapping */
     unsigned char  font;            /* font number of text or width if line */
             char *text;           /* text for element */
     struct umenu *umenu;          /* pointer to user_menu icon structure */
     struct plot  *plot;           /* pointer to Ems plot data */
       struct gel *next,           /* pointer to next graphic element */
                  *prev;           /* pointer to previous gel in list */
             char *d_name[3];      /* domain name */
              int index[3];        /* domain index for icon use */
             char mapping[17]  ;     /* string for mapping functions */
             char *scan;           /* sscanf conversion string */
           };

struct gel *mk_gel();


/* Pull down Menu structure */

struct pdm { char *title;                 /* title of menu */
              int x,y,                    /* x,y of menu */
                  no;                     /* no of items in a menu */
           struct menu { char *text;      /* each menu item name */
                         int  (*func)();  /* pointer to function called */
                         int  key;        /* key code for keyboard shortcut */
                       } menu[20];        /* max of 20 menu items */
           };
