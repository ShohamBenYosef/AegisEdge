cmake_minimum_required(VERSION 3.20)

project(AegisEdges
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aegisedges
    app/main.cpp
    device/device.c
    protocol/telemetry.c
)

target_include_directories(aegisedges PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/device
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol
)

target_compile_options(aegisedges PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)