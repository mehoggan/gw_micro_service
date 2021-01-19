set(Srcs
  "./warscroll_collector.cpp")

add_library(warscroll_collector "${Srcs}")

target_include_directories(warscroll_collector PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include")
