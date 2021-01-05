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
