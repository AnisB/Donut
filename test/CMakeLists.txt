
add_definitions( -DDONUT_TESTS)
# SFML finding
add_executable(testStateEngine ${TEST}/testStateEngine.cpp)
TARGET_LINK_LIBRARIES(testStateEngine ${CORELIBS})

add_executable(testRenderer ${TEST}/testRenderer.cpp)
TARGET_LINK_LIBRARIES(testRenderer ${CORELIBS})

add_executable(testRayTracer ${TEST}/testRayTracer.cpp)
TARGET_LINK_LIBRARIES(testRayTracer ${CORELIBS})

add_executable(testFlourLoad ${TEST}/testFlourLoad.cpp)
TARGET_LINK_LIBRARIES(testFlourLoad ${CORELIBS})

add_executable(testBRDFLoad ${TEST}/testBRDFLoad.cpp)
TARGET_LINK_LIBRARIES(testBRDFLoad ${CORELIBS})