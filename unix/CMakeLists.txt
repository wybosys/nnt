
TRACE ("Generating build system for Unix.")

ADD_SUBDIRECTORY ("../Classes" "Classes")

IF (${NNT_BUILD_SAMPLE})
  ADD_SUBDIRECTORY (sample)
ENDIF (${NNT_BUILD_SAMPLE})
