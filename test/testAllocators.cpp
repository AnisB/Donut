// Bento includes
#include <bento_base/security.h>

// Engine includes
#include "bento_collection/vector.h"
#include "base/log.h"

using namespace donut;
int main()
{
	bento::Vector<int> intArray(*bento::common_allocator());
	for(int i = 0; i < 1000; ++i)
	{
		intArray.push_back(i);
	}

	assert_msg(intArray.size() == 1000 && intArray.capacity() >= 1000, "Wrong size");

	for(int i = 999; i > -1; --i)
	{
		assert_msg(intArray[i] ==  i, "Issue with the vector container");
	}

	intArray.clear();

	assert_msg(intArray.size() == 0 &&  intArray.capacity() >= 1000, "Wrong size");

	intArray.free();

	assert_msg(intArray.size() == 0 && intArray.capacity() == 0, "Wrong size");

	bento::Vector<float> floatVector(*bento::common_allocator());
	for(int i = 0; i < 1000; ++i)
	{
		floatVector.push_back(i);
	}

	assert_msg(floatVector.size() == 1000 && floatVector.capacity() >= 1000, "Wrong size");

	for(int i = 999; i > -1; --i)
	{
		assert_msg(floatVector[i] ==  i, "Issue with the vector container");
	}

	floatVector.clear();

	assert_msg(floatVector.size() == 0 &&  floatVector.capacity() >= 1000, "Wrong size");

	floatVector.free();

	assert_msg(floatVector.size() == 0 && floatVector.capacity() == 0, "Wrong size");


	PRINT_INFO("Test", "SUCCESS");
}