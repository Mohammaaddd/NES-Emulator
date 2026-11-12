cmake_minimum_required(VERSION 3.20)

project(NES_Emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NES_Emulator
    src/main.cpp
    src/CPU.cpp
    src/Bus.cpp
)

target_include_directories(NES_Emulator PRIVATE include)