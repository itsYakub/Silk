// Compilation command:
// cc main.c -o example.out

#include <stdio.h>

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

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
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT];

    silkClearPixelBufferColor(buffer, 0xffffffff);

    silkDrawCircle(
        buffer, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH / 2.0, SILK_PIXELBUFFER_HEIGHT / 2.0f }, 
        SILK_PIXELBUFFER_HEIGHT / 4, 
        0xff0000ff
    );
    
    PPMSave(buffer, "output.ppm");

    return 0;
}