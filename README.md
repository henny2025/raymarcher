# Raymarcher 

An OpenGL-based raymarcher for rendering geometries difficult to represent in traditional polygon-based rendering schemes. Think fractals and other smooth parametrically-defined surfaces. Should be efficient enough to run as a real-time graphics application with good enough hardware though my laptop has not been able to do this.

# Installation
## Linux
1. Clone this repository
2. Install SDL2, OpenGL, and GLEW
3. Build and install using these commands from within the root directory of this repo
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
sudo cmake --install .
```
