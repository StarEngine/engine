cmake_minimum_required(VERSION 3.14)
project(pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the same packages the engine uses
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

add_executable(pong main.cpp)

# Link against the starengine static library and all its transitive deps
target_link_libraries(pong PRIVATE
    starengine
    OpenGL::GL
    GLEW::GLEW
    PkgConfig::SDL2
    PkgConfig::SDL2_MIXER
    Freetype::Freetype
    PNG::PNG
)

# Engine headers live under src/
target_include_directories(pong PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
