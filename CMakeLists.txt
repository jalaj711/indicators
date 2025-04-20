cmake_minimum_required(VERSION 3.12)
project(indicators C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Winline")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Output directory for all binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Automatically collect sources and headers
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

# Create static library
add_library(indicators STATIC ${SOURCES} ${HEADERS})
target_include_directories(indicators PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(indicators PRIVATE m)

# Benchmark executable
add_executable(benchmark benchmark.c)
target_link_libraries(benchmark PRIVATE indicators)
target_include_directories(benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
