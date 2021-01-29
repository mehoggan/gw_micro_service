# Download and unpack boostbeast at configure time
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boostbeast-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boostbeast-download)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # We have to do this because boost does not build and FindBoost behaves
  # differently on OSX.
  set(Boost_INCLUDE_DIR
    "${CMAKE_BINARY_DIR}/boostbeast-download/boostbeast-prefix/src/boost"
    CACHE INTERNAL "Boost_INCLUDE_DIR")
else()
  set(Boost_INCLUDE_DIR "${CMAKE_BINARY_DIR}/boostbeast/include"
    CACHE INTERNAL "Boost_INCLUDE_DIR")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=conversion")
