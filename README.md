# SimpleComponents
Component-Based 2D game engine in SDL for a simple games. 

# Build Instructions

Can be fairly painlessly setup in visual studio (I'm using vs2013). 
Clone the project and add all the .h and .cpp files into a new vs project. 
Get SDL2, SDL_image and SDL_ttf and link to the headers and libs in project settings.
Check libsdl.org for more details as to which libs to link to.
Make sure the SDL DLL's are in the output folder, (I use a post build copy command)

- https://www.libsdl.org/download-2.0.php
- https://www.libsdl.org/projects/SDL_image/
- https://www.libsdl.org/projects/SDL_ttf/

Follow a similar procedure for the test project, some of the .cpp files will need to be included. 

# Future Plans
- bunch of stuff is going to be re-written. (check the wiki)
- Use Google test instead of the visual studio test
- CMake build system for osx and windows
- *Maybe* move to proper OpenGL


