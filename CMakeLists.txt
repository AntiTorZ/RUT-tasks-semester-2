cmake_minimum_required(VERSION 3.14)
project(ZeroOrderApproximation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройки для MSVC
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    add_compile_options(/W4 /permissive- /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Подключение Google Test
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Библиотека классов
add_library(approximation_lib STATIC
    src/Point.cpp
    src/PiecewiseLinearApproximation.cpp
    src/ZeroOrderSegment.cpp
)

target_include_directories(approximation_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Демонстрационный проект
add_subdirectory(Demo)

# Тесты
add_subdirectory(tests)
