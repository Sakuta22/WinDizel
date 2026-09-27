cmake_minimum_required(VERSION 3.20)

project(WindowSystemProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(WindowSystem STATIC
    src/Window.cpp
    src/Input/KeypadCodeToString.cpp
    src/Input/MouseCodeToString.cpp
    src/Platform/Windows/WindowsWindow.cpp
    src/Utils/Utf.cpp
)

target_include_directories(WindowSystem
    PUBLIC
        include
    PRIVATE
        src
)

target_compile_definitions(WindowSystem
    PUBLIC
        UNICODE
        _UNICODE
    PRIVATE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
)

add_executable(WindowSystemApp main.cpp)

target_link_libraries(WindowSystemApp PRIVATE WindowSystem)