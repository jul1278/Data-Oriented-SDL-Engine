# SimpleComponents
Component-Based 2D game engine in SDL for a simple games. 

If you'd like to know more about component based design, here's a few links to get started:
- http://www.randygaul.net/2013/05/20/component-based-engine-design/
- https://www.raywenderlich.com/24878/introduction-to-component-based-architecture-in-games

# Build Instructions

### OSX

Make sure you have the following libraries in your frameworks folder.

- https://www.libsdl.org/download-2.0.php
- https://www.libsdl.org/projects/SDL_image/
- https://www.libsdl.org/projects/SDL_ttf/

Clone the branch for osx_build (not the master one!) and navigate to the SimpleComponents folder. 

```
mkdir Build
cd Build
cmake ..
```

This *should* clone the latest google test, generate a makefile for the main project and test project. 
Finally just run make to build the thing. 

### Windows

Can be fairly painlessly setup in visual studio, make sure you clone the windows_build branch. 

# Future Plans
- bunch of stuff is going to be re-written. (check the wiki)
- Use Google test instead of the visual studio test
- CMake build system for osx and windows
- *Maybe* move to proper OpenGL

# Contributing

ok sure



