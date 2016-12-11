#include "containers/vector.h"
#include "containers/array.h"
#include "base/security.h"

int main()
{
	Donut::TArray<int> intArray(*Donut::CommonAllocator());
	for(int i = 0; i < 1000; ++i)
	{
		intArray.push_back(i);
	}

	ASSERT_MSG(intArray.size() == 1000 && intArray.capacity() >= 1000, "Wrong size");

	for(int i = 999; i > -1; --i)
	{
		ASSERT_MSG(intArray[i] ==  i, "Issue with the vector container");
	}

	intArray.clear();

	ASSERT_MSG(intArray.size() == 0 &&  intArray.capacity() >= 1000, "Wrong size");

	intArray.free();

	ASSERT_MSG(intArray.size() == 0 && intArray.capacity() == 0, "Wrong size");

	Donut::TArray<float> floatVector(*Donut::CommonAllocator());
	for(int i = 0; i < 1000; ++i)
	{
		floatVector.push_back(i);
	}

	ASSERT_MSG(floatVector.size() == 1000 && floatVector.capacity() >= 1000, "Wrong size");

	for(int i = 999; i > -1; --i)
	{
		ASSERT_MSG(floatVector[i] ==  i, "Issue with the vector container");
	}

	floatVector.clear();

	ASSERT_MSG(floatVector.size() == 0 &&  floatVector.capacity() >= 1000, "Wrong size");

	floatVector.free();

	ASSERT_MSG(floatVector.size() == 0 && floatVector.capacity() == 0, "Wrong size");


	GENERAL_INFO("SUCCESS");
}