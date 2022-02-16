# FlashGraphics

## FlashTek FlashGraphics Emulation for PI4

FlashGraphics for DOS and DOSX shipped with the Zortech 3.0 compiler. It lived
up to its name being considerably faster than the first OpenGL implementations.
We made use of it for environmental monitoring.

In order to reuse this software I have implemented an emulation of the FlashGraphics
library for the PI4. Ironically the graphics stack is FG->ShivaVGes->OpenGLES3->EGL->X11.
Surprisingly it is as fast as the original

## Build
OpenGLES libraries + headers and OpenVG headers should be installed. A make file for
the test example is included. This renders "Blending In" and then responds to mouse
clicks and keyboard presses.

## Differences
OpenGLes does not support XOR writing. The mode flag is re-purposed to set the alpha blend.

EGL does not support EGL_SINGLE_BUFFER so fg_flush(0) must be called to make the render visible.

The function event_looper() must be called periodically to handle the event queue.
Do not call it in a tight loop as this is detrimental to Linux.

The library contains only the functions I required. It is sufficient to implement a graphics
editor.

## Fonts
Either roll your own with the fg_drawmatrix() or use the example from ShivaVGes.

ChiefEngineer