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

#ifndef SILK_H
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
typedef struct { pixel* buffer; vec2i size; }           pixel_buffer;


// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function declarations
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API pixel_buffer silkCreatePixelBuffer(u32 width, u32 height);
SILK_API pixel_buffer silkCreatePixelBufferDefault();

SILK_API i32 silkPixelBufferFree(pixel_buffer* buf);

SILK_API i32 silkClearPixelBuffer(pixel_buffer* buf);
SILK_API i32 silkClearPixelBufferRegion(pixel_buffer* buf, vec2i region);
SILK_API i32 silkClearPixelBufferColor(pixel_buffer* buf, pixel pix);
SILK_API i32 silkClearPixelBufferColorRegion(pixel_buffer* buf, vec2i region, pixel pix);

SILK_API pixel silkGetPixel(pixel_buffer* buf, vec2i position);
SILK_API i32 silkSetPixel(pixel_buffer* buf, vec2i position, pixel pix);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API color silkPixelToColor(pixel pix);
SILK_API pixel silkColorToPixel(color col);
SILK_API pixel silkAplhaBlend(pixel base_pixel, pixel return_pixel, color_channel value);

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel_buffer* buf, vec2i position, pixel pix);

SILK_API i32 silkDrawLine(pixel_buffer* buf, vec2i start, vec2i end, pixel pix);

SILK_API i32 silkDrawRect(pixel_buffer* buf, vec2i position, vec2i size, pixel pix);
SILK_API i32 silkDrawRectLines(pixel_buffer* buf, vec2i position, vec2i size, pixel pix);

SILK_API i32 silkDrawCircle(pixel_buffer* buf, vec2i position, i32 radius, pixel pix);

SILK_API i32 silkDrawTriangle(pixel_buffer* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix);
SILK_API i32 silkDrawTriangleEquilateral(pixel_buffer* buf, vec2i midpoint, i32 radius, pixel pix);

SILK_API i32 silkDrawTriangleLines(pixel_buffer* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix);
SILK_API i32 silkDrawTriangleEquilateralLines(pixel_buffer* buf, vec2i midpoint, i32 radius, pixel pix);

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
// SECTION: Implementation
// --------------------------------------------------------------------------------------------------------------------------------

#ifdef SILK_IMPLEMENTATION

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include "silk.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_TEXT_BUFFER_SIZE 256

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function definitions
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API pixel_buffer silkCreatePixelBuffer(u32 width, u32 height) {
    pixel_buffer result = {
        .buffer = (pixel*) calloc(width * height, sizeof(pixel)),
        .size = { width, height }
    };

    silkLogInfo("PIXEL_BUFFER: New pixel buffer: %ix%i", width, height);

    return result;
}

SILK_API pixel_buffer silkCreatePixelBufferDefault() {
    pixel_buffer result = silkCreatePixelBuffer(SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT);

    return result;
}

SILK_API i32 silkPixelBufferFree(pixel_buffer* buf) {
    if(!buf->buffer) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    silkLogInfo("PIXEL_BUFFER: Unloading the pixel buffer.");

    free(buf->buffer);

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBuffer(pixel_buffer* buf) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    for(i32 pixel = 0; pixel < buf->size.x * buf->size.y; pixel++) {
        buf->buffer[pixel] = 0;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferRegion(pixel_buffer* buf, vec2i region) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < region.y; y++) {
        for(i32 x = 0; x < region.x; x++) {
            silkSetPixel(buf, (vec2i) { x, y }, 0);
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColor(pixel_buffer* buf, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    for(i32 pixel = 0; pixel < buf->size.x * buf->size.y; pixel++) {
        buf->buffer[pixel] = pix;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColorRegion(pixel_buffer* buf, vec2i region, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < region.y; y++) {
        for(i32 x = 0; x < region.x; x++) {
            silkSetPixel(buf, (vec2i) { x, y }, pix);
        }
    }

    return SILK_SUCCESS;
}

SILK_API pixel silkGetPixel(pixel_buffer* buf, vec2i position) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return 0xffffffff;
    }

    return buf->buffer[position.y * buf->size.x + position.x];
}

SILK_API i32 silkSetPixel(pixel_buffer* buf, vec2i position, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    buf->buffer[position.y * buf->size.x + position.x] = pix;

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

SILK_API pixel silkAplhaBlend(pixel base_pixel, pixel return_pixel, color_channel value) {
    color result = { 0 };
    color base_color = silkPixelToColor(base_pixel);
    color return_color = silkPixelToColor(return_pixel);

    result.r = base_color.r + (return_color.r - base_color.r) * (value / 255.0f);
    result.g = base_color.g + (return_color.g - base_color.g) * (value / 255.0f);
    result.b = base_color.b + (return_color.b - base_color.b) * (value / 255.0f);
    result.a = value;

    return silkColorToPixel(result);
}

// --------------------------------------------------------------------------------------------------------------------------------
// SUB-SECTION: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel_buffer* buf, vec2i position, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    if( (position.x < 0 || position.x >= buf->size.x) ||
        (position.y < 0 || position.y >= buf->size.y)) {
        return SILK_FAILURE;
    }

    // If the pixel from this position is the same as the pixel we want to draw, we can return, 
    // as there won't be any change in this specific position.
    if(silkGetPixel(buf, position) == pix) {
        return SILK_SUCCESS;
    }

#if !defined(SILK_DISABLE_ALPHABLEND) || defined(SILK_ENABLE_ALPHABLEND)

    pix = silkAplhaBlend(
        buf->buffer[position.y * buf->size.x + position.x], 
        pix, 
        silkPixelToColor(pix).a
    );

#endif

    silkSetPixel(buf, position, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawLine(pixel_buffer* buf, vec2i start, vec2i end, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");

        return SILK_FAILURE;
    }

    f32 dx = end.x - start.x;
    f32 dy = end.y - start.y;
    f32 steps = 0;
    f32 i = 0;

    f32 x = 0;
    f32 y = 0;

    if (abs((i32)(dx)) >= abs((i32)(dy))) {
        steps = abs((i32)(dx));
    } else {
        steps = abs((i32)(dy));
    }

    dx = dx / steps;
    dy = dy / steps;
    x = start.x;
    y = start.y;

    while (i <= steps) {
        silkDrawPixel(buf, (vec2i) { x, y } , pix);
        x += dx;
        y += dy;
        i++;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRect(pixel_buffer* buf, vec2i position, vec2i size, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
        return SILK_FAILURE;
    }

    for(i32 y = 0; y < size.y; y++) {
        for(i32 x = 0; x < size.x; x++) {
            silkDrawPixel(buf, (vec2i) { position.x + x, position.y + y}, pix);
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRectLines(pixel_buffer* buf, vec2i position, vec2i size, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
        return SILK_FAILURE;
    }

    silkDrawLine(buf, (vec2i) { position.x, position.y }, (vec2i) { position.x + size.x, position.y }, pix);
    silkDrawLine(buf, (vec2i) { position.x, position.y }, (vec2i) { position.x, position.y + size.y }, pix);
    silkDrawLine(buf, (vec2i) { position.x + size.x, position.y }, (vec2i) { position.x + size.x, position.y + size.y }, pix);
    silkDrawLine(buf, (vec2i) { position.x, position.y + size.y }, (vec2i) { position.x + size.x, position.y + size.y }, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawCircle(pixel_buffer* buf, vec2i position, i32 radius, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
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

SILK_API i32 silkDrawTriangle(pixel_buffer* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix) {
    // Source:
    // https://github.com/tsoding/olive.c/commit/633c657dbea3435a64114570ecb3f703fa276f28

    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
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
        if(y > 0 && y < buf->size.y) {
            i32 s1 = delta_vector_ab.y != 0 ? 
                (y - point_a.y) * delta_vector_ab.x / delta_vector_ab.y + point_a.x : 
                point_a.x;

            i32 s2 = delta_vector_ac.y != 0 ? 
                (y - point_a.y) * delta_vector_ac.x / delta_vector_ac.y + point_a.x : 
                point_a.x;

            if(s1 > s2) {
                silkIntSwap(&s1, &s2);
            }

            for(i32 x = s1; x < s2; x++) {
                if (x > 0 && x < buf->size.x) {
                    silkDrawPixel(buf, (vec2i) { x, y }, pix);
                }
            }
        }
    }

    for(i32 y = point_b.y; y < point_c.y; y++) {
        if(y > 0 && y < buf->size.y) {
            i32 s1 = delta_vector_cb.y != 0 ? 
                (y - point_c.y) * delta_vector_cb.x / delta_vector_cb.y + point_c.x : 
                point_c.x;

            i32 s2 = delta_vector_ca.y != 0 ? 
                (y - point_c.y) * delta_vector_ca.x / delta_vector_ca.y + point_c.x : 
                point_c.x;

            if(s1 > s2) {
                silkIntSwap(&s1, &s2);
            }

            for(i32 x = s1; x < s2; x++) {
                if (x > 0 && x < buf->size.x) {
                    silkDrawPixel(buf, (vec2i) { x, y }, pix);
                }
            }
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleEquilateral(pixel_buffer* buf, vec2i midpoint, i32 radius, pixel pix) {
    // Source:
    // https://www.quora.com/How-do-you-calculate-the-triangle-vertices-coordinates-on-a-circumcircle-triangle-with-a-given-centre-point-and-radius-Assuming-the-triangle-is-acute-with-all-equal-length-sides-and-that-one-point-is-straight-up

    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
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

    silkDrawTriangle(buf, point_a, point_b, point_c, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleLines(pixel_buffer* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
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

SILK_API i32 silkDrawTriangleEquilateralLines(pixel_buffer* buf, vec2i midpoint, i32 radius, pixel pix) {
    if(!buf) {
        silkLogErr("Passed the invalid pixel buffer.");
        
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

#endif // SILK_IMPLEMENTATION

#endif // SILK_H