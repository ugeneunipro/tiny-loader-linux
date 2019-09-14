//
// Created by ichebyki on 9/14/19.
//
#ifndef UNTITLED2_UGENELOADER_H
#define UNTITLED2_UGENELOADER_H

#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "image.h"

#define VERSION      "1"
#define PATCHLEVEL   "1"
#define AUTHOR_EMAIL "ichebykin@unipro.ru"

#define ProgramName "ugeneloader"


/* This struct holds the X-client side bits for a rendered image.
 */

typedef struct {
    Display  *disp;       /* destination display */
    int       scrn;       /* destination screen */
    int       depth;      /* depth of drawable we want/have */
    Drawable  drawable;   /* drawable to send image to */
    Pixel     foreground; /* foreground and background pixels for mono images */
    Pixel     background;
    Colormap  cmap;       /* colormap used for image */
    GC        gc;         /* cached gc for sending image */
    XImage   *ximage;     /* ximage structure */
} XImageInfo;

char *nameOfVisualClass(int);

void        sendXImage(); /* send.c */
XImageInfo *imageToXImage();
Pixmap      ximageToPixmap();
void        freeXImage();

char *expandPath(); /* path.c */
int   findImage();

/* imagetypes.c */
Image *loadImage(char *name, unsigned int verbose);
char imageInWindow(Display *disp, int scrn, Image *image, int argc, char *argv[], unsigned int verbose);


#endif //UNTITLED2_UGENELOADER_H
