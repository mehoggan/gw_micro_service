function(wget_ngrest os)
  message(STATUS "Downloading ngrest for ${os}...")
  execute_process(
    COMMAND bash "${CMAKE_SOURCE_DIR}/scripts/download_ngrest.sh"
    RESULT_VARIABLE NGREST_RESULT_VAR
    OUTPUT_VARIABLE NGREST_OUTPUT_VAR
    ERROR_VARIABLE NGREST_ERROR_VAR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
  if (NOT NGREST_RESULT_VAR EQUAL "0")
    message(FATAL_ERROR "Failed to download ngrest "
      "using ngrest with the following results:\n"
      "     RESULT_VAR=${NGREST_RESULT_VAR}\n"
      "     OUTPUT_VAR=${NGREST_OUTPUT_VAR}\n"
      "     ERROR_VAR=${NGREST_ERROR_VAR}")
  else()
    message(STATUS "Downloaded ngrest and installed it with:\n\tresult="
      "${NGREST_RESULT_VAR}\n\toutput=${NGREST_OUTPUT_VAR}")
  endif()
endfunction()

function(get_ngrest)
  if(UNIX AND NOT APPLE)
    if(NOT EXISTS "/usr/local/bin/ngrest")
      message(STATUS "installing ngrest...")
      wget_ngrest("Linux")
    else()
      message(STATUS "ngrest is already installed.")
    endif()
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(NOT EXISTS "/usr/local/bin/ngrest")
      message(STATUS "installing ngrest...")
      wget_ngrest("Mac OSx")
    else()
      message(STATUS "ngrest is already installed.")
    endif()
  else()
    message(FATAL_ERROR "Unsupported OS!")
  endif()
endfunction()

function(make_ngrest_service)
  set(options)
  set(oneValueArgs NAME WORKING_DIRECTORY)
  set(multiValueArgs)
  cmake_parse_arguments(NGREST_SERVICE "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})
  if(NOT NGREST_SERVICE_NAME)
    message(FATAL_ERROR "You must define NAME.")
  endif()
  if(NOT NGREST_SERVICE_WORKING_DIRECTORY)
    message(FATAL_ERROR "You must define WORKING_DIRECTORY.")
  endif()
  execute_process(
    COMMAND "ngrest" "create" "${NGREST_SERVICE_NAME}"
    WORKING_DIRECTORY "${NGREST_SERVICE_WORKING_DIRECTORY}"
    RESULT_VARIABLE NGREST_RESULT_VAR
    OUTPUT_VARIABLE NGREST_OUTPUT_VAR
    ERROR_VARIABLE NGREST_ERROR_VAR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
  if (NOT NGREST_RESULT_VAR EQUAL "0")
    message(FATAL_ERROR "Failed to generate service ${NGREST_SERVICE_NAME} "
      "using ngrest with the following results:\n"
      "     RESULT_VAR=${NGREST_RESULT_VAR}\n"
      "     OUTPUT_VAR=${NGREST_OUTPUT_VAR}\n"
      "     ERROR_VAR=${NGREST_ERROR_VAR}")
  endif()
endfunction()

function(inject_deps_into_ingrest)
  set(options)
  set(oneValueArgs NAME WORKING_DIRECTORY INCLUDE_DIRS)
  set(multiValueArgs)
  cmake_parse_arguments(NGREST_SERVICE "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})
  set(WorkingDirectory "${NGREST_SERVICE_WORKING_DIRECTORY}")
  set(ServiceName "${NGREST_SERVICE_NAME}")
  set(BuildFile "${WorkingDirectory}/${ServiceName}/CMakeLists.txt")
  if(NOT EXISTS "${BuildFile}")
    message(FATAL_ERROR "${BuildFile} does not exist!!!")
  endif()
  file(READ "${BuildFile}" TmpTxt)
  string(FIND "${TmpTxt}" "########INJECTED########" Matches)
  if(${Matches} EQUAL -1)
    string(REGEX REPLACE "_service$" "" ServiceLib "${ServiceName}")
    message(STATUS "Adding library dependency on ${ServiceName} of "
      "${ServiceLib}...")
    file(APPEND "${BuildFile}" "\n\n########INJECTED########\n")
    file(APPEND "${BuildFile}" "target_link_libraries(${ServiceName} "
      "${ServiceLib})\n")
    set(ServiceIncludes "${NGREST_SERVICE_INCLUDE_DIRS}")
    file(APPEND "${BuildFile}" "target_include_directories(${ServiceName} "
      "PUBLIC ${ServiceIncludes})\n")
  endif()
endfunction()

function(clean_ngrest)
  set(options)
  set(oneValueArgs WORKING_DIRECTORY)
  set(multiValueArgs VALID_SERVICES)
  cmake_parse_arguments(NGREST_SERVICE "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})
  file(GLOB CurrentServices "${NGREST_SERVICE_WORKING_DIRECTORY}" "*")
  list(REMOVE_ITEM CurrentServices "${NGREST_SERVICE_WORKING_DIRECTORY}")
  foreach(File IN LISTS CurrentServices)
    if(IS_DIRECTORY "${File}")
      get_filename_component(Basename "${File}" NAME)
      list(FIND NGREST_SERVICE_VALID_SERVICES "${Basename}" Found)
      if (Found EQUAL -1)
        message(STATUS "Removing ${File}...")
        file(REMOVE_RECURSE "${File}")
      endif()
    endif()
  endforeach()
endfunction()

macro(add_ngrest_service_target)
  set(options)
  set(oneValueArgs NAME WORKING_DIRECTORY)
  set(multiValueArgs)
  cmake_parse_arguments(NGREST_SERVICE "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})
  if(NOT NGREST_SERVICE_NAME)
    message(FATAL_ERROR "You must define NAME.")
  endif()
  if(NOT NGREST_SERVICE_WORKING_DIRECTORY)
    message(FATAL_ERROR "You must define WORKING_DIRECTORY.")
  endif()
  add_custom_target(${NGREST_SERVICE_NAME}_start
    "ngrest"
    WORKING_DIRECTORY "${NGREST_SERVICE_WORKING_DIRECTORY}"
    COMMENT "Starts the service named after \"NAME\" variable.")
endmacro()
