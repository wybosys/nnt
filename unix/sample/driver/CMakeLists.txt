
NNT_USE_HEADERS ()

SOURCE (common.cpp)
SOURCE (SampleDevice.cpp)

ADD_LIBRARY (NntSampleDriver SHARED ${CURRENT_SOURCES})
TARGET_LINK_LIBRARIES (NntSampleDriver NntKernel)
