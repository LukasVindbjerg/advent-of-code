cmake_minimum_required(VERSION 3.15)
project(Advent-of-Code-2025 VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Compiler warnings
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.c"
)

list(FILTER SOURCES EXCLUDE REGEX ".*main\\.c$")

# Create executable
add_executable(${PROJECT_NAME}
    src/main.c
    ${SOURCES}
)

# Set include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Link libraries (add as needed)
# Example: target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

# Optional: Create a library for easier testing
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Installation rules (optional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# TODO
# enable_testing()
# add_subdirectory(tests)
