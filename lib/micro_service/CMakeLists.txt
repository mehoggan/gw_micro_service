set(GwMicroServiceMicroServiceSrc
  "./basic_controller.cpp"
  "./interrupt_handler.cpp"
  "./micro_service_controller.cpp"
  "./network_utils.cpp"
  "./runtime_utils.cpp")

add_library(MicroService "${GwMicroServiceMicroServiceSrc}")

target_link_libraries(MicroService cpprest common_utilities)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  set(BuildType "Debug")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(BuildType "Release")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  set(BuildType "Release")
else()
  message(FATAL_ERROR "Build type of ${CMAKE_BUILD_TYPE} is not supported.")
endif()

message(STATUS "Build type = ${BuildType}.")

target_include_directories(MicroService PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  "${CMAKE_BINARY_DIR}/cpprestsdk-src/${BuildType}/include")
