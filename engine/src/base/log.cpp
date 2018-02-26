// Library includes
#include "base/log.h"
#include "base/base_logger.h"

namespace donut
{
	// This the default logger we provide for the user
	TBaseLogger __donutDefaultLogger;
	TLoggerInterface* defaultLogger = &__donutDefaultLogger;

	// Access the default logger
	TLoggerInterface* default_logger()
	{
		return defaultLogger;
	}

	void set_default_logger(TLoggerInterface* _loggerInterface)
	{
		defaultLogger = _loggerInterface;
	}

	void reset_logger()
	{
		defaultLogger = &__donutDefaultLogger;
	}
}