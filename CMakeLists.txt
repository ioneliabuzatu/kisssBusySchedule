cmake_minimum_required(VERSION 3.10)
project(kusssBusySchedule)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt/5.15.0/lib/cmake)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

#add_executable(main main.cpp)
add_executable(kusssBusySchedule buildTimetable.cpp window.cpp window.h)

target_link_libraries(kusssBusySchedule Qt5::Core)
target_link_libraries(kusssBusySchedule Qt5::Widgets)
#target_link_libraries(kissBusySchedule Qt5::Quick)

