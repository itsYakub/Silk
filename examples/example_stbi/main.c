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

    silkDrawBuffer(
        buf,
        image, 
        (vec2i) { 0 }, 
        size, 
        (vec2i) { size.x * scale, size.y * scale }
    );

    return SILK_SUCCESS;
}

int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };

    silkLogErr(silkGetError());

    vec2i size = { 0 };
    pixel* image = StbiLoadImage("turtle.png", &size);

    silkClearPixelBufferColor(buffer, 0xffffffff);

    StbiRenderImage(
        buffer, 
        image, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH / 2 - size.x / 2, SILK_PIXELBUFFER_HEIGHT / 2 - size.y / 2 }, 
        size,
        1
    );

    silkSavePPM(buffer, "output.ppm");
    silkUnloadBuffer(image);
    
    return 0;
}