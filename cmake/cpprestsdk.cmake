execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cpprestsdk-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cpprestsdk-download)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_BINARY_DIR}/cpprestsdk-src
  ${CMAKE_BINARY_DIR}/cpprestsdk-build)

include_directories("${gtest_SOURCE_DIR}/include"
  "${gmock_SOURCE_DIR}/include")


