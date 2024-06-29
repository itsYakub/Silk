// Compilation command:
// $ mkdir bin/
// $ cd bin/
// $ cmake ..
// $ cmake --build .

#include <stdbool.h>
#include <string.h>

#include "bin/_deps/sdl2-src/include/SDL.h"
#include "bin/_deps/sdl2-src/include/SDL_events.h"
#include "bin/_deps/sdl2-src/include/SDL_pixels.h"
#include "bin/_deps/sdl2-src/include/SDL_render.h"
#include "bin/_deps/sdl2-src/include/SDL_timer.h"
#include "bin/_deps/sdl2-src/include/SDL_video.h"

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 SDLSetup(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture) {
if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        silkLogErr("SDL: Couldn't initialize SDL.");
        return SILK_FAILURE;
    }

    silkLogInfo("SDL: Platform initialized successfully.");

    *window = SDL_CreateWindow(
        "Silk 1.0 - SDL Example", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        800, 
        600, 
        0
    );

    if(window == NULL) {
        silkLogErr("SDL: Couldn't create an SDL Window.");
        SDL_Quit();
        return SILK_FAILURE;
    }

    silkLogInfo("SDL: Window created successfully.");

    *renderer = SDL_CreateRenderer(
        *window, 
        0, 
        0
    );

    if(*renderer == NULL) {
        silkLogErr("SDL: Couldn't create an SDL Renderer.");
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return SILK_FAILURE;
    }

    silkLogInfo("SDL: Renderer created successfully.");

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    *texture = SDL_CreateTexture(
        *renderer, 
        SDL_PIXELFORMAT_ABGR8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        800, 
        600
    );

#elif defined (SILK_BYTEORDER_BIG_ENDIAN)

    *texture = SDL_CreateTexture(
        *renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        800, 
        600
    );

#endif

    if(texture == NULL) {
        silkLogErr("SDL: Couldn't create an SDL Texture.");
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return SILK_FAILURE;
    }

    silkLogInfo("SDL: Texture created successfully.");

    return SILK_SUCCESS;
}

i32 SDLBlit(pixel* buffer, SDL_Renderer* renderer, SDL_Texture* texture) {
    if(buffer == NULL) {
        silkLogErr("SDL: Passed a NULL parameter: buffer.");

        return SILK_FAILURE;
    } if(renderer == NULL) {
        silkLogErr("SDL: Passed a NULL parameter: renderer.");

        return SILK_FAILURE;
    } if(texture == NULL) {
        silkLogErr("SDL: Passed a NULL parameter: texture.");

        return SILK_FAILURE;
    }

    vec2i sdl_renderer_size = { 0 };
    SDL_GetRendererOutputSize(renderer, &sdl_renderer_size.x, &sdl_renderer_size.y);

    SDL_Rect source_rect = {
        0,
        0,
        SILK_PIXELBUFFER_WIDTH,
        SILK_PIXELBUFFER_HEIGHT
    };

    SDL_Rect destination_rect = {
        0,
        0,
        sdl_renderer_size.x,
        sdl_renderer_size.y
    };

    SDL_UpdateTexture(
        texture,
        &source_rect,
        buffer, 
        SILK_PIXELBUFFER_WIDTH * sizeof(pixel)
    );

    SDL_RenderCopyEx(
        renderer, 
        texture, 
        &source_rect, 
        &destination_rect,
        0.0,
        NULL,
        SDL_FLIP_NONE
    );

    SDL_RenderPresent(renderer);

    return SILK_SUCCESS;
}

i32 SDLClose(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) {
    if(window == NULL) {
        silkLogErr("SDL: Passed a NULL parameter: window.");

        return SILK_FAILURE;
    } if(renderer == NULL) {
        silkLogErr("SDL: Passed a NULL parameter: renderer.");

        return SILK_FAILURE;
    } if(texture == NULL) {
        silkLogErr("SDL: Passed a NULL parameter: texture.");

        return SILK_FAILURE;
    }

    SDL_DestroyTexture(texture);    silkLogInfo("SDL: Texture unloaded successfully.");
    SDL_DestroyRenderer(renderer);  silkLogInfo("SDL: Renderer unloaded successfully.");
    SDL_DestroyWindow(window);      silkLogInfo("SDL: Window unloaded successfully.");
    SDL_Quit();                     silkLogInfo("SDL: Closing.");

    return SILK_SUCCESS;
}

int main(int argc, const string argv[]) {
    // Silk's pixel buffer
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    i32 rectangle_rotation = 0;
    
    const string text = "Hello, SDL2!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;


    // SDL components
    SDL_Window*     sdl_window;
    SDL_Renderer*   sdl_renderer;
    SDL_Texture*    sdl_texture;

    vec2i           sdl_window_size = { 0 };

    // Setting-up SDL components
    SDLSetup(
        &sdl_window,
        &sdl_renderer,
        &sdl_texture
    );

    silkLogAlphaBlendStatus();

    // Update-Render loop
    bool exit = false;
    while(!exit) { 
        // Dispatching window events
        SDL_Event event = { 0 };
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    exit = true;
                } break;
            }
        }

        SDL_GetWindowSize(sdl_window, &sdl_window_size.x, &sdl_window_size.y);

        // Clearing the silk's pixel buffer
        silkClearPixelBufferColorRegion(buffer, sdl_window_size, SILK_PIXELBUFFER_WIDTH, 0xffffffff);
        
        silkDrawCircle(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH, 
            (vec2i) {
                sdl_window_size.x / 2,
                sdl_window_size.y / 2
            }, 
            sdl_window_size.y / 8, 
            0xff0000ff
        );

        silkDrawTextDefault(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            text, 
            (vec2i) { 
                sdl_window_size.x / 2 - silkMeasureText(text, text_size, text_spacing).x / 2, 
                sdl_window_size.y / 2 - silkMeasureText(text, text_size, text_spacing).y / 2 + sdl_window_size.y / 4 
            }, 
            text_size, 
            text_spacing,
            0xff000000
        );

        // Displaying the graphics on the window
        SDLBlit(
            buffer, 
            sdl_renderer, 
            sdl_texture
        );
    }

    // Closing SDL
    SDLClose(
        sdl_window, 
        sdl_renderer, 
        sdl_texture
    );

    return 0;
}