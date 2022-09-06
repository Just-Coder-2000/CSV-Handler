cmake_minimum_required(VERSION 3.10)

project(csvHandler_v2 VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_INSTALL_PREFIX /usr/local/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/test)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/include/ DESTINATION artwork/csv)
