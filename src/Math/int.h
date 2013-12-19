


#ifndef DONUT_MATH_INT
#define DONUT_MATH_INT

#include "Base/DebugPrinters.h"


struct TInt2
{
	TInt2()
	{
	}

	TInt2(int parX, int parY)
	{
		val[0] = parX;
		val[1] = parY;
	}
	TInt2(const TInt2& parTInt2)
	{
		val[0] = parTInt2.val[0];
		val[1] = parTInt2.val[1];
	}

	int val[2];
};

#endif //DONUT_MATH_INT