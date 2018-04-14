
// donut includes
#include "input/helper.h"
#include "input/defaultinputmanager.h"

namespace donut
{
	// The library input manager
 	static TInputManager* InManager = new TDefaultInputManager();

 	void set_input_manager(TInputManager* _inputManager)
 	{
 		if(InManager != nullptr)
 			delete InManager;
 		InManager = _inputManager;
 	}
	TInputManager*  input_manager()
	{
		return InManager;
	}
}