cmake_minimum_required(VERSION 3.10)
project(CppRayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Automatically find all .cpp and .h files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# 2. Create the executable using that list
add_executable(raytracer ${SOURCES})

# This makes sure the compiler finds headers in the src folder
target_include_directories(raytracer PUBLIC src)