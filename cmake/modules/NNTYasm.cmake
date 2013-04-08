
MACRO (sourceyasm file)
  ADD_CUSTOM_COMMAND (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${file}.o"
    COMMAND yasm -w -fmacho64 -dmacho64 -rnasm -pgas -o${CMAKE_CURRENT_BINARY_DIR}/${file}.o ${CMAKE_CURRENT_SOURCE_DIR}/${file}
    )
  SOURCE (${CMAKE_CURRENT_BINARY_DIR}/${file}.o)
ENDMACRO (sourceyasm)