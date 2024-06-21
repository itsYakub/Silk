// Compilation command:
// cc main.c -o example.out

#include <stdbool.h>
#include <stdio.h>

#define SILK_PIXELBUFFER_WIDTH 64
#define SILK_PIXELBUFFER_HEIGHT 32

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 ConsoleBlit(pixel* buf) {
    if(buf == NULL) {
        silkLogErr("Raylib: Passed a NULL parameter: buffer.");

        return SILK_FAILURE;
    }

    for(int y = 0; y < SILK_PIXELBUFFER_HEIGHT; y++) {
        for(int x = 0; x < SILK_PIXELBUFFER_WIDTH; x++) {
            pixel pix = silkGetPixel(
                buf, 
                (vec2i) { x, y }, 
                (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT}
            );

            if(pix == 0x00000000) {
                printf("%c", ' ');
            }

            else {
                printf("%c", '#');
            }
        }

        printf("\n");
    }

    return SILK_SUCCESS;
}

i32 main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    silkClearPixelBuffer(buffer);
    silkDrawRectPro(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH / 2, SILK_PIXELBUFFER_HEIGHT / 2 }, 
        (vec2i) { SILK_PIXELBUFFER_HEIGHT / 4, SILK_PIXELBUFFER_HEIGHT / 4 }, 
        (vec2i) { SILK_PIXELBUFFER_HEIGHT / 8, SILK_PIXELBUFFER_HEIGHT / 8 },
        0,
        0xffffffff
    );

    ConsoleBlit(buffer);

    return 0;
}