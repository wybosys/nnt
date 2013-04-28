
NNT_USE_LIBHEADERS ()

IF (${NNT_BUILD_KERNEL})

  SOURCE (DriverApp.cpp)
  SOURCE (DriverObject.cpp)
  SOURCE (DriverFeature.cpp)

  ADD_DEFINITIONS (-DLIBNNT -DKERNELNNT)
  ADD_LIBRARY (NntKernel STATIC ${CURRENT_SOURCES})

ENDIF ()

IF (${NNT_BUILD_LIBRARY})

  SOURCE (DriverApp.cpp)
  SOURCE (DriverObject.cpp)
  SOURCE (DriverFeature.cpp)

  ADD_LIBRARY (NntKernel STATIC ${CURRENT_SOURCES})

ENDIF ()
