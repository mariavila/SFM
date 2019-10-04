cmake_minimum_required(VERSION 2.8.3)
project (sfm_test)

#Link shared library:
set ( PROJECT_LINK_LIBS sfm.so )
link_directories( ../build )
include_directories(../include)

#Add executable
add_executable(sfm_test sfm_test.cpp)
target_link_libraries(sfm_test ${PROJECT_LINK_LIBS} )
