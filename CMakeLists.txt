
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (NNT)

# prepare cmake for nnt.
LIST (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
LIST (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

INCLUDE (NNTDebug)

# process.
INCLUDE (CMakeDetermineSystem)
TRACE ("Generating build system for ${CMAKE_SYSTEM_NAME}.")

# on linux
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  INCLUDE (NNTLibrary)
  INCLUDE (NNTKernel)
  INCLUDE (NNTSample)
  ADD_SUBDIRECTORY (unix)
ENDIF ()

# on bsd
IF (${CMAKE_SYSTEM_NAME} MATCHES "BSD")
  SET(CMAKE_C_COMPILER clang)
  SET(CMAKE_CXX_COMPILER clang++)
  INCLUDE (NNTKernel)
  #INCLUDE (NNTSample)
  ADD_SUBDIRECTORY (unix)
ENDIF ()

# on macos.
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  INCLUDE (NNTLibrary)
  INCLUDE (NNTSample)
  IF (${CMAKE_BUILD_TOOL} MATCHES "gmake")    
    ADD_SUBDIRECTORY (unix)
  ELSE()
    ADD_SUBDIRECTORY (mac)
  ENDIF ()
ENDIF ()

# on windows.
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  ADD_SUBDIRECTORY(msvc)
ENDIF ()

# for cmake config file debug.
