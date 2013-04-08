
SET (NNT_BUILD_LIBRARY 1 CACHE BOOL "build the library")

MACRO (source file)
  LIST (APPEND CURRENT_SOURCES ${file})
ENDMACRO (source)

MACRO (sourcesub file)
  LIST (APPEND CURRENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${file})
ENDMACRO (sourcesub)

INCLUDE (CMakeDetermineSystem)

IF (${NNT_BUILD_LIBRARY})

  # set include directory.
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/Classes")
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/Classes/Core")

  IF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/3rd/Unix")
  ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

  IF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")    
    INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/3rd/Mac")
  ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/3rd/")

  # set default output directory.
  SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/stage")
  SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/stage")
  SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/stage")

ENDIF (${NNT_BUILD_LIBRARY})

MACRO (NNT_USE_HEADERS)
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}")
ENDMACRO (NNT_USE_HEADERS)

SET (NNT_ARCH 32)
IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET (NNT_ARCH 64)
ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)