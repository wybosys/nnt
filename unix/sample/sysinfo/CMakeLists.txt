
NNT_USE_HEADERS ()

SOURCE (sysinfo.cpp)

ADD_EXECUTABLE (sysinfo ${CURRENT_SOURCES})
TARGET_LINK_LIBRARIES (sysinfo NntCore NntParser NntTl NntMach pthread)
