add_library(ServiceTime
  "./ServiceTime.h"
  "./ServiceTime.cpp")

target_include_directories(ServiceTime PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

generate_export_header(ServiceTime)

if(BUILD_SHARED_LIBS)
  set_target_properties(ServiceTime PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1)
endif()


