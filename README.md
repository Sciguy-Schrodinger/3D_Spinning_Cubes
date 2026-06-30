# 🧊 3D Cubes

An interactive 3D visualization built with **OpenGL**, **GLFW**, **GLEW**, and **GLM**.  
Press **Space** to spawn colorful cubes that move, rotate, and scale according to random mathematical functions.

---

## 🎮 Features

- **Real-time 3D rendering** with OpenGL
- **Dynamic cube generation** — press Space to add cubes
- **Random motion** — each cube follows a unique mathematical function (sine, cosine, tangent, exponential, quadratic)
- **Colorful** — each cube has a distinct random color
- **FPS counter** — displayed in the window title
- **Smooth rotation** — cubes spin over time

---

## 🛠️ Technologies Used

- **C++** — core logic
- **OpenGL** — graphics rendering
- **GLFW** — window and input handling
- **GLEW** — OpenGL extension loading
- **GLM** — mathematics for transformations

---

## 🚀 How to Build

### Requirements

Install the dependencies (Ubuntu/Debian):

bash
sudo apt update
sudo apt install libglfw3-dev libglew-dev libglm-dev

### Compile

g++ -o cubes cubes.cpp \
    -lGL -lGLEW -lglfw \
    -lstdc++ -lm -lX11 -lXrandr -lXi

### Run

./cubes

### Controls

press space to spawn in a new cube and press enter to exit the program...
