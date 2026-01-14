cmake_minimum_required(VERSION 3.17.0)
project(homey-perception LANGUAGES CXX)


add_library()

target_include_directories()

add_executable(homey-perception
  src/main.cpp
)


target_compile_features(homey-perception PUBLIC cxx_std_20)
