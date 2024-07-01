// Compilation command (linux):
// - Compilation command (on linux):
// cc main.c -lX11 -lXrandr -lm -o example.out
//
// - Compilation command (on windows):
// cc main.c -lgdi32 -lwinmm -o example.exe
//
// Compilation command (on macOS):
// cc main.c -lm -framework Foundation -framework AppKit -framework CoreVideo -o example.out

#include <stdbool.h>
#include <string.h>

#define RGFW_BUFFER
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

size_t screenWidth = 0;
#define SILK_PIXELBUFFER_WIDTH screenWidth
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

int main(int argc, const string argv[]) {
    // RGFW components
    silkLogInfo("RGFW: Platform initialized successfully.");

    RGFW_window* window = RGFW_createWindow("Silk 1.0 - RGFW Example", RGFW_RECT(0, 0, 800, 600), RGFW_CENTER);

    RGFW_window_setIcon(window, icon, RGFW_AREA(3, 3), 4);
    screenWidth = RGFW_getScreenSize().w;
    
    // check blend status
    silkLogAlphaBlendStatus();

    // Update-Render loop
    bool exit = false;
    u8 star = false;
    size_t angle = 0;
    u32 angleDir = 1;

    image img = silkBufferToImage((pixel*)icon, (vec2i) { 3, 3 });

    vec2i circlePoint = {100, 100};

    while(!exit) { 
        // Dispatching window events
        while(RGFW_window_checkEvent(window)) {
            switch (window->event.type) {
                case RGFW_quit: {
                    exit = true;
                    break;
                }
                case RGFW_keyReleased: {  
                    switch (window->event.keyCode) {
                        case RGFW_Return: {
                            star = !star;
                            RGFW_window_showMouse(window, !star);
                            break;
                        }
                        case RGFW_Space: {
                            star = (star) ? 0 :  3;
                            RGFW_window_showMouse(window, !star);
                            break;
                        }
                        case RGFW_BackSpace: {
                            star = 0;
                            RGFW_window_setMouse(window, icon, RGFW_AREA(3, 3), 4);
                            break;
                        }
                        default: break;
                    }

                }
                case RGFW_mouseButtonReleased: {
                    if (window->event.button != 1)
                        break;

                    RGFW_rect r = {(window->r.w / 2) - 74, SILK_PIXELBUFFER_CENTER_Y - 64, 138, 128};

                    if (window->event.point.x >= r.x &&  window->event.point.x <= r.x + r.w && window->event.point.y >= r.y && window->event.point.y <= r.y + r.h) {
                        angleDir = (angleDir == 1) ? -1 : 1;
                    }

                    silkDrawStar((pixel*)window->buffer, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, SILK_PIXELBUFFER_WIDTH, (vec2i){window->event.point.x, window->event.point.y}, 10, 0, 8, 0xffeaddca);
                }
            }
        }

        // Clearing the silk's pixel buffer
        silkClearPixelBufferColor((pixel*)window->buffer, 0xff333333);
        
        // Draw the rectangle at the middle of the screen
        silkDrawRectPro(
            (pixel*)window->buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            (vec2i) { (window->r.w / 2), SILK_PIXELBUFFER_CENTER_Y}, 
            (vec2i) { 128, 128 }, 
            angle,
            (vec2i) { 64, 64 },
            0xff0000ff
        );
        angle += angleDir;

        silkDrawCircle((pixel*)window->buffer, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, SILK_PIXELBUFFER_WIDTH, circlePoint, 20, 0xff00ff00);

        RGFW_vector v = RGFW_window_getMousePoint(window);
        if (star == 1) {
            silkDrawStar((pixel*)window->buffer, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, SILK_PIXELBUFFER_WIDTH, (vec2i){v.x, v.y}, 10, 0, 5, 0xff00FFFF);
        }

        if (star == 3)
            silkDrawImage((pixel*)window->buffer, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, SILK_PIXELBUFFER_WIDTH, &img, (vec2i){v.x, v.y});

        if (RGFW_isPressedI(window, RGFW_Up))
            circlePoint.y--;
        if (RGFW_isPressedI(window, RGFW_Down))
            circlePoint.y++;
        if (RGFW_isPressedI(window, RGFW_Left))
            circlePoint.x--;
        if (RGFW_isPressedI(window, RGFW_Right))
            circlePoint.x++;

        // Displaying the graphics on the window
        RGFW_window_swapBuffers(window);
    }

    // Closing RGFW
    RGFW_window_close(window);

    return 0;
}