cmake_minimum_required(VERSION 3.10)

project(sdlEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Locate SDL2
find_package(SDL2 2.0.0 REQUIRED)
find_package(PNG 1.6.37 REQUIRED)
find_package(Boost 1.33.0 REQUIRED)

include_directories(include)

add_subdirectory(src)
