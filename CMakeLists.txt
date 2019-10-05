cmake_minimum_required(VERSION 2.8.3)
set (CMAKE_CXX_STANDARD 11)
project(sfm)
set(CMAKE_BUILD_TYPE Release)

#TODO
#Include packages
#find_package (Eigen3 3.2 REQUIRED NO_MODULE)

#Add header files
include_directories(include)

#Add source files
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(sfm SHARED ${SOURCES})
#TODO
#target_link_libraries(sfm Eigen3::Eigen)

#Install library
#install(TARGETS sfm DESTINATION /usr/lib)
#or use sudo make install
