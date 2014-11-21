CDE Graphics 1
==============

Repository for the Graphics 1 coursework for CDE Students 2014

To see this readme with nice highlighting visit https://github.com/DrHibbitts/CDE_Graphics_1/tree/codeCleanUp

## Dependencies

* OpenGL https://www.opengl.org/
* GLFW http://www.glfw.org/
* GLEW http://glew.sourceforge.net/
* GLM http://glm.g-truc.net/
* Boost http://www.boost.org/

To install the libraries on Ubuntu 14.04 run

```
sudo apt-get install cmake  libboost1.54-dev install libxmu-dev libxi-dev mesa-common-dev libglew-dev libglm-dev g++ xorg-dev libglu1-mesa-dev
```

GLFW 3.0 is needed, so compile from source since the repository version is 2.0
```
unzip glfw-3.0.4.zip
cd glfw-3.0.4/
mkdir build
cd build
cmake ../
make -j4
sudo make install
cd ../../
rm -rf glfw-3.0.4 glfw-3.0.4.zip
```

## Compilation

To compile and run the code go into the project folder and run
```
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=Release ../
make -j4
./CDE_Graphics_1
```
## User instructions

The program starts in an idle state, and it has two states: camera and goal update, which are shown on the application
window title.
Left click enters camera mode. In camera mode mouse movements change camera orientation and keys "w,a,s,d,r,f" change camera position to forward,backward, left, right, up and down respectively.
Right click enters goal mode, where the goal can be moved with the same keys as the camera.
Shift can also be used to switch between modes.
If in goal mode enter key is pressed, the current goal position will be send to the simulation and the program will switch to camera mode automatically.
Espace to reset the camera to its initial position.
Esc key can be used to close the program.

##Troubleshooting

If the program gives a `Error linking shader program, make sure the path is correct` the edit 
`src/rendering/Renderer.cpp` lines 137-139 to match your compilation folder.
