#!/usr/bin/env bash

# This command compiles the snowflakes.c source into a WASM binary file.
# To make the emcc command available in your environment, follow the
# instructions in the README

# The reason I set ERROR_ON_UNDEFINED_SYMBOLS to 0 is because the external
# symbols in snowflakes.c are loaded at run time (in the JS code that
# loads and instantiates the WASM module)

emcc snowflakes.c \
  -s WASM=1 -s ONLY_MY_CODE=1 \
  -s EXPORTED_FUNCTIONS="['_render_snowflakes', '_init_snowflakes']" \
  -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
  -o snowflakes.wasm
