cmake_minimum_required(VERSION 2.9)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 11)

project(6Forest)

set(EXECUTABLE_OUTPUT_PATH ..)

aux_source_directory(src DIR_SRCS)

add_executable(main ${DIR_SRCS})