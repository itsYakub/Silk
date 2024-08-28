// Compilation command:
// cc main.c -o example.out

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#define SILK_PIXELBUFFER_WIDTH 64
#define SILK_PIXELBUFFER_HEIGHT 48

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
                SILK_PIXELBUFFER_WIDTH
            );

            if(pix == 0x00000000) {
                putc(' ', stdout);
                putc(' ', stdout);
            }

            else {
                putc('#', stdout);
                putc('#', stdout);
            }
        }

        putc('\n', stdout);
    }

    printf("\033[%dA", SILK_PIXELBUFFER_HEIGHT);
    printf("\033[%dD", SILK_PIXELBUFFER_WIDTH);


    return SILK_SUCCESS;
}

i32 main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];
    i32 rotation = 0.0f;

    while(true) {
        silkClearPixelBuffer(buffer);
        silkDrawRectPro(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH / 2, SILK_PIXELBUFFER_HEIGHT / 2 }, 
            (vec2i) { SILK_PIXELBUFFER_HEIGHT / 4, SILK_PIXELBUFFER_HEIGHT / 4 }, 
            rotation++,
            (vec2i) { SILK_PIXELBUFFER_HEIGHT / 8, SILK_PIXELBUFFER_HEIGHT / 8 },
            0xffffffff
        );

        ConsoleBlit(buffer);

        usleep(1000 / 60);
    }

    return 0;
}