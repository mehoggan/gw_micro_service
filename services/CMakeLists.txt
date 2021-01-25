set(ServiceNames "warscroll_collector_service")

include("${CMAKE_SOURCE_DIR}/cmake/ngrest.cmake")

get_ngrest()

foreach(ServiceName IN LISTS ServiceNames)
  if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${ServiceName}")
    make_ngrest_service(
      NAME ${ServiceName}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  endif()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${ServiceName})
  add_ngrest_service_target(
    NAME ${ServiceName}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${ServiceName}")
  set(INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/../include")
  inject_deps_into_ingrest(
    NAME "${ServiceName}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    INCLUDE_DIRS "${INCLUDES}")
endforeach()

clean_ngrest(
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  VALID_SERVICES "${ServiceNames}")
