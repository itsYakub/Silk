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
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include <stdint.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Macro Definitions
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_API

#define SILK_SUCCESS 0 // SILK_SUCCESS: returned if the function was executed successfully
#define SILK_FAILURE 1 // SILK_FAILURE: returned if there was a problem during the function execution

#ifndef SILK_PIXELBUFFER_WIDTH
    #define SILK_PIXELBUFFER_WIDTH 1920 // SILK_PIXELBUFFER_WIDTH: Default Full HD monitor width
#endif // SILK_PIXELBUFFER_WIDTH

#ifndef SILK_PIXELBUFFER_HEIGHT
    #define SILK_PIXELBUFFER_HEIGHT 1080 // SILK_PIXELBUFFER_HEIGHT: Default Full HD monitor height
#endif // SILK_PIXELBUFFER_HEIGHT

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Typedefs
// --------------------------------------------------------------------------------------------------------------------------------

typedef int                                             i32;
typedef uint8_t                                         u8;
typedef float                                           f32;
typedef unsigned int                                    u32;
typedef struct { i32 x; i32 y; }                        vec2i;
typedef struct { u8 r; u8 g; u8 b; u8 a; }              color;

typedef uint8_t                                         color_channel;
typedef uint32_t                                        pixel;
typedef struct { pixel* buffer; vec2i size; }           pixel_buffer;


// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function declarations
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API pixel_buffer silkCreatePixelBuffer(u32 width, u32 height);
SILK_API pixel_buffer silkCreatePixelBufferDefault();

SILK_API i32 silkPixelBufferFree(pixel_buffer* buf);

SILK_API i32 silkClearPixelBuffer(pixel_buffer* buf);
SILK_API i32 silkClearPixelBufferColor(pixel_buffer* buf, pixel pix);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API color silkPixelToColor(pixel pix);
SILK_API pixel silkColorToPixel(color col);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel_buffer* buf, vec2i position, pixel pix);
SILK_API i32 silkDrawLine(pixel_buffer* buf, vec2i start, vec2i end, pixel pix);
SILK_API i32 silkDrawRect(pixel_buffer* buf, vec2i position, vec2i size, pixel pix);
SILK_API i32 silkDrawCircle(pixel_buffer* buf, vec2i position, i32 radius, pixel pix);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Implementation
// --------------------------------------------------------------------------------------------------------------------------------

#ifdef SILK_IMPLEMENTATION

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include <string.h>
#include <stdlib.h>
#include <math.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function definitions
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API pixel_buffer silkCreatePixelBuffer(u32 width, u32 height) {
    pixel_buffer result = {
        .buffer = (pixel*) calloc(width * height, sizeof(pixel)),
        .size = { width, height }
    };

    return result;
}

SILK_API pixel_buffer silkCreatePixelBufferDefault() {
    pixel_buffer result = silkCreatePixelBuffer(SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT);

    return result;
}

SILK_API i32 silkPixelBufferFree(pixel_buffer* buf) {
    if(!buf->buffer) {
        return SILK_FAILURE;
    }

    free(buf->buffer);

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBuffer(pixel_buffer* buf) {
    if(!buf) {
        return SILK_FAILURE;
    }

    for(i32 pixel = 0; pixel < buf->size.x * buf->size.y; pixel++) {
        buf->buffer[pixel] = 0;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColor(pixel_buffer* buf, pixel pix) {
    if(!buf) {
        return SILK_FAILURE;
    }

    for(i32 pixel = 0; pixel < buf->size.x * buf->size.y; pixel++) {
        buf->buffer[pixel] = pix;
    }

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Pixels and Colors
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

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel_buffer* buf, vec2i position, pixel pix) {
    if(!buf) {
        return SILK_FAILURE;
    }

    if( (position.x < 0 || position.x >= buf->size.x) ||
        (position.y < 0 || position.y >= buf->size.y)) {
        return SILK_FAILURE;
    }

    buf->buffer[position.y * buf->size.x + position.x] = pix;

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRect(pixel_buffer* buf, vec2i position, vec2i size, pixel pix) {
    if(!buf) {
        return SILK_FAILURE;
    }

    for(int y = 0; y < size.y; y++) {
        for(int x = 0; x < size.x; x++) {
            silkDrawPixel(buf, (vec2i) { position.x + x, position.y + y}, pix);
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawLine(pixel_buffer* buf, vec2i start, vec2i end, pixel pix) {
    if(!buf) {
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

SILK_API i32 silkDrawCircle(pixel_buffer* buf, vec2i position, i32 radius, pixel pix) {
    if(!buf) {
        return SILK_FAILURE;
    }

    i32 x0 = position.x - radius;
    i32 x1 = position.x + radius;

    i32 y0 = position.y - radius;
    i32 y1 = position.y + radius;

    for(i32 y = y0; y < y1; y++) {
        for(i32 x = x0; x < x1; x++) {
            i32 x_delta = x - position.x;
            i32 y_delta = y - position.y;

            if((x_delta * x_delta) + (y_delta * y_delta) <= (radius * radius)) {
                silkDrawPixel(buf, (vec2i) { x, y }, pix);
            }
        }
    }

    return SILK_SUCCESS;
}

#endif // SILK_IMPLEMENTATION

#endif // SILK_H