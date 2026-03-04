# How to run

## Prerequisites
* **Compiler:** GCC/G++ installed.

### Navigate to the source directory and compile using `g++`:
```
cd src
```
### Compilation
```
g++ -o app main.cpp image.cpp EdgeDetector.cpp
```

### Usage
```
app <input_image>.bmp <output_image>.bmp
```

### Example
```
./app photo.bmp edges_output.bmp
```
