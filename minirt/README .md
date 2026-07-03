# miniRT

A simple ray tracer implemented as part of the 42 Berlin curriculum.

---

## Overview

miniRT is a computer graphics project that renders 3D scenes using the ray tracing technique in C. It reads a scene description from a `.rt` file and generates a rendered image, computing how simulated light rays interact with geometric objects to produce realistic lighting, shadows, and reflections of ambient and diffuse light.  
This project helped me master the mathematical foundations of computer graphics: vector operations, ray-object intersection, and lighting models.

**Course:** 42 Berlin — 2025 (Rank 04)

---

## Key Features

- Ray tracing engine rendering 3D scenes from `.rt` configuration files.  
- Geometric objects: **planes**, **spheres**, and **cylinders**.  
- Lighting model with ambient and diffuse light (Phong-based shading).  
- Hard shadows cast by objects blocking light sources.  
- Configurable camera with adjustable position, orientation, and field of view.  
- Scene elements: ambient lighting, camera, and light sources.  
- Real-time window management using the classic MiniLibX library.  
- Robust `.rt` file parser with error handling for malformed scenes.  
- Clean window handling: close via `ESC` key or window cross.  

---

## Architecture & Design

- **Parser:** Reads and validates the `.rt` scene file, checking each element's identifier, values, and ranges before building the scene.  
- **Ray Tracer:** For each pixel, casts a ray from the camera into the scene and computes the closest intersection.  
- **Intersection Engine:** Dedicated math for ray-plane, ray-sphere, and ray-cylinder intersections.  
- **Lighting:** Computes ambient and diffuse contributions per intersection point, with shadow rays to detect occlusion.  
- **Rendering:** Writes computed colors to an image buffer displayed through MiniLibX.  

**Design choices:**  
- Modular architecture separating parsing, math/vector operations, intersections, and rendering.  
- Custom vector math library for dot products, normalization, and cross products.  
- Scene objects handled through a unified structure for extensibility.  

---

## Scene File Format

Scenes are described in `.rt` files. Each line begins with an identifier followed by its parameters:

| Identifier | Element | Example |
|------------|---------|---------|
| `A` | Ambient light (ratio, RGB) | `A 0.2 255,255,255` |
| `C` | Camera (position, orientation, FOV) | `C 0,3,-12 0,0,1 70` |
| `L` | Light (position, brightness, RGB) | `L 0,8,-5 0.9 255,255,255` |
| `pl` | Plane (point, normal, RGB) | `pl 0,0,0 0,1,0 180,180,180` |
| `sp` | Sphere (center, diameter, RGB) | `sp 0,2,5 3 255,0,0` |
| `cy` | Cylinder (center, axis, diameter, height, RGB) | `cy -5,4,5 0,1,0 1.5 8 0,0,255` |

Example scene (`walls.rt`):

```
A 0.2 255,255,255
C 0,3,-12 0,0,1 70
L 0,8,-5 0.9 255,255,255

pl 0,0,0   0,1,0   180,180,180    # floor
pl 0,0,10  0,0,-1  200,200,200    # back wall

sp 0,2,5 3 255,0,0
```

The `scenes/` folder includes 13 different test scenes to demonstrate various object combinations and camera setups.

---

## Installation / Build

Tested on Linux (Ubuntu recommended):

```bash
# Clone repo
git clone https://github.com/Gmasfisch/gustavo-portfolio.git
cd gustavo-portfolio/miniRT

# Build the ray tracer
make
```

---

## Usage

```bash
# Run with a scene file:
./miniRT scenes/walls.rt

# Try other scenes:
./miniRT scenes/walls.rt
./miniRT scenes/walls3.rt
```

**Controls:**
- `ESC` — close the window and exit.  
- Window cross — close the window and exit.  

---

## Challenges & Solutions

- **Ray-cylinder intersection:** The most complex math of the project. Solved by breaking the cylinder into its body (quadratic equation) and its two caps, then selecting the closest valid hit.  
- **Vector normalization:** Ensured all orientation and normal vectors were correctly normalized to avoid distorted rendering and lighting artifacts.  
- **Scene parsing:** Built a strict parser that validates ranges (e.g. color values 0–255, ratios 0.0–1.0) and reports clear errors for malformed files.  
- **Shadow computation:** Implemented shadow rays cast from intersection points toward light sources to determine occlusion.  

---

## Learning Outcomes

- Mathematical foundations of computer graphics: vectors, dot/cross products, and geometry.  
- Ray-object intersection algorithms for planes, spheres, and cylinders.  
- Lighting and shading models (ambient and diffuse light).  
- Hands-on experience with the MiniLibX graphics library and image buffers.  
- Improved debugging and problem-solving skills under mathematical constraints.  

---

## Project Status

✅ Completed (mandatory part: planes, spheres, and cylinders with ambient and diffuse lighting).

---

## Author / Contact

Gustavo Fischbach — 42 Berlin (rank 04)  
**GitHub Portfolio:** [Portfolio](https://github.com/Gmasfisch/gustavo-portfolio)  
**GitHub Profile:** [Profile](https://github.com/Gmasfisch)  
**Email:** fischbachgustavo@gmail.com
