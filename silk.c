// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include "silk.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Function definitions
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

    memset(
        buf->buffer, 
        0, 
        SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT * sizeof(pixel)
    );

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

            if(sqrt(x_delta) + sqrt(y_delta) <= sqrt(radius)) {
                silkDrawPixel(buf, (vec2i) { x, y }, pix);
            }
        }
    }

    return SILK_SUCCESS;
}