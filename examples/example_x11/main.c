// Compilation command:
// cc main.c -o example.out -lX11 -lm

#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>   // X11 Window Library / Protocol
#include <stdbool.h>    // Required for: 'bool quit;'

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 X11Setup(pixel* buf, Display** display, Window* root, Window* window, XWindowAttributes* attributes, GC* graphics_context, XImage** image, Atom* message_delete_window) {
    *display = XOpenDisplay(NULL);
    if(!*display) {
        silkLogErr("X11: Couldn't open the default display.");
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Default display opened successfully.");

    *root = DefaultRootWindow(*display);
    if(*root == 0) {
        silkLogErr("X11: Couldn't open the default window root.");
        XCloseDisplay(*display);
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Default root opened successfully.");

    *window = XCreateSimpleWindow(
        *display, 
        *root, 
        0, 
        0, 
        800, 
        600, 
        0, 
        0, 
        0
    );

    if(*window == 0) {
        silkLogErr("X11: Couldn't create an X11 Window.");
        XCloseDisplay(*display);
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Window created successfully.");

    XStoreName(
        *display, 
        *window, 
        "Silk 1.0 - X11 Example"
    );

    XGetWindowAttributes(
        *display, 
        *window, 
        attributes
    );

    *image = XCreateImage(
        *display, 
        attributes->visual, 
        attributes->depth, 
        ZPixmap, 
        0, 
        (char*) buf, 
        SILK_PIXELBUFFER_WIDTH, 
        SILK_PIXELBUFFER_HEIGHT, 
        32, 
        SILK_PIXELBUFFER_WIDTH * sizeof(pixel)
    );

    *graphics_context = XCreateGC(
        *display, 
        *window, 
        0, 
        NULL
    );

    if(*graphics_context == 0) {
        silkLogErr("X11: Couldn't create graphics context.");
        XCloseDisplay(*display);
        return SILK_FAILURE;
    }

    silkLogInfo("X11: Graphics context created successfully.");

    *message_delete_window = XInternAtom(*display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(*display, *window, message_delete_window, 1);

    silkLogInfo("X11: New window protocol: WM_DELETE_WINDOW.");

    XMapWindow(*display, *window);

    return SILK_SUCCESS;
}

i32 X11Blit(pixel* buffer, Display* display, Window* window, GC* graphics_context, XImage* image) {
    if(buffer == NULL) {
        silkLogErr("X11: Passed a NULL parameter: buffer.");

        return SILK_FAILURE;
    } if(display == NULL) {
        silkLogErr("X11: Passed a NULL parameter: display.");

        return SILK_FAILURE;
    } if(window == NULL) {
        silkLogErr("X11: Passed a NULL parameter: window.");

        return SILK_FAILURE;
    } if(graphics_context == NULL) {
        silkLogErr("X11: Passed a NULL parameter: graphics_context.");

        return SILK_FAILURE;
    } if(image == NULL) {
        silkLogErr("X11: Passed a NULL parameter: image.");

        return SILK_FAILURE;
    }

    XPutImage(
        display, 
        *window, 
        *graphics_context, 
        image, 
        0, 
        0, 
        0, 
        0, 
        SILK_PIXELBUFFER_WIDTH, 
        SILK_PIXELBUFFER_HEIGHT
    );

    return SILK_SUCCESS;
}

i32 X11Close(Display* display, XImage* image) {
    if(display == NULL) {
        silkLogErr("X11: Passed a NULL parameter: display.");

        return SILK_FAILURE;
    } if(image == NULL) {
        silkLogErr("X11: Passed a NULL parameter: image.");

        return SILK_FAILURE;
    }

    XCloseDisplay(display);

    return SILK_SUCCESS;
}

i32 main(i32 argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    i32 rectangle_rotation = 0;
    
    const string text = "Hello, X11!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;

    Display* x11_display =                      NULL;
    Window x11_root =                           0;
    Window x11_window =                         0;
    XWindowAttributes x11_window_attributes =   { 0 };
    XImage* x11_render_surface =                NULL;
    GC x11_graphics_context =                   0;
    Atom wm_delete_window =                     0;

    X11Setup(buffer, &x11_display, &x11_root, &x11_window, &x11_window_attributes, &x11_graphics_context, &x11_render_surface, &wm_delete_window);

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

        silkClearPixelBufferColorRegion(buffer, (vec2i) { x11_window_attributes.width, x11_window_attributes.height }, SILK_PIXELBUFFER_WIDTH, 0xffffffff);

        silkDrawPolygon(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH, 
            (vec2i) {
                x11_window_attributes.width / 2,
                x11_window_attributes.height / 2
            }, 
            x11_window_attributes.height / 8, 
            rectangle_rotation++, 
            5, 
            0xffff0000
        );

        silkDrawTextDefault(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            text, 
            (vec2i) { 
                x11_window_attributes.width / 2 - silkMeasureText(text, text_size, text_spacing).x / 2, 
                x11_window_attributes.height / 2 - silkMeasureText(text, text_size, text_spacing).y / 2 + x11_window_attributes.height / 4 
            }, 
            text_size, 
            text_spacing,
            0xff000000
        );

        X11Blit(buffer, x11_display, &x11_window, &x11_graphics_context, x11_render_surface);
    }

    X11Close(x11_display, x11_render_surface);

    return 0;
}