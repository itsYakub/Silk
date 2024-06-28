// Compilation command:
// cc main.c -o example.out

#include <stdio.h>

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    i32 rectangle_rotation = 45;
    
    const string text = "Hello, PPM!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;

    silkClearPixelBufferColor(buffer, 0xffffffff);

    silkDrawRectPro(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
        SILK_PIXELBUFFER_WIDTH, 
        (vec2i) {
            SILK_PIXELBUFFER_CENTER_X,
            SILK_PIXELBUFFER_CENTER_Y
        }, 
        (vec2i) {
            SILK_PIXELBUFFER_CENTER_Y / 2,
            SILK_PIXELBUFFER_CENTER_Y / 2
        }, 
        rectangle_rotation, 
        (vec2i) {
            SILK_PIXELBUFFER_CENTER_Y / 4,
            SILK_PIXELBUFFER_CENTER_Y / 4
        }, 
        0xff0000ff
    );

    silkDrawTextDefault(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
        SILK_PIXELBUFFER_WIDTH,
        text, 
        (vec2i) { 
            SILK_PIXELBUFFER_CENTER_X - silkMeasureText(text, text_size, text_spacing).x / 2, 
            SILK_PIXELBUFFER_CENTER_Y - silkMeasureText(text, text_size, text_spacing).y / 2 + SILK_PIXELBUFFER_CENTER_Y / 2 
        }, 
        text_size, 
        text_spacing,
        0xff000000
    );
    
    silkSavePPM(buffer, "output.ppm");

    return 0;
}