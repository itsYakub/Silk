// Compilation command (on linux):
// cc main.c -o example.out -lm
//
// Compilation command (on windows):
// cc main.c -o example.exe -lm
//
// Compilation command (on macOS):
// cc main.c -o example.out -lm

#include "your_backend_of_choosing.h"

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 main(i32 argc, const string argv[]) {
    // Setting-up the main pixel-buffer
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };

    // Set-up your back-end here ...

    while(true) {
        // Clearing the pixel-buffer to white (0xffffffff -> #FFFFFFFF -> WHITE)
        silkClearPixelBufferColor(buffer, 0xffffffff);

        // Draw the red rectangle at the position in the middle of the pixel-buffer
        silkDrawRect(
            buffer,                                                             // pixel-buffer
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },        // pixel-buffer size
            SILK_PIXELBUFFER_WIDTH,                                             // pixel-buffer stride
            (vec2i) { SILK_PIXELBUFFER_CENTER_X, SILK_PIXELBUFFER_CENTER_Y },   // The position where we want to draw our red rectangle
            (vec2i) { 64, 64 },                                                 // The size of our red rectangle
            0xff0000ff                                                          // The color of our rectangle (0xff0000ff -> #FF0000FF -> RED)
        );

        // ... Blit your graphics using your back-end ...
    }

    // ... close your back-end here

    return 0;
}