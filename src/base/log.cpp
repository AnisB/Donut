// Library includes
#include "log.h"
#include "baselogger.h"

namespace Donut
{
	// This the default logger we provide for the user
	TBaseLogger __donutDefaultLogger;
	TLoggerInterface* defaultLogger = &__donutDefaultLogger;

	// Access the default logger
	TLoggerInterface* DefaultLogger()
	{
		return defaultLogger;
	}

	void SetDefaultLogger(TLoggerInterface* _loggerInterface)
	{
		defaultLogger = _loggerInterface;
	}
}