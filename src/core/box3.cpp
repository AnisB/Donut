// Library include
#include "box3.h"
#include "butter/vector3.h"

// External includes
#include <float.h>

namespace Donut
{
	TBox3::TBox3()
	{
		Reset();
	}

	TBox3::~TBox3()
	{

	}

	void TBox3::Reset()
	{
		min = vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		max = -vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	}
}