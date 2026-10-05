cmake_minimum_required(VERSION 3.25)
include(FetchContent)

set(FETCHCONTENT_FULLY_DISCONNECTED ON)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/dependencies)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

project(tp_1 LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -fsanitize=address,undefined")
endif()

#----------------------------------------
# Mandatory: Add any new source files here
set(sources_ex1
  ex1_complexe/src/complexe.cpp
  ex1_complexe/src/algebrique.cpp
  ex1_complexe/src/polaire.cpp
  ex1_complexe/src/ensemble.cpp
)

# Optional: Add any new header files here
set(headers_ex1
  ex1_complexe/src/complexe.hpp
  ex1_complexe/src/algebrique.hpp
  ex1_complexe/src/polaire.hpp
  ex1_complexe/src/ensemble.hpp
)
#----------------------------------------

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_library(tp_1 OBJECT)
target_sources(tp_1 PRIVATE ${sources_ex1} PUBLIC ${headers_ex1})
target_include_directories(tp_1 PUBLIC ex1_complexe/src)

add_executable(ex1_complexe)
target_link_libraries(ex1_complexe PRIVATE Catch2::Catch2WithMain tp_1)
target_sources(ex1_complexe PRIVATE ex1_complexe/test/tp1_complexe_test.cpp)

add_executable(ex2_mandelbrot ex2_mandelbrot/src/main.cpp)
target_link_libraries(ex2_mandelbrot PRIVATE tp_1)
target_include_directories(ex2_mandelbrot PRIVATE dependencies/CImg)

add_executable(sandbox)
target_link_libraries(sandbox PRIVATE tp_1)
target_sources(sandbox PRIVATE sandbox/main.cpp)
target_include_directories(sandbox PRIVATE sandbox/src)
