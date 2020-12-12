set(_srcs "./ServiceTimeImpl.cpp")

usFunctionGetResourceSource(TARGET ServiceTime_SystemClock OUT _srcs)
usFunctionGenerateBundleInit(TARGET ServiceTime_SystemClock OUT _srcs)

add_library(ServiceTime_SystemClock ${_srcs})

target_link_libraries(ServiceTime_SystemClock "CppMicroServices" "ServiceTime")

set(_bundle_name service_time_systemclock)

set_target_properties(ServiceTime_SystemClock PROPERTIES
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_bundle_name}
  US_BUNDLE_NAME ${_bundle_name})

if(BUILD_SHARED_LIBS)
  set_target_properties(ServiceTime_SystemClock PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1)
endif()

usFunctionEmbedResources(TARGET ServiceTime_SystemClock
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  FILES "manifest.json")


