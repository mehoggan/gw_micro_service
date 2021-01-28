cmake_minimum_required(VERSION 3.0.2)
project(gw_micro_service)

option(BUILD_SHARED_LIBS "Build shared libraries over static library." ON)
option(DAGTASKS_TESTS "Build unit tests." ON)
option(DAGTASKS_BINDINGS "Build all bindings for the native library." ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.boostbeast.txt.in
  ${CMAKE_BINARY_DIR}/boostbeast-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/boostbeast.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.cpprestsdk.txt.in
  ${CMAKE_BINARY_DIR}/cpprestsdk-download/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpprestsdk.cmake)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_MACOSX_RPATH 1)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/c++11.cmake)

add_subdirectory("./include")
add_subdirectory("./lib")
add_subdirectory("./services")
