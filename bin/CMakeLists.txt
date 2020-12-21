set(_srcs "main.cpp")

if(NOT BUILD_SHARED_LIBS)
  usFunctionGetResourceSource(TARGET Driver OUT _srcs)
endif()

add_executable(Driver ${_srcs})

target_link_libraries(Driver DictionaryService CppMicroServices)

if(NOT BUILD_SHARED_LIBS)
  set(_static_bundles DictionaryService)
  target_link_libraries(Driver ${_static_bundles})
  usFunctionEmbedResources(TARGET Driver
    BUNDLE_NAME getting_started
    ZIP_ARCHIVES ${_static_bundles})
else()
  set(_bundle_name driver)
  set_target_properties(Driver PROPERTIES                           
    COMPILE_DEFINITIONS US_BUNDLE_NAME=${_bundle_name}                            
    US_BUNDLE_NAME ${_bundle_name})
endif()
