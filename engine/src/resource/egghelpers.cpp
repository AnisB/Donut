// Library includes
#include "resource/egghelpers.h"
#include "resource/egg.h"

namespace donut
{
	TEgg* ReadEggFile(const std::string& _eggFileLocation)
	{
		TEgg* newEgg = new TEgg();
		std::fstream in;
		in.open(_eggFileLocation.c_str(), std::fstream::in | std::ios::binary);
		if (in.is_open())
		{
			in >> (*newEgg);
			in.close();
		}
		return newEgg;
	}
}