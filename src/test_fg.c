#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>

#include <VG/openvg.h>
#include <X11/Xcursor/Xcursor.h>
#include "shGLESinit.h"
#include "shContext.h"
#include "shVectors.h"
#include "shPaint.h"
#include "fg.h"
#include "shapes.h"

VGPath line;
VGPath polyOpen;
VGPath polyClosed;
VGPath rect;
VGPath rectRound;
VGPath ellipse;
VGPath arcOpen;
VGPath arcChord;
VGPath arcPie;
VGPaint stroke ;

extern  Display  *x_display;
extern  Window win ;
extern EGLDisplay  egl_display;
extern EGLContext  egl_context;
extern EGLSurface  egl_surface;
extern VGContext   *vg_context;
extern int exit_flag ;
extern struct fg_state fg;

static char cross_matrix[45] =
  {
       0x00,0x80,0x00, /*         X         */
       0x01,0xc0,0x00, /*         X         */
       0x03,0xe0,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x00,0x00, /*                   */
       0xfe,0x3f,0x80, /* XXXXXXX   XXXXXXX */
       0x00,0x00,0x00, /*                   */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
       0x00,0x80,0x00, /*         X         */
  };


static fg_msm_cursor_t crosshair = {cross_matrix,{0,0,17,14}, 8, 7};

static char arrow_matrix[15] =
  {
       0x80,  /* X        */
       0xc0,  /* XX       */
       0xe0,  /* XXX      */
       0xf0,  /* XXXX     */
       0xf8,  /* XXXXX    */
       0xfc,  /* XXXXXX   */
       0xfe,  /* XXXXXXX  */
       0xff,  /* XXXXXXXX */
       0xfc,  /* XXXXXX   */
       0xf8,  /* XXXXX    */
       0xf8,  /* XXXXX    */
       0xcc,  /* XX  XX   */
       0x8c,  /* X   XX   */
       0x06,  /*      XX  */
       0x06,  /*      XX  */
  };
  static fg_msm_cursor_t arrow = {arrow_matrix,{0,0,7,14}, 0, 0};

static struct fg_msm_cursor *msm_cur;

/* ************************************************************ */
VGPath testCreatePath()
{
   return vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F,
                       1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
}

void render()
{
//   glFlush() ;
   eglSwapBuffers ( egl_display, egl_surface );  // buffer to the screen
}


/* ************************************************************ */
void display()
{
  VGfloat black[] = { 0, 0, 0, 1 };

  vgSetfv(VG_CLEAR_COLOR, 4, black);
  vgClear(0, 0, vg_context->surfaceWidth, vg_context->surfaceHeight);

  fg_line_t line = {0,0,640,480} ;
  fg_box_t clip =  {10, 10, 50, 50} ;
  fg_box_t box1 = {10, 10, 400, 150} ;
  fg_box_t box2 = {10, 160, 400, 300} ;
  fg_box_t box3 = {200, 160, 500, 470} ;
  msm_cur = &crosshair ;
  struct timespec start, finish ;
  long mss, msf ;
  clock_gettime(CLOCK_REALTIME, &start);

//  StrokeWidth((float)1) ;
  fg_fillbox(0,FG_MODE_SET,~0, box2) ;
  fg_drawthickline(0,FG_MODE_SET,~0,FG_LINE_SOLID,line,fg.displaybox, 1);
  fg_drawmatrix(0, FG_MODE_SET, ~0, 0, 80, 80, msm_cur->matrix,
                 msm_cur->box, fg.displaybox);

  fg_fillbox(1,FG_MODE_XOR,~0, box3) ;
  fg_flush(0) ; // Show it

  clock_gettime(CLOCK_REALTIME, &finish);
  mss = round(start.tv_nsec / 1.0e6);
  msf = round(finish.tv_nsec / 1.0e6);
  fprintf(stderr, "Duration: %d ms\n", msf - mss) ;
}


int main(int argc, char **argv)
{  bool quit = false;
   fg_coord_t px, py ;
   unsigned int stat ;


   printf("Fg Test\n");

   SetWindowName("FlashGraphics") ;
   fg_init(640, 480) ;

// pal 0 is white
   fg_setpalette(0, 255, 255, 255, 255);
// pal 1 is green
   fg_setpalette(1, 0, 155, 0, 255);

   fg_msm_setcursor(&arrow, 0, 0) ;
   fg_msm_showcursor(0) ;
   fg_msm_setcurpos(vg_context->surfaceWidth/2, vg_context->surfaceHeight/2) ;

  display() ;

  int key ;
  while (exit_flag == 0)
   {
//     event_looper() ;   Calls now in fg library

     int but_num = FG_MSM_LEFT ;
     if ((stat = fg_msm_getpress(&but_num,&px, &py)) != 0)
         printf("#%d %d %d\n", stat, px, py) ;
     if (_bios_keybrd(1) != 0)
      {
       key = _bios_keybrd(0) ;
       printf("key: %x\n", key) ;
      }
     usleep(50000) ;
   }

  fg_term() ;

  return 0;
}
