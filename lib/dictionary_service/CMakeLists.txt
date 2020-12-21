# Activator
set(_srcs
  "./Activator.cpp"
  "./DictionaryService.cpp"
  "./IDictionaryService.cpp")

usFunctionGetResourceSource(TARGET DictionaryService OUT _srcs)              
usFunctionGenerateBundleInit(TARGET DictionaryService OUT _srcs)

add_library(DictionaryService ${_srcs})

target_link_libraries(DictionaryService "CppMicroServices")

set(_bundle_name dictionary_service)

set_target_properties(DictionaryService PROPERTIES                           
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_bundle_name}                            
  US_BUNDLE_NAME ${_bundle_name})

if(BUILD_SHARED_LIBS)
  set_target_properties(DictionaryService PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1)
endif()

usFunctionEmbedResources(TARGET DictionaryService
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  FILES "manifest.json")

# Interface
generate_export_header(DictionaryService)

target_include_directories(DictionaryService PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
