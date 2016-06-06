#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <unistd.h>

void drawSplashScreen(int *isDownloaded)
{
    Display                 *display;
    Visual                  *visual;
    int                     depth;
    int                     text_x;
    int                     text_y;
    XSetWindowAttributes    frame_attributes;
    Window                  frame_window;
    XFontStruct             *fontinfo;
    XGCValues               gr_values;
    GC                      graphical_context;
    XEvent                  event;
    char                    hello_string1[] = "Unipro UGENE installer preparing   ";
    char                    hello_string2[] = "Unipro UGENE installer preparing.  ";
    char                    hello_string3[] = "Unipro UGENE installer preparing.. ";
    char                    hello_string4[] = "Unipro UGENE installer preparing...";
    int                     hello_string_length = strlen(hello_string1);

    display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    visual = DefaultVisual(display, screen);
    depth  = DefaultDepth(display, screen);

    frame_attributes.background_pixel = XWhitePixel(display, screen);
    frame_attributes.border_pixel = XBlackPixel(display, screen);
    /* create the application window */
    int width = 500;
    int height = 50;
    int x = DisplayWidth(display,screen)/2-width/2;
    int y = DisplayHeight(display,screen)/2-height/2;
    frame_window = XCreateWindow(display, XRootWindow(display, screen),
                                 x, y, width, height, 5, depth,
                                 InputOutput, visual, CWBackPixel,
                                 &frame_attributes);
    Atom type = XInternAtom(display,"_NET_WM_WINDOW_TYPE", False);
    Atom value = XInternAtom(display,"_NET_WM_WINDOW_TYPE_SPLASH", False);
    XChangeProperty(display, frame_window, type, XA_ATOM, 32, PropModeReplace, reinterpret_cast<unsigned char*>(&value), 1);
    /* register interest in the delete window message */
    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, frame_window, &wmDeleteMessage, 1);

    XStoreName(display, frame_window, "Unipro UGENE installer preparing...");
    XSelectInput(display, frame_window, ExposureMask | StructureNotifyMask);

    fontinfo = XLoadQueryFont(display, "10x20");
    gr_values.font = fontinfo->fid;
    gr_values.foreground = XBlackPixel(display, 0);
    graphical_context = XCreateGC(display, frame_window, 
                                  GCFont+GCForeground, &gr_values);
    XMapWindow(display, frame_window);
    for(;;) {
            XNextEvent(display, &event);
            if (event.type == MapNotify)
                  break;
      }
    for(;;) {
        XNextEvent(display, (XEvent *)&event);
        if (event.type == Expose) { // Draw first time
            XWindowAttributes window_attributes;
            int font_direction, font_ascent, font_descent;
            XCharStruct text_structure;
            XTextExtents(fontinfo, hello_string1, hello_string_length, 
                         &font_direction, &font_ascent, &font_descent, 
                         &text_structure);
            XGetWindowAttributes(display, frame_window, &window_attributes);
            text_x = (window_attributes.width - text_structure.width)/2;
            text_y = (window_attributes.height + (text_structure.ascent+text_structure.descent))/2;
            XDrawString(display, frame_window, graphical_context,
                        text_x, text_y, hello_string1, hello_string_length);
            XFlush(display);
            break;
        }
    }
    int i=0;
    for(;;) {
        XWindowAttributes window_attributes;
        int font_direction, font_ascent, font_descent;
        XCharStruct text_structure;
        XTextExtents(fontinfo, hello_string1, hello_string_length, 
                     &font_direction, &font_ascent, &font_descent, 
                     &text_structure);
        XGetWindowAttributes(display, frame_window, &window_attributes);
        text_x = (window_attributes.width - text_structure.width)/2;
        text_y = (window_attributes.height + (text_structure.ascent+text_structure.descent))/2;
        if (i==3){
            XDrawString(display, frame_window, graphical_context,
                    text_x, text_y, hello_string4, hello_string_length);
            i=0;
            XFlush(display);
            usleep(500000);
        }
        if (i==2){
            XDrawString(display, frame_window, graphical_context,
                    text_x, text_y, hello_string3, hello_string_length);
            XFlush(display);
            usleep(500000);
        }
        if (i==1){
            XDrawString(display, frame_window, graphical_context,
                    text_x, text_y, hello_string2, hello_string_length);
            XFlush(display);
            usleep(500000);
        }
        if (i==0){
            XClearArea(display, frame_window, text_x, text_y - (text_structure.ascent+text_structure.descent), text_structure.width, text_structure.ascent+text_structure.descent, False);
            XDrawString(display, frame_window, graphical_context,
                    text_x, text_y, hello_string1, hello_string_length);
            XFlush(display);
            usleep(500000);
        }
        i++;
        //printf("%d, %d Hi, splash screen.\n",*isDownloaded,i);
        if(*isDownloaded==1)
            break;
    }
    XFlush(display);
    XUnmapWindow(display,frame_window);
    XFlush(display);
    /* close connection to server */
    XCloseDisplay(display);
}


