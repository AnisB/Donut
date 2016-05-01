// Library includes
#include "egghelpers.h"
#include "egg.h"

namespace Donut
{
	TEgg* ReadEggFile(const STRING_TYPE& _eggFileLocation)
	{
		TEgg* newEgg = new TEgg();
		std::fstream in;
		in.open(_eggFileLocation.c_str(), std::fstream::in | std::ios::binary);
		in >> (*newEgg);
		in.close();
		return newEgg;
	}
}