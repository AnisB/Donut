cmake_minimum_required(VERSION 2.6)

MACRO(GENERATE_LIB LIB_PATH LIB_NAME FOLDER_NAME)
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
set_target_properties(${LIB_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
ENDMACRO()

MACRO(GENERATE_TEST SRC_FILE)
add_executable(${SRC_FILE} ${TEST}/${SRC_FILE})
TARGET_LINK_LIBRARIES(${SRC_FILE} ${CORELIBS})
set_target_properties(${SRC_FILE} PROPERTIES FOLDER "Tests")
ENDMACRO()

MACRO(GENERATE_PROGRAM SRC_FILE)
add_executable(${SRC_FILE} ${PROGRAM}/${SRC_FILE})
TARGET_LINK_LIBRARIES(${SRC_FILE} ${CORELIBS})
set_target_properties(${SRC_FILE} PROPERTIES FOLDER "Program")
ENDMACRO()