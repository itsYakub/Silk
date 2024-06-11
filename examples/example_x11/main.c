// Compilation command:
// cc main.c -o example.out -lX11

#include <X11/Xlib.h>   // X11 Window Library / Protocol
#include <stdbool.h>    // Required for: 'bool quit;'

#define SILK_IMPLEMENTATION
#include "../../silk.h"


int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    Display* x11_display = XOpenDisplay(NULL);
    if(!x11_display) {
        silkLogErr("X11: Couldn't open the default display.");
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Default display opened successfully.");

    Window x11_root = DefaultRootWindow(x11_display);
    if(x11_root == 0) {
        silkLogErr("X11: Couldn't open the default window root.");
        XCloseDisplay(x11_display);
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Default root opened successfully.");

    Window x11_window = XCreateSimpleWindow(
        x11_display, 
        x11_root, 
        0, 
        0, 
        800, 
        600, 
        0, 
        0, 
        0
    );

    if(x11_window == 0) {
        silkLogErr("X11: Couldn't create an X11 Window.");
        XCloseDisplay(x11_display);
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Window created successfully.");

    XStoreName(
        x11_display, 
        x11_window, 
        "Silk 1.0 - X11 Example"
    );

    XWindowAttributes x11_window_attributes = { 0 };
    XGetWindowAttributes(
        x11_display, 
        x11_window, 
        &x11_window_attributes
    );

    XImage* x11_render_surface = XCreateImage(
        x11_display, 
        x11_window_attributes.visual, 
        x11_window_attributes.depth, 
        ZPixmap, 
        0, 
        (char*) buffer, 
        SILK_PIXELBUFFER_WIDTH, 
        SILK_PIXELBUFFER_HEIGHT, 
        32, 
        SILK_PIXELBUFFER_WIDTH * sizeof(pixel)
    );

    GC x11_graphics_context = XCreateGC(
        x11_display, 
        x11_window, 
        0, 
        NULL
    );

    if(x11_graphics_context == 0) {
        silkLogErr("X11: Couldn't create graphics context.");
        XCloseDisplay(x11_display);
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Graphics context created successfully.");

    XMapWindow(x11_display, x11_window);

    Atom wm_delete_window = XInternAtom(x11_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(x11_display, x11_window, &wm_delete_window, 1);

    silkLogInfo("X11: New window protocol: WM_DELETE_WINDOW.");

    bool quit = false;
    while(!quit) {
        while(XPending(x11_display) > 0) {
            XEvent x11_event = { 0 };
            XNextEvent(x11_display, &x11_event);

            switch (x11_event.type) {
                case ClientMessage: {
                    if(x11_event.xclient.data.l[0] == wm_delete_window) {
                        quit = true;
                    }
                } break;
            }
        }

        XGetWindowAttributes(
            x11_display, 
            x11_window, 
            &x11_window_attributes
        );

        silkClearPixelBufferColorRegion(
            buffer, 
            (vec2i) {
                x11_window_attributes.width,
                x11_window_attributes.height
            }, 
            0xfffffff
        );

        silkDrawCircle(
            buffer, 
            (vec2i) {
                x11_window_attributes.width / 2.0f,
                x11_window_attributes.height / 2.0f
            },
            128,
            0xff0000ff
        );

        XPutImage(
            x11_display, 
            x11_window, 
            x11_graphics_context, 
            x11_render_surface, 
            0, 
            0, 
            0, 
            0, 
            SILK_PIXELBUFFER_WIDTH, 
            SILK_PIXELBUFFER_HEIGHT
        );
    }

    XCloseDisplay(x11_display);

    return 0;
}