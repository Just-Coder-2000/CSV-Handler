cmake_minimum_required(VERSION 3.10)

project(csvHandler VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ./main.cpp)
