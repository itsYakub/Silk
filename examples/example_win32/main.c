// Compilation command (on Windows)
// cc main.c -o example -municode -lgdi32

#if !defined (UNICODE)
    #define UNICODE
#endif // UNICODE

#include <Windows.h>
#include <wingdi.h>
#include <windef.h>
#include <winuser.h>

#define SILK_IMPLEMENTATION
#include "../../silk.h"

// NOTE(yakub): For some reason pixel buffer must be statically / globaly declared; otherwise the program won't even launch...
static pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };
static bool win32_close_window = false;
static vec2i win32_window_size = { 0 };

LRESULT Win32WindowProcedures(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_SIZE: {
            RECT win32_window_rect = { 0 };
            GetClientRect(hwnd, &win32_window_rect);

            win32_window_size = (vec2i) {
                .x = win32_window_rect.right - win32_window_rect.left,
                .y = win32_window_rect.bottom - win32_window_rect.top
            };
        } break;

        case WM_CLOSE: {
            win32_close_window = true;
            PostQuitMessage(0);
        } break;

        case WM_DESTROY: {
            win32_close_window = true;
            PostQuitMessage(0);
        } break;
    }

    return DefWindowProc(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
};

i32 Win32CreateWindow(HINSTANCE hInstance, i32 nCmdShow, HWND* window) {
    if(window == NULL) {
        silkLogErr("WIN32: Passed a NULL parameter: window.");

        return SILK_FAILURE;
    }

    const wchar_t win32_window_class_name[] = L"SilkWin32Example";

    WNDCLASS win32_window_class = { 
        .lpszClassName = win32_window_class_name,
        .lpfnWndProc = Win32WindowProcedures,
        .hInstance = hInstance
    };
    
    RegisterClass(&win32_window_class);

    silkLogInfo("WIN32: Registered window class: %ls", win32_window_class_name);

    *window = CreateWindowEx(
        0, 
        win32_window_class_name, 
        L"Silk 1.0 - Win32 Example", 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        800, 
        600, 
        NULL, 
        NULL, 
        hInstance, 
        NULL
    );

    if(window == NULL) {
        silkLogErr("WIN32: Unable to create a Win32 window.");

        return SILK_FAILURE;
    }

    ShowWindow(*window, nCmdShow);

    silkLogInfo("WIN32: Window created successfully.");

    return SILK_SUCCESS;
};

i32 Win32DispatchEvents(HWND* window, MSG* messages) {
    if(window == NULL) {
        silkLogErr("WIN32: Passed a NULL parameter: window.");

        return SILK_FAILURE;
    }

    if(messages == NULL) {
        silkLogErr("WIN32: Passed a NULL parameter: messages.");

        return SILK_FAILURE;
    }

    while(PeekMessageA(messages, *window, 0, 0, PM_REMOVE)) {
        TranslateMessage(messages);
        DispatchMessage(messages);
    }

    return SILK_SUCCESS;
};

i32 Win32Blit(HWND* window) {
    if(window == NULL) {
        silkLogErr("WIN32: Passed a NULL parameter: window.");

        return SILK_FAILURE;
    }

    BITMAPINFO win32_bitmap_info = {
        .bmiHeader.biSize = sizeof(win32_bitmap_info.bmiHeader),
        .bmiHeader.biWidth = SILK_PIXELBUFFER_WIDTH,
        .bmiHeader.biHeight = -SILK_PIXELBUFFER_HEIGHT,
        .bmiHeader.biBitCount = 32,
        .bmiHeader.biPlanes = 1,
        .bmiHeader.biCompression = BI_RGB
    };

    HDC win32_device_context = GetDC(*window);

    StretchDIBits(
        win32_device_context, 
        0, 0, win32_window_size.x, win32_window_size.y, 
        0, 0, win32_window_size.x, win32_window_size.y, 
        buffer, 
        &win32_bitmap_info, 
        DIB_RGB_COLORS, 
        SRCCOPY
    );

    ReleaseDC(*window, win32_device_context);


    return SILK_SUCCESS;
};

i32 WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, i32 nCmdShow) {
    i32 rotation = 0;
    
    const string text = "Hello, Win32!";
    const i32 text_size = 4;
    const i32 text_spacing = 1;

    // Win32 components
    HWND win32_window;
    MSG win32_event_messages;

    // Setting-up Win32
    Win32CreateWindow(hInstance, nCmdShow, &win32_window);

    // Update-Render loop
    while(!win32_close_window) {
        // Dispatching Win32 events
        Win32DispatchEvents(&win32_window, &win32_event_messages);

        // Clearing the silk's pixel buffer
        silkClearPixelBufferColorRegion(buffer, win32_window_size, SILK_PIXELBUFFER_WIDTH, 0xffffffff);

        silkDrawTriangleEquilateral(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH, 
            (vec2i) {
                win32_window_size.x / 2,
                win32_window_size.y / 2
            }, 
            win32_window_size.y / 8, 
            rotation++, 
            0xff0000ff
        );

        silkDrawTextDefault(
            buffer, 
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },
            SILK_PIXELBUFFER_WIDTH,
            text, 
            (vec2i) { 
                win32_window_size.x / 2 - silkMeasureText(text, text_size, text_spacing).x / 2, 
                win32_window_size.y / 2 - silkMeasureText(text, text_size, text_spacing).y / 2 + win32_window_size.y / 4 
            }, 
            text_size, 
            text_spacing,
            0xff000000
        );

        // Displaying the graphics on the window
        Win32Blit(&win32_window);
    }

    return 0;
}

