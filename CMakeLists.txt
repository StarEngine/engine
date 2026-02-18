cmake_minimum_required(VERSION 3.14)
project(StarEngine
    VERSION 0.1.1
    LANGUAGES CXX
    DESCRIPTION "A 2D game engine"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(STAR2D "Enable 2D mode" ON)
option(STARENGINE_BUILD_EXAMPLES "Build example projects" ON)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the engine library
add_subdirectory(src)

# Example / test programs
if(STARENGINE_BUILD_EXAMPLES)
    add_subdirectory(test/pong)
endif()