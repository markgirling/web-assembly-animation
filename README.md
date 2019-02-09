# Web Assembly Animation
This is a small demonstration of Web Assembly (WASM) working in the browser by use of a
canvas animation of some falling snowflakes!

If you aren't sure what Web Assembly is, check the 'Further Reading' section at the
bottom of this README, in particular the Web Assembly Concepts page on MDN.

Long story short, Web Assembly is essentially a new programming language for the browser.
It's a low level language not intended to be written by hand, rather you take a language
such as C or Rust and use a compiler to produce a Web Assembly binary file. You can load
and execute these binary files in the browser by using JavaScript.

Web Assembly's biggest feature is its speed. It provides a way for code to run in the
browser at near-native speeds.

Web Assembly is still very much in its early stages, but it is implemented in all
the mainstream modern browsers including Edge, Chrome, Firefox, and Safari.

# Project Overview
The project is partly implemented in JS, partly implemented in C. The C source code gets
compiled into WASM binary, the JS code runs in the browser as a normal JS program would.

You can see the JS code used in the `snowflakes-loader.js` file.

The C source code is stored in the `snowflakes.c` file.

# Development Environment Setup
Follow the instructions from the web assembly site to setup your dev environment:

http://webassembly.org/getting-started/developers-guide/

It will guide you through installing the development SDK from source.

Remember that the `emcc` and `emrun` commands, needed for compiling Web Assembly code and
launching a web server to serve it on, will not be available in your environment unless you
source the `emsdk_env.sh` file in the `emsdk` repo. See the 'Environment setup after
installation' section of the above guide. 

# Compilation
Before you can see the animation, we must compile the C source into WASM binary code. All you need
to do is run the `compile.sh` file. If you can't run it then you can copy and paste the command inside
it directly into your shell.
```sh
emcc snowflakes.c \
  -s WASM=1 -s ONLY_MY_CODE=1 \
  -s EXPORTED_FUNCTIONS="['_render_snowflakes', '_init_snowflakes']" \
  -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
  -o snowflakes.wasm
```
This will produce a file called `snowflakes.wasm`, containing the compiled WASM binary code for our C program.

# See the animation
Run this command in the project folder to start a static file web server:
```sh
emrun --no_browser --port 8080 .
```
Now browse to http://localhost:8080/index.html in your browser and you'll see a pretty, pixelly snowflake animation.

# Further Reading
- https://developer.mozilla.org/en-US/docs/WebAssembly/Concepts
- https://developer.mozilla.org/en-US/docs/WebAssembly/Using_the_JavaScript_API
- https://developer.mozilla.org/en-US/docs/WebAssembly/Understanding_the_text_format
- https://hacks.mozilla.org/2017/03/why-webassembly-is-faster-than-asm-js/
- https://medium.com/@mbebenita/lets-write-pong-in-webassembly-ac3a8e7c4591
