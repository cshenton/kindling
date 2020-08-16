# Kindling

Fire starter for 3D web projects. This is a set of hand written zig bindings to
various web platform APIs that enable zig to be a complete application
development environment for the browser.

The goal is to make getting a fullscreen canvas with a webGL 2.0 context, audio,
and networking interfaces that are all callable from a webassembly module
generated from zig code.

- [X] Zig Build Generating `.wasm` module
- [X] Core Wasm Bindings (`console.log`, canvas size, etc.)
- [X] WebGL 2.0 Bindings (mostly finished)
- [ ] WebAudio Bindings
- [ ] WebSockets Bindings


## Current State

![Current State](img/hello.png)

All I do currently is create a fullscreen canvas, then render to that canvas
from inside a wasm module. This involves creating a fullscreen quad and
uploading it, compiling a shader embedded in the wasm module itself, and making
the appropriate draw calls, see `src/main.zig` for the callback functionality,
and `index.html` for how it all gets tied together in the browser.


## Building

Ensure you have a newish version of zig installed and then just:

```
zig build wasm
```

And copy `zig-cache/lib/kindling.wasm` to this directory.


## Running

To preview things in their current state just run a webserver in this directory,
you probably have python installed so the following may work.

```sh
python -m http.server
```


## How It Works

I found "all in one" solutions like emscripten and wasm-bindgen more confusing
than helpful so this is a "raw" implementation of wasm bindings. All you have to
do is define some javascript functions (like the ones in `js/webgl.js`) then
pass them into the environment when you initialise your wasm module.

To call those js functions you need corresponding function prototypes in your
wasm language (so here the corresponding bindings are in `src/webgl.zig`) and
the browser will handle linking them when the module is initialised.

It's very straightforward, with the caveat that complex types can't be passed
across that ABI, so you do sometimes need to keep objects in JS land and pass
handles to your wasm module (which is what I do with gl objects).

The great thing about doing things this way is you're not tied to someone else's
platform bindings. If you need more functionality from the browser, you just
write it.


## Credits

A big thanks to [flooh](http://github.com/floooh) for sokol and
[raulgrell](https://github.com/raulgrell) for wasm tetris. These both helped me
understand how wasm platform bindings actually work (and at least as
importantly, how to get a nice looking fullscreen canvas). 
