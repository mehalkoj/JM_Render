# JM Render
<img width="400" height="250" alt="2026-06-2116-25-50-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/23bafe6a-5bc2-4c50-8da2-e8658a4838a7" /> <img width="400" height="250" alt="2026-06-2116-26-46-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/a7fccd43-4cf6-4a70-8b8b-763707bf6427" />



A custom software rasterizer with its own mini math lib, that uses SDL3 and Imgui. This project was created due to being curious about how
graphics work at the lower end of things, so what graphics APIs like Vulkan and OpenGL do underneath the hood. The features lists will
expand as I have other ideas for this project and plan on doing a release file as a toy to play with.

## Features

- [x] Wireframe Drawing
- [x] Triangle Rasterization
- [x] OBJ Model Importing
- [x] Math Library
- [x] 3D/perspective
- [x] z-buffer
- [x] Flat Shading
- [ ] Camera Controls
- [ ] Lighting
- [ ] Shadows 

## Wireframe
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/4d2a91b7-6e3f-4fbb-a203-af2e74df347c" />

## Triangle Filling
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/9b076fa9-2949-4178-b8a0-ad5766201575" />

### Normalized Model
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/a5da56dc-8927-4cc1-9ccb-f3d4096c265f" />

### Shaded Teapot
<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/b555b28f-827d-4a37-ae7a-9bead2a32700" />

<img width="600" height="430" alt="2026-06-2116-26-46-ezgif com-video-to-gif-converter" src="https://github.com/user-attachments/assets/a7fccd43-4cf6-4a70-8b8b-763707bf6427" />



## Build
### Requirements
- Visual Studio 2022
- SDL3
  
### Setup
1. Clone the repo
2. Open `JM_Render.sln` in Visual Studio
3. Ensure SDL3 are linked (see their docs for setup)
4. Build and run

## References
[scratchapixel.com](https://www.scratchapixel.com/index.html)

[tinyrenderer](https://haqr.eu/)

[A trip through the Graphics Pipeline 2011](https://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/)

[A Parallel Algorithm for Polygon Rasterization](https://www.cs.drexel.edu/~deb39/Classes/Papers/comp175-06-pineda.pdf)

[Algorithm for computer control of a digital plotter](https://web.archive.org/web/20080528040104/http://www.research.ibm.com/journal/sj/041/ibmsjIVRIC.pdf)
[Computer Graphics from Scratch by Gabriel Gambetta](https://gabrielgambetta.com/computer-graphics-from-scratch/)


Fundamentals of Computer Graphics Third Edition by Steve Marschner and Peter Shirley

