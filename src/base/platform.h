#pragma once

// External includes
#if __posix__
	// Includes
	#include <unistd.h>
	#include <execinfo.h>
	#include <stdint.h>

	// Defines
	#define FUNCTION_NAME __PRETTY_FUNCTION__

#elif WIN32
	// Includes
	#include <stdint.h>

	// defines
	#define FUNCTION_NAME __func__
#endif