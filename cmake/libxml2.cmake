execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/libxml2-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/libxml2-download)

add_subdirectory(${CMAKE_BINARY_DIR}/libxml2-src
  ${CMAKE_BINARY_DIR}/libxml2-build)

