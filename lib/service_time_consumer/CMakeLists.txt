set(_srcs "./ServiceTimeConsumer.cpp")

usFunctionGetResourceSource(TARGET ServiceTime_Consumer OUT _srcs)
usFunctionGenerateBundleInit(TARGET ServiceTime_Consumer OUT _srcs)

add_library(ServiceTime_Consumer ${_srcs})

target_link_libraries(ServiceTime_Consumer "CppMicroServices" "ServiceTime")

set(_bundle_name service_time_consumer)

set_target_properties(ServiceTime_Consumer PROPERTIES
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_bundle_name}
  US_BUNDLE_NAME ${_bundle_name})

if(BUILD_SHARED_LIBS)
  set_target_properties(ServiceTime_Consumer PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1)
endif()

usFunctionEmbedResources(TARGET ServiceTime_Consumer
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  FILES "manifest.json")
