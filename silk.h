// --------------------------------------------------------------------------------------------------------------------------------
// Silk: Single-Header CPU graphics library
// --------------------------------------------------------------------------------------------------------------------------------
// Author: @itsYakub
//      - GitHub:           https://github.com/itsYakub
//      - GitLab:           https://gitlab.com/itsYakub
//      - Twitter / X:      https://twitter.com/YakubButOnTwt
// --------------------------------------------------------------------------------------------------------------------------------
// Version history:
//      - 1.0 (Current):
//          - Release date: 
// --------------------------------------------------------------------------------------------------------------------------------
// Macro definitions:
// - SILK_IMPLEMENTATION:
//      This macro includes function definitions to the project, during the "preprocessor" compilation stage.
//      NOTE: This macro MUST be included only once. Otherwise there will be a multiple-definition error!   
//
// - SILK_ENABLE_ALPHABLEND:
//      Enables alpha-blending.
//      NOTE: This macro is defined by default. You can disable it by defining 'SILK_DISABLE_ALPHABLEND'.
//
// - SILK_DISABLE_ALPHABLEND:
//      Disables alpha-blending.
//
// - SILK_DISABLE_LOG_INFO:
//      Disables info-logging.
//
// - SILK_DISABLE_LOG_WARN:
//      Disables warn-logging.
//
// - SILK_DISABLE_LOG_ERR:
//      Disables error-logging.
//
// - SILK_DISABLE_LOG_ALL:
//      Completely disables all logging (info, warn and err).
// --------------------------------------------------------------------------------------------------------------------------------
// Licence: MIT
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE. 
// --------------------------------------------------------------------------------------------------------------------------------

#if !defined(SILK_H)
#define SILK_H

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Macro Definitions
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_API

#define SILK_VERSION "1.0"
#define SILK_VERSION_MAJOR 1
#define SILK_VERSION_MINOR 0

#define SILK_SUCCESS 0 // SILK_SUCCESS: returned if the function was executed successfully
#define SILK_FAILURE 1 // SILK_FAILURE: returned if there was a problem during the function execution

#if !defined (SILK_DISABLE_ALPHABLEND)
    #define SILK_ENABLE_ALPHABLEND
#endif

#if !defined(SILK_PIXELBUFFER_WIDTH)
    #define SILK_PIXELBUFFER_WIDTH 1920 // SILK_PIXELBUFFER_WIDTH: Default Full HD monitor width
#endif // SILK_PIXELBUFFER_WIDTH

#if !defined(SILK_PIXELBUFFER_HEIGHT)
    #define SILK_PIXELBUFFER_HEIGHT 1080 // SILK_PIXELBUFFER_HEIGHT: Default Full HD monitor height
#endif // SILK_PIXELBUFFER_HEIGHT

#define SILK_PIXELBUFFER_CENTER_X (SILK_PIXELBUFFER_WIDTH / 2)
#define SILK_PIXELBUFFER_CENTER_Y (SILK_PIXELBUFFER_HEIGHT / 2)

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Typedefs
// --------------------------------------------------------------------------------------------------------------------------------

typedef int                                             i32;
typedef float                                           f32;
typedef unsigned char                                   u8;
typedef unsigned int                                    u32;
typedef char*                                           string;

typedef struct { i32 x; i32 y; }                        vec2i;
typedef struct { u8 r; u8 g; u8 b; u8 a; }              color;

typedef u8                                              color_channel;
typedef u32                                             pixel;


// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function declarations
// --------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {            
#endif

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkClearPixelBuffer(pixel* buf);
SILK_API i32 silkClearPixelBufferRegion(pixel* buf, vec2i region);
SILK_API i32 silkClearPixelBufferColor(pixel* buf, pixel pix);
SILK_API i32 silkClearPixelBufferColorRegion(pixel* buf, vec2i region, pixel pix);

SILK_API pixel silkGetPixel(pixel* buf, vec2i position, vec2i size);
SILK_API i32 silkSetPixel(pixel* buf, vec2i position, vec2i size, pixel pix);

SILK_API i32 silkUnloadBuffer(pixel* buf);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API color silkPixelToColor(pixel pix);
SILK_API pixel silkColorToPixel(color col);
SILK_API pixel silkAlphaBlend(pixel base_pixel, pixel return_pixel, color_channel value);
SILK_API pixel silkPixelFade(pixel pix, f32 factor);
SILK_API pixel silkPixelTint(pixel pix, pixel tint);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel* buf, vec2i position, pixel pix);

SILK_API i32 silkDrawLine(pixel* buf, vec2i start, vec2i end, pixel pix);

SILK_API i32 silkDrawRect(pixel* buf, vec2i position, vec2i size, i32 rotation, pixel pix);
SILK_API i32 silkDrawRectPro(pixel* buf, vec2i position, vec2i offset, vec2i size, i32 angle, pixel pix);
SILK_API i32 silkDrawRectLines(pixel* buf, vec2i position, vec2i size, pixel pix);

SILK_API i32 silkDrawCircle(pixel* buf, vec2i position, i32 radius, pixel pix);
SILK_API i32 silkDrawCircleLines(pixel* buf, vec2i position, i32 radius, pixel pix);

SILK_API i32 silkDrawTriangle(pixel* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix);
SILK_API i32 silkDrawTriangleLines(pixel* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix);
SILK_API i32 silkDrawTriangleEquilateral(pixel* buf, vec2i midpoint, i32 radius, i32 angle, pixel pix);
SILK_API i32 silkDrawTriangleEquilateralLines(pixel* buf, vec2i midpoint, i32 radius, pixel pix);

SILK_API i32 silkDrawPolygon(pixel* buf, vec2i midpoint, i32 radius, i32 n, i32 rotation, pixel pix);
SILK_API i32 silkDrawStar(pixel* buf, vec2i midpoint, i32 radius, i32 n, i32 rotation, pixel pix);

SILK_API i32 silkDrawBuffer(pixel* buf, pixel* img_buf, vec2i position, vec2i size);
SILK_API i32 silkDrawBufferScaled(pixel* buf, pixel* img_buf, vec2i position, vec2i size_src, vec2i size_dest);
SILK_API i32 silkDrawBufferPro(pixel* buf, pixel* img_buf, vec2i position, vec2i offset, vec2i size_src, vec2i size_dest, pixel tint);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkLogInfo(const string text, ...);
SILK_API i32 silkLogWarn(const string text, ...);
SILK_API i32 silkLogErr(const string text, ...);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Math
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkVectorSwap(vec2i* a, vec2i* b);
SILK_API i32 silkIntSwap(i32* a, i32* b);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: IO
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API pixel* silkLoadPPM(const string path, vec2i* size);
SILK_API i32 silkSavePPM(pixel* buf, const string path);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Error-Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API string silkGetError();

#if defined(__cplusplus)
}    
#endif

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Implementation
// --------------------------------------------------------------------------------------------------------------------------------

#ifdef SILK_IMPLEMENTATION

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Macro Definitions
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_TEXT_BUFFER_SIZE 256

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Error Messages
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_ERR_MSG_EMPTY "Error message NULL or Empty."
#define SILK_ERR_BUF_INVALID "Passed the invalid pixel buffer."
#define SILK_ERR_BUF_IMG_INVALID "Passed the invalid image buffer."
#define SILK_ERR_BUF_ACCES_OUT_OF_BOUNDS "Trying to access the out-of-bounds buffer address."
#define SILK_ERR_FILE_OPEN_FAIL "Couldn't open the file."

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Internals
// --------------------------------------------------------------------------------------------------------------------------------

static char silk_error_msg[SILK_TEXT_BUFFER_SIZE] = SILK_ERR_MSG_EMPTY;

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Internal functions
// --------------------------------------------------------------------------------------------------------------------------------

i32 silkAssignErrorMessage(const string msg) {
    strcpy(
        silk_error_msg,
        msg
    );

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function definitions
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkClearPixelBuffer(pixel* buf) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 pixel_index = 0; pixel_index < SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT; pixel_index++) {
        buf[pixel_index] = 0;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferRegion(pixel* buf, vec2i region) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < region.y; y++) {
        for(i32 x = 0; x < region.x; x++) {
            silkSetPixel(buf, (vec2i) { x, y }, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, 0);
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColor(pixel* buf, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 pixel_index = 0; pixel_index < SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT; pixel_index++) {
        buf[pixel_index] = pix;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColorRegion(pixel* buf, vec2i region, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < region.y; y++) {
        for(i32 x = 0; x < region.x; x++) {
            silkSetPixel(buf, (vec2i) { x, y }, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, pix);
        }
    }

    return SILK_SUCCESS;
}

SILK_API pixel silkGetPixel(pixel* buf, vec2i position, vec2i size) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return 0xffffffff;
    }

    return buf[position.y * size.x + position.x];
}

SILK_API i32 silkSetPixel(pixel* buf, vec2i position, vec2i size, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    buf[position.y * size.x + position.x] = pix;

    return SILK_SUCCESS;
}

SILK_API i32 silkUnloadBuffer(pixel* buf) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    free(buf);

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API color silkPixelToColor(pixel pix) {
    color result = { 0 };

    result.r = (pix >> 8 * 0) & 0xFF;
    result.g = (pix >> 8 * 1) & 0xFF;
    result.b = (pix >> 8 * 2) & 0xFF;
    result.a = (pix >> 8 * 3) & 0xFF;

    return result;
}

SILK_API pixel silkColorToPixel(color col) {
    pixel result = 0;

    result = 
        col.r | 
        col.g << 8 | 
        col.b << 16 | 
        col.a << 24;

    return result;
}

SILK_API pixel silkAlphaBlend(pixel base_pixel, pixel return_pixel, color_channel value) {
    color result = { 0 };
    color base_color = silkPixelToColor(base_pixel);
    color return_color = silkPixelToColor(return_pixel);

    result.r = base_color.r + (return_color.r - base_color.r) * (value / 255.0f);
    result.g = base_color.g + (return_color.g - base_color.g) * (value / 255.0f);
    result.b = base_color.b + (return_color.b - base_color.b) * (value / 255.0f);
    result.a = value;

    return silkColorToPixel(result);
}

SILK_API pixel silkPixelFade(pixel pix, f32 factor) {
    color result = { 
        .r = silkPixelToColor(pix).r,
        .g = silkPixelToColor(pix).g,
        .b = silkPixelToColor(pix).b,
        .a = factor * 255
    };

    return silkColorToPixel(result);
}

SILK_API pixel silkPixelTint(pixel pix, pixel tint) {
    color result = { 
        .r = ((i32)silkPixelToColor(pix).r * (i32)silkPixelToColor(tint).r) / 255,
        .g = ((i32)silkPixelToColor(pix).g * (i32)silkPixelToColor(tint).g) / 255,
        .b = ((i32)silkPixelToColor(pix).b * (i32)silkPixelToColor(tint).b) / 255,
        .a = ((i32)silkPixelToColor(pix).a * (i32)silkPixelToColor(tint).a) / 255
    };

    return silkColorToPixel(result);
}

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel* buf, vec2i position, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if( (position.x < 0 || position.x >= SILK_PIXELBUFFER_WIDTH) ||
        (position.y < 0 || position.y >= SILK_PIXELBUFFER_HEIGHT)) {
        silkAssignErrorMessage(SILK_ERR_BUF_ACCES_OUT_OF_BOUNDS);

        return SILK_FAILURE;
    }

    // If the pixel from this position is the same as the pixel we want to draw, we can return, 
    // as there won't be any change in this specific position.
    if(silkGetPixel(buf, position, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }) == pix) {
        return SILK_SUCCESS;
    }

#if !defined(SILK_DISABLE_ALPHABLEND) || defined(SILK_ENABLE_ALPHABLEND)

    pix = silkAlphaBlend(
        silkGetPixel(buf, position, (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT } ), 
        pix, 
        silkPixelToColor(pix).a
    );

#endif

    silkSetPixel(
        buf, 
        position, 
        (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT }, 
        pix
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawLine(pixel* buf, vec2i start, vec2i end, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(start.x < end.x) {
        silkVectorSwap(&start, &end);
    }

    f32 x = start.x;
    f32 y = start.y;
    
    f32 dx = end.x - start.x;
    f32 dy = end.y - start.y;

    f32 steps = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);

    dx /= steps;
    dy /= steps;

    for(int i = 0; i <= steps; i++) {
        silkDrawPixel(buf, (vec2i) { round(x), round(y) } , pix);
        x += dx;
        y += dy;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRect(pixel* buf, vec2i position, vec2i size, i32 rotation, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    silkDrawRectPro(
        buf, 
        position, 
        size, 
        (vec2i) { 0 }, 
        rotation, 
        pix
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRectPro(pixel* buf, vec2i position, vec2i offset, vec2i size, i32 angle, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    vec2i points[4] = {
        { 0 }, // top-left
        { 0 }, // top_right
        { 0 }, // bottom_left
        { 0 }  // bottom_right
    };

    f32 angle_to_radians = angle * 3.14 / 180;

    vec2i delta = { 
        -offset.x,
        -offset.y
    };

    points[0].x = position.x + delta.x * cos(angle_to_radians) - delta.y * sin(angle_to_radians);
    points[0].y = position.y + delta.x * sin(angle_to_radians) + delta.y * cos(angle_to_radians);

    points[1].x = position.x + (delta.x + size.x) * cos(angle_to_radians) - delta.y * sin(angle_to_radians);
    points[1].y = position.y + (delta.x + size.x) * sin(angle_to_radians) + delta.y * cos(angle_to_radians);

    points[2].x = position.x + delta.x * cos(angle_to_radians) - (delta.y + size.y) * sin(angle_to_radians);
    points[2].y = position.y + delta.x * sin(angle_to_radians) + (delta.y + size.y) * cos(angle_to_radians);

    points[3].x = position.x + (delta.x + size.x) * cos(angle_to_radians) - (delta.y + size.y) * sin(angle_to_radians);
    points[3].y = position.y + (delta.x + size.x) * sin(angle_to_radians) + (delta.y + size.y) * cos(angle_to_radians);

    // Indices:
    // 0 - 1 - 2
    // 1 - 2 - 3

    silkDrawTriangle(
        buf, 
        points[0], 
        points[1], 
        points[2], 
        pix
    );

    silkDrawTriangle(
        buf, 
        points[1], 
        points[2], 
        points[3], 
        pix
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRectLines(pixel* buf, vec2i position, vec2i size, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    silkDrawLine(buf, (vec2i) { position.x, position.y }, (vec2i) { position.x + size.x, position.y }, pix);
    silkDrawLine(buf, (vec2i) { position.x, position.y }, (vec2i) { position.x, position.y + size.y }, pix);
    silkDrawLine(buf, (vec2i) { position.x + size.x, position.y }, (vec2i) { position.x + size.x, position.y + size.y }, pix);
    silkDrawLine(buf, (vec2i) { position.x, position.y + size.y }, (vec2i) { position.x + size.x, position.y + size.y }, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawCircle(pixel* buf, vec2i position, i32 radius, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    i32 x0 = position.x - radius;
    i32 x1 = position.x + radius;

    i32 y0 = position.y - radius;
    i32 y1 = position.y + radius;

    for(i32 y = y0; y < y1; y++) {
        for(i32 x = x0; x < x1; x++) {
            vec2i delta = {
                x - position.x,
                y - position.y
            };

            if((delta.x * delta.x) + (delta.y * delta.y) <= (radius * radius)) {
                silkDrawPixel(buf, (vec2i) { x, y }, pix);
            }
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawCircleLines(pixel* buf, vec2i position, i32 radius, pixel pix) {
    // Source:
    // https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/

    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    i32 x = 0;
    i32 y = radius;
    i32 d = 3 - 2 * radius;

    silkDrawPixel(buf, (vec2i) { position.x + x, position.y + y }, pix);
    silkDrawPixel(buf, (vec2i) { position.x - x, position.y + y }, pix);
    silkDrawPixel(buf, (vec2i) { position.x + x, position.y - y }, pix);
    silkDrawPixel(buf, (vec2i) { position.x - x, position.y - y }, pix);
    silkDrawPixel(buf, (vec2i) { position.x + y, position.y + x }, pix);
    silkDrawPixel(buf, (vec2i) { position.x - y, position.y + x }, pix);
    silkDrawPixel(buf, (vec2i) { position.x + y, position.y - x }, pix);
    silkDrawPixel(buf, (vec2i) { position.x - y, position.y - x }, pix);

    while(y >= x) {
        x++;

        if(d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }

        silkDrawPixel(buf, (vec2i) { position.x + x, position.y + y }, pix);
        silkDrawPixel(buf, (vec2i) { position.x - x, position.y + y }, pix);
        silkDrawPixel(buf, (vec2i) { position.x + x, position.y - y }, pix);
        silkDrawPixel(buf, (vec2i) { position.x - x, position.y - y }, pix);
        silkDrawPixel(buf, (vec2i) { position.x + y, position.y + x }, pix);
        silkDrawPixel(buf, (vec2i) { position.x - y, position.y + x }, pix);
        silkDrawPixel(buf, (vec2i) { position.x + y, position.y - x }, pix);
        silkDrawPixel(buf, (vec2i) { position.x - y, position.y - x }, pix);
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangle(pixel* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix) {
    // Source:
    // https://github.com/tsoding/olive.c/commit/633c657dbea3435a64114570ecb3f703fa276f28

    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(point_a.y > point_b.y) silkVectorSwap(&point_a, &point_b);
    if(point_a.y > point_c.y) silkVectorSwap(&point_a, &point_c);
    if(point_b.y > point_c.y) silkVectorSwap(&point_b, &point_c);
    
    vec2i delta_vector_ab = {
        point_b.x - point_a.x,
        point_b.y - point_a.y
    };

    vec2i delta_vector_ac = {
        point_c.x - point_a.x,
        point_c.y - point_a.y
    };

    vec2i delta_vector_cb = {
        point_b.x - point_c.x,
        point_b.y - point_c.y
    };

    vec2i delta_vector_ca = {
        point_a.x - point_c.x,
        point_a.y - point_c.y
    };

    for(i32 y = point_a.y; y < point_b.y; y++) {
        if(y > 0 && y < SILK_PIXELBUFFER_HEIGHT) {
            i32 s1 = delta_vector_ab.y != 0 ? 
                (y - point_a.y) * delta_vector_ab.x / delta_vector_ab.y + point_a.x : 
                point_a.x;

            i32 s2 = delta_vector_ac.y != 0 ? 
                (y - point_a.y) * delta_vector_ac.x / delta_vector_ac.y + point_a.x : 
                point_a.x;

            if(s1 > s2) {
                silkIntSwap(&s1, &s2);
            }

            for(i32 x = s1; x <= s2; x++) {
                silkDrawPixel(buf, (vec2i) { x, y }, pix);
            }
        }
    }

    for(i32 y = point_b.y; y < point_c.y; y++) {
        if(y > 0 && y < SILK_PIXELBUFFER_HEIGHT) {
            i32 s1 = delta_vector_cb.y != 0 ? 
                (y - point_c.y) * delta_vector_cb.x / delta_vector_cb.y + point_c.x : 
                point_c.x;

            i32 s2 = delta_vector_ca.y != 0 ? 
                (y - point_c.y) * delta_vector_ca.x / delta_vector_ca.y + point_c.x : 
                point_c.x;

            if(s1 > s2) {
                silkIntSwap(&s1, &s2);
            }

            for(i32 x = s1; x <= s2; x++) {
                silkDrawPixel(buf, (vec2i) { x, y }, pix);
            }
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleLines(pixel* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(point_a.y > point_b.y) silkVectorSwap(&point_a, &point_b);
    if(point_a.y > point_c.y) silkVectorSwap(&point_a, &point_c);
    if(point_b.y > point_c.y) silkVectorSwap(&point_b, &point_c);

    silkDrawLine(buf, point_a, point_b, pix);
    silkDrawLine(buf, point_b, point_c, pix);
    silkDrawLine(buf, point_a, point_c, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleEquilateral(pixel* buf, vec2i midpoint, i32 radius, i32 angle, pixel pix) {
    // Source:
    // https://www.quora.com/How-do-you-calculate-the-triangle-vertices-coordinates-on-a-circumcircle-triangle-with-a-given-centre-point-and-radius-Assuming-the-triangle-is-acute-with-all-equal-length-sides-and-that-one-point-is-straight-up

    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    vec2i points[3] = {
        { midpoint.x, midpoint.y - radius },                                // point: 0 (top)
        { midpoint.x - sqrt(3) * radius / 2, midpoint.y + radius / 2 },     // point: 1 (left)
        { midpoint.x + sqrt(3) * radius / 2, midpoint.y + radius / 2 },     // point: 2 (bottom)
    };

    // Big thanks to @zet23t for help:
    // https://twitter.com/zet23t
    
    f32 angle_to_radians = angle * 3.14f / 180.0f;
    f32 x_right = cos(angle_to_radians);
    f32 y_right = sin(angle_to_radians);
    f32 x_up = -y_right;
    f32 y_up = x_right;
    
    for(i32 i = 0; i < 3; i++) {
        f32 dx = points[i].x - midpoint.x;
        f32 dy = points[i].y - midpoint.y;
        
        points[i].x = midpoint.x + (x_right * dx + x_up * dy);
        points[i].y = midpoint.y + (y_right * dx + y_up * dy);
    }

    silkDrawTriangle(buf, points[0], points[1], points[2], pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleEquilateralLines(pixel* buf, vec2i midpoint, i32 radius, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    vec2i point_a = {
        midpoint.x,
        midpoint.y - radius
    };

    vec2i point_b = {
        midpoint.x - sqrt(3) * radius / 2,
        midpoint.y + radius / 2
    };

    vec2i point_c = {
        midpoint.x + sqrt(3) * radius / 2,
        midpoint.y + radius / 2
    };

    silkDrawTriangleLines(buf, point_a, point_b, point_c, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawPolygon(pixel* buf, vec2i midpoint, i32 radius, i32 n, i32 rotation, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(n < 3) {
        n = 3;
    }

    i32 theta = 360 / n;
    vec2i points[n];

    // Calculating the positions of each point of our polygon
    for(i32 i = 0; i < n; i++) {
        // Equation: https://www.wyzant.com/resources/answers/601887/calculate-point-given-x-y-angle-and-distance
        points[i] = (vec2i) {
            .x = midpoint.x + radius * cos(((theta * i) + rotation) * 3.14 / 180),
            .y = midpoint.y + radius * sin(((theta * i) + rotation) * 3.14 / 180)
        };
    }

    // Drawing triangles based on the points
    for(i32 i = 0; i < n; i++) {
        silkDrawTriangle(
            buf, 
            midpoint,                               // First point is always midpoint
            points[i],                              // second point is based on the current 'i'
            i < n - 1 ? points[i + 1] : points[0],  // third point is based on the next index from 'i' OR the very first point of the array if we reach it's end
            pix
        );
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawStar(pixel* buf, vec2i midpoint, i32 radius, i32 n, i32 rotation, pixel pix) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(n < 3) {
        n = 3;
    }

    i32 theta = 360 / n;

    // Calculating the positions of each point of our star and rendering it to the screen
    for(i32 i = 0; i < n; i++) {
        // Equation: https://www.wyzant.com/resources/answers/601887/calculate-point-given-x-y-angle-and-distance
        vec2i point_a = {
            .x = midpoint.x + radius * cos(((theta * i) + rotation) * 3.14 / 180),
            .y = midpoint.y + radius * sin(((theta * i) + rotation) * 3.14 / 180)
        };        
        
        vec2i point_b = {
            .x = midpoint.x + (radius / n * 2) * cos(((theta * i) - 90 + rotation) * 3.14 / 180),
            .y = midpoint.y + (radius / n * 2) * sin(((theta * i) - 90 + rotation) * 3.14 / 180)
        };        
        
        vec2i point_c = {
            .x = midpoint.x + (radius / n * 2) * cos(((theta * i) + 90 + rotation) * 3.14 / 180),
            .y = midpoint.y + (radius / n * 2) * sin(((theta * i) + 90 + rotation) * 3.14 / 180)
        };

        silkDrawTriangle(
            buf, 
            point_a, 
            point_b, 
            point_c, 
            pix
        );
    }


    return SILK_SUCCESS;
}

SILK_API i32 silkDrawBuffer(pixel* buf, pixel* img_buf, vec2i position, vec2i size) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(!img_buf) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);
        
        return SILK_FAILURE;
    }

    silkDrawBufferPro(
        buf, 
        img_buf, 
        position, 
        (vec2i) { 0 },
        size, 
        size, 
        0xffffffff
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawBufferScaled(pixel* buf, pixel* img_buf, vec2i position, vec2i size_src, vec2i size_dest) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(!img_buf) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);
        
        return SILK_FAILURE;
    }

    silkDrawBufferPro(
        buf, 
        img_buf, 
        position,
        (vec2i) { 0 }, 
        size_src, 
        size_dest, 
        0xffffffff
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawBufferPro(pixel* buf, pixel* img_buf, vec2i position, vec2i offset, vec2i size_src, vec2i size_dest, pixel tint) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);
        
        return SILK_FAILURE;
    }

    if(!img_buf) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);
        
        return SILK_FAILURE;
    }

    for(i32 y = 0; y < size_dest.y; y++) {
        for(i32 x = 0; x < size_dest.x; x++) {
            vec2i new_position = {
                x * size_src.x / size_dest.x,
                y * size_src.y / size_dest.y
            };

            silkDrawPixel(
                buf, 
                (vec2i) { (position.x - offset.x) + x, (position.y - offset.y) + y },
                silkPixelTint(
                    silkGetPixel(
                        img_buf, 
                        new_position, 
                        size_src
                    ),
                    tint
                )
            );
        }
    }

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkLogInfo(const string text, ...) {
#if defined(SILK_DISABLE_LOG_INFO) || defined(SILK_DISABLE_LOG_ALL)

    return SILK_SUCCESS;

#endif

    char buf[SILK_TEXT_BUFFER_SIZE];

    va_list list;
    va_start(list, text);

    vsnprintf(
        buf, 
        sizeof(buf), 
        text, 
        list
    );

    va_end(list);

    fprintf(stdout, "[INFO] %s\n", buf);

    return SILK_SUCCESS;
}

SILK_API i32 silkLogWarn(const string text, ...) {
#if defined(SILK_DISABLE_LOG_WARN) || defined(SILK_DISABLE_LOG_ALL)

    return SILK_SUCCESS;

#endif

    char buf[SILK_TEXT_BUFFER_SIZE];

    va_list list;
    va_start(list, text);

    vsnprintf(
        buf, 
        sizeof(buf), 
        text, 
        list
    );

    va_end(list);

    fprintf(stdout, "[WARN] %s\n", buf);

    return SILK_SUCCESS;
}

SILK_API i32 silkLogErr(const string text, ...) {
#if defined(SILK_DISABLE_LOG_ERR) || defined(SILK_DISABLE_LOG_ALL)

    return SILK_SUCCESS;

#endif

    char buf[SILK_TEXT_BUFFER_SIZE];

    va_list list;
    va_start(list, text);

    vsnprintf(
        buf, 
        sizeof(buf), 
        text, 
        list
    );

    va_end(list);

    fprintf(stdout, "[ERR] %s\n", buf);

    return SILK_SUCCESS;
}


// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Math
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkVectorSwap(vec2i* a, vec2i* b) {
    vec2i temp = *a;
    *a = *b;
    *b = temp;

    return SILK_SUCCESS;
}

SILK_API i32 silkIntSwap(i32* a, i32* b) {
    i32 temp = *a;
    *a = *b;
    *b = temp;

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: IO
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API pixel* silkLoadPPM(const string path, vec2i* size) {
    // You can learn more about PPM format here:
    // https://netpbm.sourceforge.net/doc/ppm.html

    FILE* file = fopen(path, "r");
    if(!file) {
        silkAssignErrorMessage(SILK_ERR_FILE_OPEN_FAIL);
        return NULL;
    }

    pixel* result = (pixel*)calloc(size->x * size->y, sizeof(pixel));

    // TODO(yakub):
    // Implement the way of reading the PPM file
    // The things we need to focus on are:
    // - (Mandatory) Image's width and height;
    // - (Mandatory) Image's color information;
    // - (Optional, nice to have) We need to get the information about the maximum color channel value, then get it to our 255 maximum value;

    fclose(file);

    silkLogInfo("Image path: %s", path);
    silkLogInfo("Image resolution: x.%i, y.%i", size->x, size->y);
    silkLogInfo("Image memory size: %i", size->x * size->y * sizeof(pixel));

    return result;
}

SILK_API i32 silkSavePPM(pixel* image_buf, const string path) {
    // You can learn more about PPM format here:
    // https://netpbm.sourceforge.net/doc/ppm.html

    if(!image_buf) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);
        
        return SILK_FAILURE;
    }

    FILE* file = fopen(path, "w");
    if(!file) {
        silkAssignErrorMessage(SILK_ERR_FILE_OPEN_FAIL);
        return SILK_FAILURE;
    }

    fprintf(
        file, 
        "P6\n"      // PPM Magic Number
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
            silkPixelToColor(image_buf[i]).r,
            silkPixelToColor(image_buf[i]).g,
            silkPixelToColor(image_buf[i]).b
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

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: IO
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API string silkGetError() {
    return silk_error_msg;
}


#endif // SILK_IMPLEMENTATION

#endif // SILK_H