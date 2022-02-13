# Make file for fg on ShivaVG

FILES = test_fg.c fg.c
CFLAGS = -Werror -fmax-errors=2

test_fg: $(FILES)   
	gcc $(CFLAGS) $(FILES) shvg.a libjpeg.a -lm -lX11 -lEGL -lGLESv2 -lXcursor -lwiringPi -otest

