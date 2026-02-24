# add_library(homey-lib)

add_executable(homey-perception
  main.cpp
)

target_link_libraries(homey-perception PRIVATE opencv_core realsense2)
