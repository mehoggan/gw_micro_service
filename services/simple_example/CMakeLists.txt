set(HelloWorldSource "./main.cpp")

add_executable(hello_world "${HelloWorldSource}")

target_link_libraries(hello_world MicroService cpprest common_utilities)

target_include_directories(hello_world PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  "${CMAKE_BINARY_DIR}/cpprestsdk-src/${CMAKE_BUILD_TYPE}/include")
