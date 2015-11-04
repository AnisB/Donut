cmake_minimum_required(VERSION 2.6)

MACRO(GENERATE_LIB LIB_PATH LIB_NAME)
  SET(${Source_File} "")
file(
  GLOB_RECURSE 
  Source_File 
  ${LIB_PATH}/*.h
  ${LIB_PATH}/*.ih
  ${LIB_PATH}/*.cpp
    )
add_library(${LIB_NAME} ${Source_File})
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${EXTERNAL_INCLUDES} )
ENDMACRO()