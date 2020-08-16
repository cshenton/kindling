# Kindling

Fire starter for Windows/Linux game projects, with 3D rendering, sound, and UDP based networking.


## Functionality

Provided through a mix of vendored libraries and provided code are:

- Basic 3D math
- Slotmap for game entities
- ...


## External Dependencies

Kindling is first and foremost a working build system for a set of quality 3rd
party packages I often use, these are:

- [`cgtlf`](https://github.com/jkuhlmann/cgltf) (GLTF 3D file format loader)
- [`glad`](https://github.com/Dav1dde/glad) (OpenGL Loader)
- [`glfw`](https://github.com/glfw/glfw) (Windowing)
- [`miniaudio`](https://github.com/dr-soft/miniaudio) (Audio Playback and Capture)
- [`enet`](https://github.com/zpl-c/enet) (UDP Networking Layer)
- [`librg`](https://github.com/zpl-c/librg) (Interest Middleware)

Almost all of these are single header, with the exception of glfw, which I use
precompiled binaries for.


## TODO:

- vector math
- perspective camera
- integrate cgltf
- gradually add support to represent everything in gltf
    - buffers
    - textures
    - cameras
    - skins
    - animations
    - textures
    - samplers
    - pbr materials
