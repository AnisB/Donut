#pragma once

// Library includes
#include "defines.h"
#include <input/inputManager.h>

namespace donut
{
	// Sets the input manager 
	void set_input_manager(TInputManager* parInputManager);
	TInputManager*  input_manager();
}