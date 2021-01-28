# Download and unpack boostbeast at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boostbeast-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boostbeast-download)

set(Boost_INCLUDE_DIR "${CMAKE_BINARY_DIR}/boostbeast/include"
  CACHE INTERNAL "Boost_INCLUDE_DIR")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=conversion")
