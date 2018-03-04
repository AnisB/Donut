add_definitions( -DDONUT_TESTS)

bento_exe("testStateEngine" "tests" "testStateEngine.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testStateEngine" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

bento_exe("testRenderer" "tests" "testRenderer.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testRenderer" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

bento_exe("testRayTracer" "tests" "testRayTracer.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testRayTracer" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

bento_exe("testFlourLoad" "tests" "testFlourLoad.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testFlourLoad" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

bento_exe("testAllocators" "tests" "testAllocators.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testAllocators" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

if(Vulkan_FOUND)
	bento_exe("testvulkan" "tests" "testvulkan.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
	target_link_libraries("testvulkan" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")
endif(Vulkan_FOUND)

# Copy the binaries
copy_next_to_binary("testFlourLoad" "${THIRD_PARTY_BINARIES}")