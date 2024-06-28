// Compilation command:
// $ mkdir bin/
// $ cd bin/
// $ cmake ..
// $ cmake --build .

#include "./bin/_deps/raylib-build/raylib/include/raylib.h"
#include "./bin/_deps/raylib-build/raylib/include/raymath.h"

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 RaylibSetup(Texture* texture) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(
        800, 
        600, 
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

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    SetTextureFilter(*texture, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

#elif defined (SILK_BYTEORDER_BIG_ENDIAN)

    SetTextureFilter(*texture, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

#endif

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

    i32 rectangle_rotation = 0;
    
    const string text = "Hello, raylib!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;

    // Raylib components
    Texture raylib_texture = { 0 };
    
    // Setting-up Raylib components
    RaylibSetup(&raylib_texture);

    silkLogByteOrderStatus();
    silkLogAlphaBlendStatus();

    // Update-Render loop
    while(!WindowShouldClose()) {
        // Clearing the silk's pixel buffer
        silkClearPixelBufferColorRegion(buffer, (vec2i) { GetScreenWidth(), GetScreenHeight() }, SILK_PIXELBUFFER_WIDTH, 0xffffffff);

        silkDrawRectPro(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH, 
            (vec2i) {
                GetScreenWidth() / 2,
                GetScreenHeight() / 2
            }, 
            (vec2i) {
                GetScreenHeight() / 4,
                GetScreenHeight() / 4
            }, 
            rectangle_rotation++, 
            (vec2i) {
                GetScreenHeight() / 8,
                GetScreenHeight() / 8
            }, 
            0xff0000ff
        );

        silkDrawTextDefault(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            text, 
            (vec2i) { 
                GetScreenWidth() / 2 - silkMeasureText(text, text_size, text_spacing).x / 2, 
                GetScreenHeight() / 2 - silkMeasureText(text, text_size, text_spacing).y / 2 + GetScreenHeight() / 4 
            }, 
            text_size, 
            text_spacing,
            0xff000000
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