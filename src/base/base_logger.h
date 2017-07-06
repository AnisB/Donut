#ifndef BASE_LOGGER_SYSTEM_H
#define BASE_LOGGER_SYSTEM_H

// Library includes
#include "log.h"

namespace donut
{
	class TBaseLogger : public TLoggerInterface
	{
	public:
		TBaseLogger();
		~TBaseLogger();

		// The virtual logging function that must be 
		virtual void log(TLogLevel::Type _logLevel, const char* _tag, const char* _message);
	};
}

#endif // BASE_LOGGER_SYSTEM_H