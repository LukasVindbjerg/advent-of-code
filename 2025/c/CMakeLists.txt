cmake_minimum_required(VERSION 3.15)

# Project
project(AdventOfCode2025 VERSION 1.0.0 LANGUAGES C)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Generate compile_commands.json (for clangd / Neovim)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type for single-config generators (Make, Ninja)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" "")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# Compiler warnings
if(MSVC)
  set(WARN_FLAGS /W4)
else()
  set(WARN_FLAGS -Wall -Wextra -Wpedantic)
endif()

# Sources: all .c files under src/, except main.c (linked only into the exe)
file(GLOB_RECURSE AOC_SOURCES CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/*.c"
)
list(FILTER AOC_SOURCES EXCLUDE REGEX ".*/main\\.c$")

# Library with all AoC solution code (good for tests later)
add_library(aoc2025_lib STATIC ${AOC_SOURCES})
target_include_directories(aoc2025_lib
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_options(aoc2025_lib PRIVATE ${WARN_FLAGS})

# Executable that contains main() and links the library
add_executable(aoc2025
  ${PROJECT_SOURCE_DIR}/src/main.c
)
target_link_libraries(aoc2025 PRIVATE aoc2025_lib)
target_compile_options(aoc2025 PRIVATE ${WARN_FLAGS})

# Optional install rule
install(TARGETS aoc2025
  RUNTIME DESTINATION bin
)

# Optional testing (future):
# enable_testing()
# add_subdirectory(tests)

