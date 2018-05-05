add_definitions( -DDONUT_TESTS)

bento_exe("testStateEngine" "tests" "testStateEngine.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testStateEngine" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

bento_exe("testAllocators" "tests" "testAllocators.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
target_link_libraries("testAllocators" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")

if(Vulkan_FOUND)
	bento_exe("testvulkan" "tests" "testvulkan.cpp" "${DONUT_ENGINE_INCLUDE};${THIRD_PARTY_INCLUDE_DIRS}")
	target_link_libraries("testvulkan" "donut_engine" "bento_sdk" "${THIRD_PARTY_LIBRARIES}")
endif(Vulkan_FOUND)