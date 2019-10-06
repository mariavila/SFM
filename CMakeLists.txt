cmake_minimum_required(VERSION 2.8.3)
set (CMAKE_CXX_STANDARD 11)
project(sfm)
set(CMAKE_BUILD_TYPE Release)

find_package(OpenCV REQUIRED)

#Add header files
include_directories(include)

#Add source files
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(sfm SHARED ${SOURCES})
target_link_libraries( sfm ${OpenCV_LIBS})
