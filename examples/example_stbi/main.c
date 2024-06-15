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
    pixel* result;
    i32 image_channels = 0;

    stbi_uc* data = stbi_load(
        path, 
        &size->x, 
        &size->y, 
        &image_channels, 
        STBI_rgb_alpha
    );

    if(!data) {
        silkLogErr("Image loading failure: %s", stbi_failure_reason());
        return result;
    }

    result = (pixel*)calloc(size->x * size->y, sizeof(pixel));

    // index_source -> index of stb_image color channels
    // index_result -> index of our pixel buffer's data
    for(i32 index_source = 0, index_result = 0; index_source < size->x * size->y * image_channels * sizeof(stbi_uc) && index_result < size->x * size->y * sizeof(pixel); index_result++) {
        color col = { 0 };

        // STB_Image stores the pixel information as an array of color channels (u8's)
        // We need to take those color channels and transform them to our pixel color system
        // It's nothing special, just assigning the vlaues of each image channel to the 'color' struct and then parse it to the pixel value using 'silkColorToPixel'
        col.r = data[index_source++];
        col.g = data[index_source++];
        col.b = data[index_source++];
        col.a = data[index_source++];

        result[index_result] = silkColorToPixel(col);
    }

    stbi_image_free(data);

    silkLogInfo("Image path: %s", path);
    silkLogInfo("Image resolution: x.%i, y.%i", size->x, size->y);
    silkLogInfo("Image channels: %i", image_channels);
    silkLogInfo("Image memory size: %i", size->x * size->y * sizeof(pixel));

    return result;
}

i32 StbiRenderImage(pixel* buf, pixel* image, vec2i position, vec2i size) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
        return SILK_FAILURE;
    }

    if(!image) {
        silkLogErr("Passed the invalid image buffer.");
        
        return SILK_FAILURE;
    }

    for(i32 y = 0; y < size.y; y++) {
        for(i32 x = 0; x < size.x; x++) {
            silkDrawPixel(
                buf, 
                (vec2i) { position.x + x, position.y + y }, 
                silkGetPixel(image, (vec2i) { x, y }, size )
            );
        }
    }

    return SILK_SUCCESS;
}

i32 PPMSave(pixel* buf, const string path) {
    // You can learn more about PPM format here:
    // https://netpbm.sourceforge.net/doc/ppm.html

    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
        return SILK_FAILURE;
    }

    FILE* file = fopen(path, "w");
    if(!file) {
        silkLogErr("FILE: Couldn't open the file: %s", path);
        return SILK_FAILURE;
    }

    fprintf(
        file, 
        "P6\n"      // PPM Header
        "%i %i\n"   // PPM image's width and height
        "255\n",    // PPM max color information (maximum color value can be 225)
        SILK_PIXELBUFFER_WIDTH, 
        SILK_PIXELBUFFER_HEIGHT
    );

    if(ferror(file)) {
        fclose(file);
        return SILK_FAILURE;
    }

    for(int i = 0; i < SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT; i++) {
        u8 channels[3] = {
            silkPixelToColor(buf[i]).r,
            silkPixelToColor(buf[i]).g,
            silkPixelToColor(buf[i]).b
        };
        
        fwrite(
            channels, 
            sizeof(channels), 
            1, 
            file  
        );

        if(ferror(file)) {
            fclose(file);
            return SILK_FAILURE;
        }
    }

    fclose(file);

    return SILK_SUCCESS;
}

int main(int argc, const string argv[]) {
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };

    vec2i size = { 0 };
    pixel* image = StbiLoadImage("turtle.png", &size);

    silkClearPixelBufferColor(buffer, 0xffffffff);
    StbiRenderImage(
        buffer, 
        image, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH / 2 - size.x / 2, SILK_PIXELBUFFER_HEIGHT / 2 - size.y / 2 }, 
        size
    );

    PPMSave(buffer, "output.ppm");

    free(image);
    
    return 0;
}