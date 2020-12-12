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
