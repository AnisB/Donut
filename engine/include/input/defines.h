#pragma once

namespace donut
{
	namespace TKeyCode
	{
		enum Type
		{
			// Letters
			A=65,
			B=66,  
			C=67,  
			D=68,  
			E=69,  
			F=70,  
			G=71,  
			H=72,  
			I=73,  
			J=74,  
			K=75,  
			L=76,  
			M=77,  
			N=78,  
			O=79,  
			P=80,  
			Q=81,  
			R=82,  
			S=83,  
			T=84,  
			U=85,  
			V=86,  
			W=87,  
			X=88,  
			Y=89,  
			Z=90,  
			// Directions
			RIGHT=262,
	 		LEFT=263,
			DOWN=264,
			UP=265,

			// Other
			PAGE_UP = 266,
			PAGE_DOWN = 267,
			ESCAPE = 256
		};
	}

	namespace TMouseCode
	{
		enum Type
		{
			BUTTON_1=0,
			BUTTON_2=1,
			BUTTON_3=2,
			BUTTON_4=3,
			BUTTON_5=4,
			BUTTON_6=5,
			BUTTON_7=6,
			BUTTON_8=7,
		};
	}
}