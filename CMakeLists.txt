cmake_minimum_required(VERSION 2.8.3)
project(sfm)
set(CMAKE_BUILD_TYPE Release)

#Add header files
include_directories(include)

#Add source files
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(sfm SHARED ${SOURCES})

#Install library
#install(TARGETS sfm DESTINATION /usr/lib)
#or use sudo make install
