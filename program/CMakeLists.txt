
# SFML finding

add_executable(bezierProgram ${PROGRAM}/bezierProgram.cpp)
TARGET_LINK_LIBRARIES(bezierProgram ${CORELIBS})

if(ROOF)
add_executable(roofGeneration ${PROGRAM}/roofGeneration.cpp)
TARGET_LINK_LIBRARIES(roofGeneration ${CORELIBS})
endif(ROOF)

add_executable(objSerializer ${PROGRAM}/objSerializer.cpp)
TARGET_LINK_LIBRARIES(objSerializer ${CORELIBS})

add_executable(brdfReader ${PROGRAM}/brdfReader.cpp)
