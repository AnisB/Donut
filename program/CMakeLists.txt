
# SFML finding

add_executable(realisticRendering ${PROGRAM}/realisticRendering)
TARGET_LINK_LIBRARIES(realisticRendering Donut ${CORELIBS})

add_executable(bezierProgram ${PROGRAM}/bezierProgram.cpp)
TARGET_LINK_LIBRARIES(bezierProgram Donut ${CORELIBS})
