// Compilation command:
// cc main.c -o example.out -lm

#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

pixel* StbiLoadImage(const string path, vec2i* size) {
    pixel* result = (pixel*) stbi_load(
        path, 
        &size->x, 
        &size->y, 
        NULL, 
        STBI_rgb_alpha
    );

    if(!result) {
        silkLogErr("Image loading failure: %s", stbi_failure_reason());
        return result;
    }

    silkLogInfo("Image path: %s", path);
    silkLogInfo("Image resolution: x.%i, y.%i", size->x, size->y);
    silkLogInfo("Image memory size: %i", size->x * size->y * sizeof(pixel));

    return result;
}

i32 StbiRenderImage(pixel* buf, pixel* image, vec2i position, vec2i size, i32 scale) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
        return SILK_FAILURE;
    }

    if(!image) {
        silkLogErr("Passed the invalid image buffer.");
        
        return SILK_FAILURE;
    }

    silkDrawBufferPro(
        buf,                                                        // Main pixel-buffer
        SILK_PIXELBUFFER_WIDTH,                                     // Stride of the pixel-buffer
        image,                                                      // Image buffer
        position,                                                   // Image position
        (vec2i) { size.x / 2, size.y / 2 },                         // Image position offset        
        size,                                                       // Image size (source)
        (vec2i) { size.x * scale, size.y * scale },                 // Image size (destination)
        0xffffffff                                                  // Image tint
    );

    return SILK_SUCCESS;
}

int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };

    vec2i size = { 0 };
    pixel* image = StbiLoadImage("turtle.png", &size);

    const string text = "Hello, Stb_Image!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;

    silkClearPixelBufferColor(buffer, 0xffffffff);

    silkDrawBufferPro(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
        SILK_PIXELBUFFER_WIDTH, 
        image, 
        (vec2i) {
            SILK_PIXELBUFFER_CENTER_X,
            SILK_PIXELBUFFER_CENTER_Y
        }, 
        (vec2i) {
            size.x / 4,
            size.y / 4
        }, 
        size,
        (vec2i) {
            size.x / 2,
            size.y / 2
        },
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

    silkSavePPM(buffer, "output.ppm");
    silkUnloadBuffer(image);
    
    return 0;
}