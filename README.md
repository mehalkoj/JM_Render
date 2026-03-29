# JM Render

A custom software rasterizer with its own mini math lib, that uses SDL3 and Imgui. This project was created due to being curious about how
graphics work at the lower end of things, so what graphics APIs like Vulkan and OpenGL do underneath the hood. This document will be updated
with progress as well as additional features planned, and I do plan to build a release file when it has a user interface and has interactivity.

## Features

- [x] Wireframe Drawing
- [x] Triangle Rasterization
- [ ] Z-Buffer
- [ ] Camera Controls
- [ ] 3d Model Import
- [ ] Lighting
- [ ] Shadows
- [ ] Math Library

<img width="600" height="430" alt="image" src="https://github.com/user-attachments/assets/4d2a91b7-6e3f-4fbb-a203-af2e74df347c" />


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
[scratchapixel.com](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage.html)
[tinyrenderer](https://haqr.eu/tinyrenderer/rasterization/#properties-of-a-good-triangle-filling-algorithm)

[A Parallel Algorithm for Polygon Rasterization](https://www.cs.drexel.edu/~deb39/Classes/Papers/comp175-06-pineda.pdf)
[Algorithm for computer control of a digital plotter](https://web.archive.org/web/20080528040104/http://www.research.ibm.com/journal/sj/041/ibmsjIVRIC.pdf)

Fundamentals of Computer Graphics Third Edition by Steve Marschner and Peter Shirley
