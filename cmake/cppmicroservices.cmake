execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppmicroservices-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppmicroservices-download)

add_subdirectory(${CMAKE_BINARY_DIR}/cppmicroservices-src
  ${CMAKE_BINARY_DIR}/cppmicroservices-build)
