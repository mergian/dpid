# Rapid, Detail-Preserving Image Downscaling

This is the code for the paper "Rapid, Detail-Preserving Image Downscaling" (https://dl.acm.org/citation.cfm?id=2980239) by Nicolas Weber, Michael Waechter, Sandra C. Amend, Stefan Guthe and Michael Goesele, presented at SIGGRAPH Asia 2016.

## CUDA Version:
The CUDA version requires:
* CMake 2.8
* CUDA 6.0
* OpenCV 3.x
* a GPU with at least compute capability 3.0 (Kepler)

If you have a GPU newer than 3.0, 3.5 or 5.2, please add your compute capability to the `CUDA_NVCC_FLAGS` in the `CMkeLists.txt`.

## Matlab Version:
The Matlab version does not have any external dependencies and should work out of the box.