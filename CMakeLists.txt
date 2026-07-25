cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(ANGEL12)

set(SOURCES
    src/main.cpp
    src/Reel.cpp
    src/ReelManager.cpp
    src/StateManager.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/InputManager.cpp
    src/AudioManager.cpp
    src/EffectManager.cpp
)

add_executable(Angel12
    ${SOURCES}
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)

# This assumes the SDLs source is available in vendored/
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# set PROJECT_ROOT
target_compile_definitions(Angel12 PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Link dependencies
target_link_options(Angel12 PRIVATE
    -static-libstdc++
    -static-libgcc
)
target_link_libraries(Angel12 PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf)
target_include_directories(Angel12 PRIVATE ${CMAKE_SOURCE_DIR}/include)
