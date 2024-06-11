<div align="center">

<img src="./res/images/silk_banner.svg" width=100% height=100% style="border-radius:16px 64px">

</div>

## Introduction

This is Silk - 2D single-header graphics library, which works entirely on CPU.
The soul-purpose of this library is to give you the buffer for pixels which then you can display with your windowing library of choosing.

Check out [`examples`](./examples/) to see how you can do this with some of the most popular libraries!

You can also check out [`TODO.md`](./TODO.md) file to see the possible additions in the future!

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

Possible examples in the future:
- raylib Example
- stb_image example

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
