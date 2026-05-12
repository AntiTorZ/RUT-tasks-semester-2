cmake_minimum_required(VERSION 3.10)
project(PiecewiseApproximation)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files for the main library/executable
set(SOURCES
    src/ClassPoint.cpp
    src/ClassPiecewiseLinear.cpp
    src/ClassZeroOrderExtrapolator.cpp
    src/Main.cpp
)

add_executable(App ${SOURCES})

# --- Google Test Setup ---
# Скачиваем и компилируем GoogleTest (если не установлен в системе)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Source files for tests
set(TEST_SOURCES
    src/ClassPoint.cpp
    src/ClassPiecewiseLinear.cpp
    src/ClassZeroOrderExtrapolator.cpp
    tests/tests.cpp
)

add_executable(RunTests ${TEST_SOURCES})
target_link_libraries(RunTests gtest_main)

include(GoogleTest)
gtest_discover_tests(RunTests)
