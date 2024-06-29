// Compilation command:
// cc main.c -o example.out -lm

#include <stdlib.h>
#include <stdio.h>

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_INCLUDE_MODULE_STB_IMAGE
#define SILK_MODULE_STB_IMAGE_PATH "./examples/example_stbi/stb_image.h"

#define SILK_INCLUDE_MODULE_STB_IMAGE_WRITE
#define SILK_MODULE_STB_IMAGE_WRITE_PATH "./examples/example_stbi/stb_image_write.h"

#define SILK_IMPLEMENTATION
#include "../../silk.h"

int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };

    image img = silkLoadImage("turtle.png");

    const string text = "Hello, Stb_Image!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;

    silkClearPixelBufferColor(buffer, 0xffffffff);

    silkDrawImagePro(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, 
        SILK_PIXELBUFFER_WIDTH, 
        &img, 
        (vec2i) { SILK_PIXELBUFFER_CENTER_X, SILK_PIXELBUFFER_CENTER_Y }, 
        (vec2i) { img.size.x / 4, img.size.y / 4 }, 
        (vec2i) { img.size.x / 2, img.size.y / 2 }, 
        0xffffffff
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

    image buffer_to_image = silkBufferToImage(buffer, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT });

    silkSaveImage("output.png", &buffer_to_image);
    silkSaveImage("output.jpg", &buffer_to_image);
    silkSaveImage("output.bmp", &buffer_to_image);
    silkSaveImage("output.ppm", &buffer_to_image);
    
    silkUnloadBuffer(img.data);
    silkUnloadBuffer(buffer_to_image.data);
    
    return 0;
}