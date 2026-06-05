cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(FIEAPeggleClone)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 CONFIG REQUIRED)

find_package(SDL2_mixer CONFIG REQUIRED)

find_package(SDL2_ttf CONFIG REQUIRED)


add_executable(FIEAPeggleClone
    src/main.cpp

    src/Engine/Window.cpp
    src/Engine/Renderer.cpp
    src/Engine/Time.cpp
    src/Engine/AudioManager.cpp
    src/Engine/AudioManager.h

    src/Game/Ball.cpp
    src/Game/Peg.cpp
    src/Game/Bucket.cpp
    src/Game/Bucket.h
    src/Game/HUD.cpp
    src/Game/HUD.h
)

target_include_directories(FIEAPeggleClone PRIVATE src)

target_link_libraries(FIEAPeggleClone PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)