// this will be used to handle all of the backend after a user picks an option and it is handled by input handler
#pragma once
#include "InputHandler.h"

namespace Controller {
	// no need to repete the namespace int the declaration
	void useMenuOption(InputHandler::RequestedOption option);
}