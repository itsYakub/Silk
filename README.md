<div align="center">

<img src="./res/images/silk_banner.png" width=100% height=100%>

</div>

## Introduction

This is Silk - 2D single-header graphics library.
The soul-purpose of this library is to give you the front-end for rendering graphics immediately to the screen. Everything works on CPU, completely on stack. 
Note that you MUST provide your own rendering and/or windowing back-end to work with Silk.

```c
#include "your_backend_of_choosing.h"

#define SILK_PIXELBUFFER_WIDTH 800
#define SILK_PIXELBUFFER_HEIGHT 600

#define SILK_IMPLEMENTATION
#include "../../silk.h"

i32 main(i32 argc, const string argv[]) {
    // Setting-up the main pixel-buffer
    pixel buffer[SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT] = { 0 };

    // Set-up your back-end here ...

    while(true) {
        // Clearing the pixel-buffer to white (0xffffffff -> #FFFFFFFF -> WHITE)
        silkClearPixelBufferColor(buffer, 0xffffffff);

        // Draw the red rectangle at the position in the middle of the pixel-buffer
        silkDrawRect(
            buffer,                                                             // pixel-buffer
            (vec2i) { SILK_PIXELBUFFER_WIDTH, SILK_PIXELBUFFER_HEIGHT },        // the size of the pixel-buffer
            (vec2i) { SILK_PIXELBUFFER_CENTER_X, SILK_PIXELBUFFER_CENTER_Y },   // The position where we want to draw our red rectangle
            (vec2i) { 64, 64 },                                                 // The size of our red rectangle
            0xff0000ff                                                          // The color of our rectangle (0xff0000ff -> #FF0000FF -> RED)
        );

        // ... Blit your graphics using your back-end ...
    }

    // ... close your back-end here

    return 0;
}
```

Check out [`examples`](./examples/) to see how you can do this with some of the most popular libraries!
If you wish to extand the list of examples, check out the [`example template`](./examples/example_template/). You can also use it to build your application using Silk!

You can also check out [`TODO.md`](./TODO.md) file to see the possible additions in the future!

Lastly, check out the [`docs`](./docs/) for documentation.

## Setup
### 1. Getting started
Get the `silk.h` header file into your project:
- You can download the file directly form [GitHub](https://github.com/itsYakub/Silk/blob/main/silk.h)
- You can clone this repository ...
```console
$ git clone https://github.com/itsYakub/Silk.git
```
... and then provide the directory to include `silk.h` into your project

### 2. Project setup
Design of the single-header libraries allows us to simply include the header file in your project:

```c
#include "silk.h"
```

*WARNING:* You must, at least and no more than only once, provide the special macro `SILK_IMPLEMENTATION` in one of your source files, before the include directive:
```c
#define SILK_IMPLEMENTATION
#include "silk.h"
```
This macro tells the preprocessor to not only include the function declarations, but also their defnitions.
- Not calling this macro ever in your project causes the `undefined reference to ..` error.
- Calling this macro multiple time throughout the project causes the `multiple definitions of ..` error.

## Examples
This is the list of available examples provided by Silk:
- [PPM Example](./examples/example_ppm/)
- [X11 Example](./examples/example_x11/)
- [SDL Example](./examples/example_sdl/)
- [Raylib Example](./examples/example_raylib/)
- [STB_Image Example](./examples/example_stbi/)
- [RGFW Example](./examples/example_rgfw/)

## Credits
1. Inspiration:
- [Olive.c](https://www.youtube.com/playlist?list=PLpM-Dvs8t0Va-Gb0Dp4d9t8yvNFHaKH6N)
- [Programming a first person shooter from scratch like it's 1995](https://www.youtube.com/watch?v=fSjc8vLMg8c)
- [nothings/stb](https://github.com/nothings/stb)

2. Sources:
- [My previous project: Soft](https://github.com/itsYakub/Soft/blob/main/src/soft.c)
- [DDA Algorithm / Line-Drawing algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Circle-Drawing algorithm](https://youtu.be/LmQKZmQh1ZQ?list=PLpM-Dvs8t0Va-Gb0Dp4d9t8yvNFHaKH6N&t=3088)
- [Triangle-Drawing algorithm](https://github.com/tsoding/olive.c/commit/633c657dbea3435a64114570ecb3f703fa276f28)
- [Equations for equilateral triangle vertices](https://www.quora.com/How-do-you-calculate-the-triangle-vertices-coordinates-on-a-circumcircle-triangle-with-a-given-centre-point-and-radius-Assuming-the-triangle-is-acute-with-all-equal-length-sides-and-that-one-point-is-straight-up)

## Licence
This project is under the [MIT Licence](./LICENCE).
