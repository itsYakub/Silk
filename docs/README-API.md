<div align="center">

# Silk Documentation - API

</div>

You can find the official Silk API in the **[silk.h](../silk.h)** file, under the `SECTION: API` title.

## Naming convention

Rule of naming is like this:
```c
SILK_API i32 silkDoSomething(...);
```
Let's talk about it's structure:
- **`SILK_API`** - the key-word added to each publically-available function in Silk.
- **`i32`** - integer return type. Almost every Silk function returns the exit value: `SILK_SUCCESS` and `SILK_FAILURE`. Depending on the circumstances, if the functions executes without any issue it will return `SILK_SUCCESS` (Macro for the value: 0), or if there'll be some problem, and function won't execute completely (i.e. the value NULL was passed) it will return `SILK_FAILURE` (Macro for the value: 1).
- **`silkDoSomething`** - every Silk function is prefixed with the word `silk`. This is the common practice for C libraries, as this language doesn't support namespacing, thus to distinguish that the function belongs to this library it's prefixed by something connected to it.
- **`...`** - function parameters. For readability and simplicity Silk follows some simple rules of parameter naming and ordering (i.e. every buffer-manipulation function starts it's parameter list with `pixel* buf` parameter).

## Functions

API is organised by *Modules* for each separate topic and use.
The API consists of:
### 1. SECTION MODULE: Pixel buffer
- **`SILK_API i32 silkClearPixelBuffer(pixel* buf)`** - clear the pixel buffer; set all the pixels from the buffer to 0.

- **`SILK_API i32 silkClearPixelBufferRegion(pixel* buf, vec2i size)`** - clear the pixel buffer in the specified region. The range in the refresh happens is: (0, 0) -> (size.x, size.y).

- **`SILK_API i32 silkClearPixelBufferColor(pixel* buf, pixel **pix)`** - clears the pixel buffer with the color specified by `pix`.

- **`SILK_API i32 silkClearPixelBufferColorRegion(pixel* buf, vec2i size, pixel **pix)`** - clear the pixel buffer in the specified region with the color specified by `pix`. The range in the refresh happens is: (0, 0) -> (size.x, size.y).

- **`SILK_API pixel silkGetPixel(pixel* buf, vec2i position, vec2i size)`** - gets the pixel color from the specified `position`, bounded to the `size`.

- **`SILK_API i32 silkSetPixel(pixel* buf, vec2i position, vec2i size, pixel **pix)`** - sets the color of the pixel to the color `pix` at the specific `position`, bounded to the `size`.

- **`SILK_API i32 silkUnloadBuffer(pixel* buf)`** - unloads the dynamically allocated pixel buffer (i. e. images).

### 2. SECTION MODULE: Pixels and Colors
- **`SILK_API color silkPixelToColor(pixel **pix)`** - converts pixel to color;

- **`SILK_API pixel silkColorToPixel(color col)`** - converts color to pixel;

- **`SILK_API pixel silkAlphaBlend(pixel base_pixel, pixel return_pixel, color_channel value)`** - blends the pixel `return_pixel` with the `base_pixel` by the `value` color channel.

- **`SILK_API pixel silkPixelFade(pixel pix, f32 factor)`** - fades the color `pix` by the `factor` (0.0 - 1.0).

- **`SILK_API pixel silkPixelTint(pixel pix, pixel tint)`** - tints the color `pix` with the `tint`.

### 3. SECTION MODULE: Rendering
- **`SILK_API i32 silkDrawPixel(pixel* buf, vec2i position, pixel **pix)`** - draws the pixel `pix` at the specified `position`.

- **`SILK_API i32 silkDrawLine(pixel* buf, vec2i start, vec2i end, pixel **pix)`** - draws the line from `start` to `end` using the color `pix`.

- **`SILK_API i32 silkDrawRect(pixel* buf, vec2i position, vec2i size, pixel **pix)`** - draws the rectangle of a color `pix` at the specified `position` with specified `size`.

- **`SILK_API i32 silkDrawRectPro(pixel* buf, vec2i position, vec2i size, i32 angle, vec2i offset, pixel **pix)`** - draws the rectangle of a color `pix` at the specified `position`, corrected by the `offset`, with specified `size` and `angle`.

- **`SILK_API i32 silkDrawRectLines(pixel* buf, vec2i position, vec2i size, i32 angle, vec2i offset, pixel **pix)`** - draws the lines of the rectangle of a color `pix` at the specified `position`, corected by the `offset`, with specified `size` and `angle`.

- **`SILK_API i32 silkDrawCircle(pixel* buf, vec2i position, i32 radius, pixel **pix)`** - draws the circle of a color `pix` at the specified `position` with specified `radius`.

- **`SILK_API i32 silkDrawCircleLines(pixel* buf, vec2i position, i32 radius, pixel **pix)`** - draws the lines of a circle of a color `pix` at the specified `position` with specified `radius`.

- **`SILK_API i32 silkDrawTriangle(pixel* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel **pix)`** - draws the triangle of the color `pix` at the area specified by three points: `point_a`, `point_b` and `point_c`.

- **`SILK_API i32 silkDrawTriangleLines(pixel* buf, vec2i point_a, vec2i point_b, vec2i point_c, pixel **pix)`** - draws the lines of a triangle of the color `pix` at the area specified by three points: `point_a`, `point_b` and `point_c`.

- **`SILK_API i32 silkDrawTriangleEquilateral(pixel* buf, vec2i position, i32 radius, i32 angle, pixel **pix)`** - draws the equilateral triangle of the color `pix` at the specified `position` with specified `radius` and `angle`.

- **`SILK_API i32 silkDrawTriangleEquilateralLines(pixel* buf, vec2i position, i32 radius, i32 angle, pixel **pix)`** - draws the lines of a equilateral triangle of the color `pix` at the specified `position` with specified `radius` and `angle`.

- **`SILK_API i32 silkDrawPolygon(pixel* buf, vec2i position, i32 radius, i32 angle, i32 n, pixel **pix)`** - draws the `n`-sided polygon of the color `pix` at the specified `position` with specified `radius` and `angle`.

- **`SILK_API i32 silkDrawStar(pixel* buf, vec2i position, i32 radius, i32 angle, i32 n, pixel **pix)`** - draws the `n`-armed star of the color `pix` at the specified `position` with specified `radius` and `angle`.

- **`SILK_API i32 silkDrawBuffer(pixel* buf, pixel* img_buf, vec2i position, vec2i size)`** - draws the image buffer `img_buf` at the specified `position` with specified `size`.

- **`SILK_API i32 silkDrawBufferScaled(pixel* buf, pixel* img_buf, vec2i position, vec2i size_src, vec2i size_dest)`** - draws the image buffer `img_buf` at the specified `position`, scaled from `size_src` to `size_dest`.

- **`SILK_API i32 silkDrawBufferPro(pixel* buf, pixel* img_buf, vec2i position, vec2i offset, vec2i size_src, vec2i size_dest, pixel tint)`** - draws the image buffer `img_buf` tinted with `tint` at the specified `position`, corrected by the `offset`, scaled from `size_src` to `size_dest`.

*NOTE: Before we start we should mention the structure of these function parameters. Let's see:*
```c
SILK_API i32 silkDrawRectLines(
    pixel* buf, 
    vec2i position, 
    vec2i size, 
    i32 angle, 
    vec2i offset, 
    pixel pix
)
```
*This function consists of the simple parameter structure that every other rendering function adapt:*
- `pixel* buf` - pixel buffer that we renders into;
- `vec2i position` - position at which we want to render our object;
- `vec2i size` / `i32 radius` - the size or the radius of the object;
- `vec2i offset` - the origin point of drawing our object, relative to it's position;
- `pixel pix` / `pixel tint` - the color of our object OR the tint of our object;

### 4. SECTION MODULE: Logging
- **`SILK_API i32 silkLogInfo(const string text, ...)`** - prints the information message to the console (prefixed with: **[INFO]**).
- **`SILK_API i32 silkLogWarn(const string text, ...)`** - prints the warning message to the console (prefixed with: **[WARN]**).
- **`SILK_API i32 silkLogErr(const string text, ...)`** - prints the error message to the console (prefixed with: **[ERR]**).
- **`SILK_API i32 silkLogAlphaBlendStatus()`** - prints the current state of alpha-blending (**ENABLED|DISABLED**).
- **`SILK_API i32 silkLogByteOrderStatus()`** - prints the current byte ordering (**LITTLE ENDIAN|BIG ENDIAN**).

### 5. SECTION MODULE: Math
- **`SILK_API i32 silkVectorSwap(vec2i* a, vec2i* b)`** - swaps the vector `a` with `b` and vice versa.
- **`SILK_API i32 silkIntSwap(i32* a, i32* b)`** - swaps the integer `a` with `b` and vice versa.

### 6. SECTION MODULE: IO
- **`SILK_API pixel* silkLoadPPM(const string path, vec2i* size)`** - deserializes the PPM image format from the `path` and sets the `size` vector to it's resolution.
- **`SILK_API i32 silkSavePPM(pixel* buf, const string path)`** - serializes the PPM image format to the `path`.

### 7. SECTION MODULE: Error-Logging
- **`SILK_API string silkGetError()`** - prints the latest internal error to the console.