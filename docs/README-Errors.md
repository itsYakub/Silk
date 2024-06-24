<div align="center">

# Silk Documentation - Error Messages

</div>

You can find the list of Silk's error messages in the **[silk.h](../silk.h)** file, under the `SECTION MODULE: Error Messages` title.

Here's the list of error messages internally used by Silk:
## General:
- **"Error message NULL or Empty."** - error message wasn't registered yet OR is set to NULL.

- **"Undefined behaviour."** - the behaviour that causes this error is undefined.

## Buffer:
- **"Passed the invalid pixel buffer."** - there was the invalid pixel buffer *(most likely: NULL)* passed to the function.

- **"Passed the invalid image buffer."** - there was the invalid image *(most likely: NULL)* passed to the function.

- **"Trying to access the out-of-bounds buffer address."** - the index we tried to access is outside of the pixel buffer's boundaries.

## File:
- **"Couldn't open the file."** - the file-opeining didn't finished correctly.