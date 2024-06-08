// Compilation command:
// cc main.c -o example.out

#include <stdio.h>

#define SILK_IMPLEMENTATION
#include "../../silk.h"

static i32 saveToPPM(pixel_buffer* buf, const char* path) {
    FILE* file = fopen(path, "w");
    if(!file) {
        return SILK_FAILURE;
    }

    fprintf(
        file, 
        "P6\n"      // PPM Header
        "%i %i\n"   // PPM image's width and height
        "255\n",    // PPM max color information (maximum color value can be 225)
        buf->size.x, 
        buf->size.y
    );

    if(ferror(file)) {
        fclose(file);
        return SILK_FAILURE;
    }

    for(int i = 0; i < buf->size.x * buf->size.y; i++) {
        u8 channels[3] = {
            silkPixelToColor(buf->buffer[i]).r,
            silkPixelToColor(buf->buffer[i]).g,
            silkPixelToColor(buf->buffer[i]).b
        };
        
        // PPM pixel data
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

int main(int argc, char* argv[]) {
    pixel_buffer buffer = silkCreatePixelBuffer(800, 600);

    silkClearPixelBufferColor(&buffer, 0xffffffff);

    silkDrawCircle(
        &buffer, 
        (vec2i) { 
            buffer.size.x / 2.0f,
            buffer.size.y / 2.0f
        }, 
        128,
        0xff0000ff    
    );
    
    saveToPPM(&buffer, "output.ppm");

    silkPixelBufferFree(&buffer);

    return 0;
}