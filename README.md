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
Clone the windows_build branch.

Make sure you have the following libraries (with .h includes)

- https://www.libsdl.org/download-2.0.php
- https://www.libsdl.org/projects/SDL_image/
- https://www.libsdl.org/projects/SDL_ttf/

In order to build the test project, you'll need to setup the google test framework, follow the instructions here: 
http://www.bogotobogo.com/cplusplus/google_unit_test_gtest.php

Go into the project settings for SimpleComponents and SimpleComponentsTest and make sure the library and
include paths point to the right locations (SDL libs and .h files, GoogleTest lib and .h files).

Finally you'll need to copy the following DLL's from the SDL lib folders so they are in the .exe output folder (I'd reccomend setting up a post build macro in vs)

libfreetype-6.dll
libpng16-16.dll
SDL2.dll
SDL2_image.dll
SDL2_ttf.dll

# Future Plans
- bunch of stuff is going to be re-written. (check the wiki)
- Use Google test instead of the visual studio test
- CMake build system for osx and windows
- *Maybe* move to proper OpenGL

# Contributing

Sure



