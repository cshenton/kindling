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

