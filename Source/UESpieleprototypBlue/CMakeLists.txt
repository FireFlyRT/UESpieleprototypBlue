cmake_minimum_required(VERSION 3.27)
project(parsers)
find_package(Python3)

set(SOURCE_FILES PythonInterface.cpp)
add_library(parsers SHARED ${SOURCE_FILES})
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(parsers ${PYTHON_LIBRARIES})
