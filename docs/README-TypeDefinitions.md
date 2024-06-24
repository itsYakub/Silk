<div align="center">

# Silk Documentation - Type Definitions

</div>

You can find the list of Type Definitions in the **[silk.h](../silk.h)** file, under the `SECTION: Typedefs` title.

Here's the list of available macro definitions:
- `i32` - 32-bit signed integer variable | **int**;
- `f32` - 32-bit floating-point variable | **float**;
- `u8` - 8-bit unsigned integer variable | **unsigned char**;
- `u32` - 32-bit unsigned integer variable | **unsigned int**;
- `string` - array of characters | **char***;
- `color_channel` - singular color channel | **u8**;
- `pixel` - singular pixel | **u32**;
- `vec2i` - struct of two integers: x, y | **struct { i32 x; i32 y };**
- `color` - struct of four color channels: r, g, b, a | **struct { color_channel r; color_channel g; color_channel b; color_channel a; };**
