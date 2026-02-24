cmake_minimum_required(VERSION 3.17.0)
project(homey-perception LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(realsense2 REQUIRED)
find_package(OpenCV REQUIRED)

option(BUILD_TESTING "Build tests" ON)

if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# add_executable(homey-perception
#   src/main.cpp
# )

# target_link_libraries(homey-perception PRIVATE opencv_core)

# include(CTest)
