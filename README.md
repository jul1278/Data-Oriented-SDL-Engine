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

mkdir Build
cd Build
cmake ..

This *should* clone the latest google test, generate a makefile for the main project and test project. 
Finally just run make to build the thing. 

### Windows

Can be fairly painlessly setup in visual studio (I'm using vs2013). 
Clone the project and add all the .h and .cpp files into a new vs project. 
Get SDL2, SDL_image and SDL_ttf and link to the headers and libs in project settings.
Check libsdl.org for more details as to which libs to link to.
Make sure the SDL DLL's are in the output folder, (I use a post build copy command)

- https://www.libsdl.org/download-2.0.php
- https://www.libsdl.org/projects/SDL_image/
- https://www.libsdl.org/projects/SDL_ttf/

In order to build the test project, you'll need to setup the google test framework, follow the instructions here: 
http://www.bogotobogo.com/cplusplus/google_unit_test_gtest.php

# Future Plans
- bunch of stuff is going to be re-written. (check the wiki)
- Use Google test instead of the visual studio test
- CMake build system for osx and windows
- *Maybe* move to proper OpenGL

# Contributing

ok sure



