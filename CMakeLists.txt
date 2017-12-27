cmake_minimum_required(VERSION 3.2)
project(hyper VERSION 0.1.0 LANGUAGES CXX)

# Include modules from cmake/ directory.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(SetCompilerWarningAll)

# Use C++ 14.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

enable_testing()
include_directories(include)
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(test)