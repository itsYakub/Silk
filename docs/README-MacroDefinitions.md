<div align="center">

# Silk Documentation - Macro Definitions

</div>

You can find the list of Macro Definitions in the **[silk.h](../silk.h)** file, under the `SECTION: Macro Definitions` title.

Here's the list of available macro definitions:
- `SILK_IMPLEMENTATION` - This macro includes function definitions to the project, during the *preprocessor* compilation stage. 

*NOTE: This macro MUST be included only once. Otherwise there will be a multiple-definition error!*

- `SILK_ALPHA_IGNORE` - Ignore alpha-channel during the color calculations. 

*NOTE: This macro disables alpha-blending, even if you define the `SILK_ALPHABLEND_ENABLE` macro.*

- `SILK_ALPHABLEND_ENABLE` - Enables alpha-blending.

*NOTE: This macro is defined by default. You can disable it by defining `SILK_ALPHABLEND_DISABLE`.*

- `SILK_ALPHABLEND_DISABLE` - Disables alpha-blending.

- `SILK_BYTEORDER_LITTLE_ENDIAN` - Byte order is little endian.

- `SILK_BYTEORDER_BIG_ENDIAN` - Byte order is big endian.

- `SILK_DISABLE_LOG_INFO` - Disables info-logging.

- `SILK_DISABLE_LOG_WARN` - Disables warn-logging.

- `SILK_DISABLE_LOG_ERR` - Disables error-logging.

- `SILK_DISABLE_LOG_ALL` - Completely disables all logging (info, warn and err).