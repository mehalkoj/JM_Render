# JM Render

A custom software rasterizer with its own mini math lib, that uses SDL3 and Imgui. This project was created due to being curious about how
graphics work at the lower end of things, so what graphics APIs like Vulkan and OpenGL do underneath the hood. The features lists will
expand as I have other ideas for this project and plan on doing a release file as a toy to play with.

## Features

- [x] Wireframe Drawing
- [x] Triangle Rasterization
- [x] OBJ Model Importing
- [x] Math Library
- [ ] 3D
- [ ] Camera Controls
- [ ] Lighting
- [ ] Shadows 

## Wireframe
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/4d2a91b7-6e3f-4fbb-a203-af2e74df347c" />

### Tiny Renderer Normalized Model
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/610f5c56-2d52-4303-a71c-da876f3d7389" />


## Triangle Filling
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/9b076fa9-2949-4178-b8a0-ad5766201575" />

### Tiny Renderer Normalized Model
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/fcd3b7a1-8332-434e-8edf-6d2fc6ef6c3c" />


## Build
### Requirements
- Visual Studio 2022
- SDL3
- Dear ImGui

### Setup
1. Clone the repo
2. Open `JM_Render.sln` in Visual Studio
3. Ensure SDL3 and ImGui are linked (see their docs for setup)
4. Build and run

## References
[scratchapixel.com](https://www.scratchapixel.com/index.html)

[tinyrenderer](https://haqr.eu/)

[A trip through the Graphics Pipeline 2011](https://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/)

[A Parallel Algorithm for Polygon Rasterization](https://www.cs.drexel.edu/~deb39/Classes/Papers/comp175-06-pineda.pdf)

[Algorithm for computer control of a digital plotter](https://web.archive.org/web/20080528040104/http://www.research.ibm.com/journal/sj/041/ibmsjIVRIC.pdf)



Fundamentals of Computer Graphics Third Edition by Steve Marschner and Peter Shirley

