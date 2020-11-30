cmake_minimum_required(VERSION 3.0.2)
project(gw_micro_service)

option(BUILD_SHARED_LIBS "Build shared libraries over static library." ON)
option(DAGTASKS_TESTS "Build unit tests." ON)
option(DAGTASKS_BINDINGS "Build all bindings for the native library." ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_MACOSX_RPATH 1)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/c++11.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/externals.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.cppmicroservices.txt.in
    ${CMAKE_BINARY_DIR}/cppmicroservices-download/CMakeLists.txt)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cppmicroservices.cmake)

include(GenerateExportHeader)

add_subdirectory(lib)


# [exec-begin]
#=========================================================
# The executable managing the CppMicroServices framework
#---------------------------------------------------------

set(_srcs "main.cpp")

if(NOT BUILD_SHARED_LIBS)
  # Set up dependencies to resources from static bundles
  usFunctionGetResourceSource(TARGET GettingStarted OUT _srcs)
endif()

add_executable(GettingStarted ${_srcs})

target_link_libraries(GettingStarted CppMicroServices)

if(NOT BUILD_SHARED_LIBS)
  set(_static_bundles ServiceTime_SystemClock ServiceTime_Consumer)
  target_link_libraries(GettingStarted ${_static_bundles})
  usFunctionEmbedResources(TARGET GettingStarted
    # The executable is not a bundle itself but we still
    # need a bundle name for it here.
    BUNDLE_NAME getting_started
    # Merge in all resources from static bundles
    ZIP_ARCHIVES ${_static_bundles}
    )
endif()
# [exec-end]
