// This file contains the 'main' function. Program execution begins and ends there.

// Basic process injector made by sol this is a free and open source injector, if you use and complie the project
// please leave feed back on improvments that could be made if you have any 

#include "UI.h"
#include "InputHandler.h"
#include "Controller.h"


int main()
{

	while (true)
	{
		UI::printMainMenu();
		InputHandler::RequestedOption userChoice = InputHandler::getMainMenuOption();
		Controller::useMenuOption(userChoice);
	}
	

}
