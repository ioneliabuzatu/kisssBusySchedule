cmake_minimum_required(VERSION 3.14)
project(kussBusySchedule)

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include)
link_directories(  /usr/local/lib )


add_executable(main main.cpp)
