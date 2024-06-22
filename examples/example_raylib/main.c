// Compilation command:
// $ mkdir bin/
// $ cd bin/
// $ cmake ..
// $ cmake --build .

#include "./bin/_deps/raylib-build/raylib/include/raylib.h"
#include "./bin/_deps/raylib-build/raylib/include/raymath.h"

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 RaylibSetup(Texture* texture) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(
        SILK_PIXELBUFFER_WIDTH, 
        SILK_PIXELBUFFER_HEIGHT, 
        "Silk 1.0 - Raylib Example"
    );

    if(!IsWindowReady()) {
        silkLogErr("Raylib: Couldn't create a Window");

        return SILK_FAILURE;
    }

    Image raylib_image = GenImageColor(
        SILK_PIXELBUFFER_WIDTH, 
        SILK_PIXELBUFFER_HEIGHT, 
        BLANK
    );

    *texture = LoadTextureFromImage(raylib_image);
    UnloadImage(raylib_image);

    if(!IsTextureReady(*texture)) {
        silkLogErr("Raylib: Couldn't create a Texture");

        return SILK_FAILURE;
    }

    return SILK_SUCCESS;
}

i32 RaylibBlit(pixel* buffer, Texture* texture) {
    if(buffer == NULL) {
        silkLogErr("Raylib: Passed a NULL parameter: buffer.");

        return SILK_FAILURE;
    } if(texture == NULL) {
        silkLogErr("Raylib: Passed a NULL parameter: texture.");

        return SILK_FAILURE;
    }

    UpdateTexture(*texture, buffer);

    BeginDrawing();
    DrawTexture(*texture, 0, 0, WHITE);
    EndDrawing();

    return SILK_SUCCESS;
}

i32 RaylibClose(Texture* texture) {
    if(texture == NULL) {
        silkLogErr("Raylib: Passed a NULL parameter: texture.");

        return SILK_FAILURE;
    } 

    UnloadTexture(*texture);
    CloseWindow();

    return SILK_SUCCESS;
}

int main(int argc, const string argv[]) {
    // Silk's pixel buffer
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };
    i32 rotation = 0;

    // Raylib components
    Texture raylib_texture = { 0 };
    
    // Setting-up Raylib components
    RaylibSetup(&raylib_texture);

    // Update-Render loop
    while(!WindowShouldClose()) {
        // Clearing the silk's pixel buffer
        silkClearPixelBufferColor(buffer, 0xffffffff);

        // Draw the spinning star at the middle of the screen
        silkDrawStar(
            buffer, 
            (vec2i) { 
                SILK_PIXELBUFFER_CENTER_X, 
                SILK_PIXELBUFFER_CENTER_Y
            }, 
            SILK_PIXELBUFFER_HEIGHT / 4, 
            5, 
            rotation++,
            0xff0000ff
        );

        // Displaying the graphics on the window
        RaylibBlit(
            buffer,
            &raylib_texture
        );
    }

    // Closing Raylib
    RaylibClose(&raylib_texture);

    return 0;
}