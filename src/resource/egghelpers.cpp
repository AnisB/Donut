// Library includes
#include "egghelpers.h"
#include "egg.h"

namespace donut
{
	TEgg* ReadEggFile(const STRING_TYPE& _eggFileLocation)
	{
		TEgg* newEgg = new TEgg();
		std::fstream in;
		in.open(_eggFileLocation.c_str(), std::fstream::in | std::ios::binary);
		if (in.is_open())
		{
			in >> (*newEgg);
			in.close();
		}
		else
		{
			ASSERT_FAIL("File " << _eggFileLocation << " not found");
		}
		return newEgg;
	}
}