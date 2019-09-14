#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "ugeneloader.h"

/* if an image loader needs to have our display and screen, it will get
 * them from here.  this is done to keep most of the image routines
 * clean
 */

Display      *Disp= NULL;
int           Scrn= 0;

int main2() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}