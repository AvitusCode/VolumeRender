cmake_minimum_required(VERSION 3.5)

project(VolumeRender)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(math)
include_directories(support)
include_directories(render)
include_directories(../libraries/includes)
include_directories(../libraries/libs)

set(SOURCES
     glad.c
     Main.cpp
     vec3.cpp
     vec4.cpp
     tests_generate_functions.cpp
     Shader.cpp
     WinRender.cpp
)

set(HEADERS
     vec3.h
     vec4.h
     Profiler.h
     tests_generate_functions.h
     Shader.h
     WinRender.h
     Mat2D.h
     Mat3D.h
     Voxel.h
)

add_executable(VolumeRender ${SOURCES} ${HEADERS})

target_link_libraries(VolumeRender PRIVATE glfw3)
target_link_libraries(VolumeRender PRIVATE gdi32)
target_link_libraries(VolumeRender PRIVATE opengl32)

install(TARGETS VolumeRender DESTINATION program)