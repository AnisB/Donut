
add_definitions( -DDONUT_TESTS)
#  SFML finding
add_executable(testStateEngine ${TEST}/testStateEngine.cpp)
TARGET_LINK_LIBRARIES(testStateEngine Donut ${CORELIBS})


add_executable(testRenderer ${TEST}/testRenderer.cpp)
TARGET_LINK_LIBRARIES(testRenderer Donut ${CORELIBS})


add_executable(testMovingSquare ${TEST}/testMovingSquare.cpp)
TARGET_LINK_LIBRARIES(testMovingSquare Donut ${CORELIBS})

 


