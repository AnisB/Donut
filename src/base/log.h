/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

#ifndef DONUT_DEBUG_PRINTER
#define DONUT_DEBUG_PRINTER

// Library includes
#include "stringhelper.h"

// STL Includes
#include <iostream>
#include <cstdio>

namespace Donut
{
	// Defining the different available log levels
	namespace TLogLevel
	{
		enum Type
		{
			DEBUG = 0,
			INFO = 1, 
			WARNING = 2,
			ERROR = 3
		};	
	}

	// The logger interface that must be overloaded by your custom logger
	class TLoggerInterface
	{
	public:
		TLoggerInterface() {}
		virtual ~TLoggerInterface() {}

		// The virtual logging function that must be 
		virtual void Log(TLogLevel::Type _logLevel, const char* _tag, const char* _message) = 0;
	};

	// Access the default logger
	TLoggerInterface* DefaultLogger();
	void SetDefaultLogger(TLoggerInterface* _loggerInterface);

	// General print macro
	#define PRINT_GENERAL(LEVEL, TAG, ENONCE)\
	{\
		STREAM_TYPE collector;\
		collector<<ENONCE;\
		Donut::DefaultLogger()->Log(LEVEL, TAG, collector.str().c_str());\
	}

	// General purpose MACROS
	#if _SILENT
		#define PRINT_DEBUG(TAG, ENONCE) {}
		#define PRINT_INFO(TAG, ENONCE) {}
		#define PRINT_WARNING(TAG, ENONCE) {}
		#define PRINT_ERROR(TAG, ENONCE) {}
	#else
		#if _DEBUG
		#define PRINT_DEBUG(TAG, ENONCE) PRINT_GENERAL(Donut::TLogLevel::DEBUG, TAG, ENONCE)
		#else
		#define PRINT_DEBUG(TAG, ENONCE) {}
		#endif
		#define PRINT_INFO(TAG, ENONCE) PRINT_GENERAL(Donut::TLogLevel::INFO, TAG, ENONCE)
		#define PRINT_WARNING(TAG, ENONCE) PRINT_GENERAL(Donut::TLogLevel::WARNING, TAG, ENONCE)
		#define PRINT_ERROR(TAG, ENONCE) PRINT_GENERAL(Donut::TLogLevel::ERROR, TAG, ENONCE)
	#endif
}
#endif