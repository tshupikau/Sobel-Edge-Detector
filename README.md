# Sobel Edge Detector

A C++ desktop application for loading and displaying BMP images alongside their Sobel edge detection results.

<img width="1913" height="1016" alt="Screenshot 2026-11-14 122448" src="https://github.com/user-attachments/assets/cc790cce-48b7-4ff8-a2e2-9926464765d6" />

## Requirements

- **CMake** 3.16 or newer
- A **C++20** compiler (MSVC 2022+, GCC 11+ or Clang 14+)
- **Git** - CMake downloads GLFW and Dear ImGui automatically on the first configure
- A GPU driver with **OpenGL 3.0** or newer

## Build and run

```bash
git clone https://github.com/tshupikau/Sobel-Edge-Detector.git
cd Sobel-Edge-Detector

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Run:

```bash
# Windows
build\Release\sobel.exe
```

## Roadmap
- Saving the result
- More input formats: PNG, JPEG
- More operations: flip, rotate, blur, threshold
- Undo history for applied operations
