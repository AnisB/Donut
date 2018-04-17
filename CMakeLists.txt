cmake_minimum_required(VERSION 3.0.2)
project(donut)

# Declare the global variable folders
set(BENTO_SDK_ROOT "${PROJECT_SOURCE_DIR}/bento")
set(DONUT_ENGINE_ROOT "${PROJECT_SOURCE_DIR}/engine/")
set(DONUT_TEST_ROOT "${PROJECT_SOURCE_DIR}/test/")
set(DONUT_PROGRAM_ROOT "${PROJECT_SOURCE_DIR}/program/")
set(THIRD_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/3rd/win32/include")
set(THIRD_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/3rd/win32/lib")

# Override the cmake module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")

# Enable filters for cmake
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Define the cmake macros
include(CMakePlatforms)
include(CMakeMacros)
include(CMakeBuildSettings)

# Define the build options
define_plaform_settings()

# Print the platform's name
message(STATUS "The build identifier is: ${NYX_PLATFORM_NAME}")

# Create the list of allowed files to be included
set(bento_source_extensions)
list(APPEND bento_source_extensions ".h" ".cpp" ".inl" ".txt")

# Compile the bento SDK
add_subdirectory(${BENTO_SDK_ROOT}/src)

# Find opengl
FIND_LIBRARY(OpenGL_LIBRARY OpenGL )

# Find vulkan if available
try_find_vulkan()

# Set the include directories
set(COMBINED_INCLUDE_DIRS "${THIRD_INCLUDE_DIRS}" "${OPENGL_INCLUDE_DIRS}")
set(COMBINED_INCLUDE_DIRS "${COMBINED_INCLUDE_DIRS}" "${GRAPHIC_INCLUDE_DIR}")
SET(THIRD_PARTY_LIBRARIES "${GRAPHIC_LIBS}" "${THIRD_LIBRARY_DIRS}/lib-vc2015/glfw3.lib" "${THIRD_LIBRARY_DIRS}/glew32.lib" "${THIRD_LIBRARY_DIRS}/glew32s.lib" "opengl32.lib")
SET(THIRD_PARTY_BINARIES "${THIRD_LIBRARY_DIRS}/glew32.dll")

# Compile the engine
add_subdirectory(${DONUT_ENGINE_ROOT}/src)

# Adding the tests if we should
add_subdirectory(${DONUT_TEST_ROOT})

# Adding the programs if we should
add_subdirectory(${DONUT_PROGRAM_ROOT})