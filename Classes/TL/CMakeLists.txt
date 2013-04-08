
SOURCE (Algorithm+NNT.cpp)
SOURCE (String+NNT.cpp)
SOURCE (Regex+NNT.cpp)
SOURCE (Variant+NNT.cpp)

SOURCESUB ("hardware/Assembly+NNT.cpp")
SOURCESUB ("hardware/Cpu+NNT.cpp")
SOURCESUB ("hardware/Device+NNT.cpp")
SOURCESUB ("hardware/Hardware+NNT.cpp")

ADD_LIBRARY (NntTl STATIC ${CURRENT_SOURCES})
