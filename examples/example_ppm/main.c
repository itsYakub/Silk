// Compilation command:
// cc main.c -o example.out

#include <stdio.h>

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    silkClearPixelBufferColor(buffer, 0xffffffff);

    silkDrawCircle(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH / 2, SILK_PIXELBUFFER_HEIGHT / 2 }, 
        SILK_PIXELBUFFER_HEIGHT / 4, 
        0xff0000ff
    );
    
    silkSavePPM(buffer, "output.ppm");

    return 0;
}