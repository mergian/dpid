# Copyright (c) 2016 Nicolas Weber and Sandra C. Amend / GCC / TU-Darmstadt. All rights reserved. 
# Use of this source code is governed by the BSD 3-Clause license that can be
# found in the LICENSE file.
cmake_minimum_required(VERSION 2.8)

project(dpid)

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

set(CUDA_NVCC_FLAGS "-DNDEBUG -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_52,code=sm_52 --use_fast_math --no-device-link")

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

cuda_add_executable(dpid main.cpp main.cu)
target_link_libraries(dpid ${OpenCV_LIBS})
