// Library includes
#include "baselogger.h"

namespace Donut
{
	// Color list
	#define DEFAULT "\033[0m"
	#define BLACK "\033[0;30m"
	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define ORANGE "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[0;35m"
	#define CYAN "\033[0;36m"
	#define WHITE "\033[0;37m"

	TBaseLogger::TBaseLogger()
	{

	}

	TBaseLogger::~TBaseLogger()
	{

	}

	void TBaseLogger::Log(TLogLevel::Type _logLevel, const char* _tag, const char* _message)
	{
		switch(_logLevel)
		{
			case TLogLevel::DEBUG:
			{
				std::cout<<BLUE<<"[DEBUG]";
			}
			break;
			case TLogLevel::INFO:
			{
				std::cout<<GREEN<<"[INFO]";
			}
			break;
			case TLogLevel::WARNING:
			{
				std::cout<<ORANGE<<"[WARNING]";
			}
			break;
			case TLogLevel::ERROR:
			{
				std::cout<<RED<<"[ERROR]";
			}
			break;
		};
		std::cout<<"["<<_tag<<"]"<<_message<<DEFAULT<<std::endl;
	}
}