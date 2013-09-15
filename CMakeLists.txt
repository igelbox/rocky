cmake_minimum_required(VERSION 2.6)
project(rocky)

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_VERBOSE_MAKEFILE on)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0 gdlmm-3.0 jack)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} ${GDLMM_INCLUDE_DIRS} ${JACK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${GDLMM_LIBRARIES} ${JACK_LIBRARIES})
