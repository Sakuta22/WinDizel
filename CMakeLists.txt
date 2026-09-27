cmake_minimum_required(VERSION 3.20)

project(WinDizelProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(WinDizel STATIC
    src/Window.cpp
    src/Input/KeypadCodeToString.cpp
    src/Input/MouseCodeToString.cpp
    src/Platform/Windows/WindowsWindow.cpp
    src/Utils/Utf.cpp
)

target_include_directories(WinDizel
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(WinDizel
    PUBLIC
        UNICODE
        _UNICODE
    PRIVATE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
)

add_executable(WinDizelApp main.cpp)

target_link_libraries(WinDizelApp PRIVATE WinDizel)