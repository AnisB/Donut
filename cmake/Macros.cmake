cmake_minimum_required(VERSION 2.6)

MACRO(GENERATE_LIB LIB_PATH LIB_NAME FOLDER_NAME)
  SET(${Source_File} "")
file(
  GLOB_RECURSE 
  Source_File 
  ${LIB_PATH}/*.h
  ${LIB_PATH}/*.ih
  ${LIB_PATH}/*.inl
  ${LIB_PATH}/*.cpp
    )
add_library(${LIB_NAME} ${Source_File})
include_directories(${SOURCES} ${GRAPHIC_INCLUDE_DIR} ${EXTERNAL_INCLUDES} )
set_target_properties(${LIB_NAME} 
	PROPERTIES FOLDER ${FOLDER_NAME}
	COMPILE_PDB_NAME ${LIB_NAME}
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
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

MACRO(HANDLE_VULKAN)
find_package(Vulkan)
if(Vulkan_FOUND)
  message(STATUS "Vulkan found")
  set(GRAPHIC_INCLUDE_DIR "${GRAPHIC_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS}")
  SET(GRAPHIC_LIBS "${GRAPHIC_LIBS}" "${Vulkan_LIBRARY}")
  add_definitions( -DVULKAN_SUPPORTED )
endif(Vulkan_FOUND)
ENDMACRO()