**HNE (The Honored Engine)** is a custom 2D game engine written from scratch in C++ using OpenGL.

The goal is to learn how game engines actually work by building the systems myself instead of relying on an existing game engine or framework.

## What I'm Building

HNE is focused on 2D games, with the engine eventually handling things like:

- Rendering
- Window management
- Input
- Textures
- Sprites
- Audio
- Game objects
- Scenes
- Asset management

I'm building the systems incrementally and keeping the engine as lightweight and low-level as possible.

## Current State

Currently, HNE can:

- Create an OpenGL window through GLFW
- Initialize OpenGL through GLAD
- Load external GLSL shaders
- Create vertex buffers and vertex arrays
- Compile and link shaders
- Render a basic triangle

## Building

### Requirements

- C++ compiler (MinGW/GCC)
- CMake
- vcpkg

### Build

###### For Windows (WIN32)
```powershell
./build
```

###### For GNU/Linux (Linux)
```bash
sudo apt install ninja  # If debian/debian-based
sudo pacman -S ninja    # If arch/arch-based
./build.sh
```
