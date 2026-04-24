// logic and error check for picking current avalible injection method

#include "getInjectionMethod.h"
#include "changeConsoleTextColor.h"

RequestedMethod getInjectionMethod()
{
	int userChoice{ 0 };
	std::cin >> userChoice;

	// if user enters a char clear and ignore it
	if (!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(999999, '\n');
		changeConsoleOutPutColor(consoleColor::Red);
		std::cerr << "ERROR: invalid option try again\n:";
		changeConsoleOutPutColor(consoleColor::White);
	}
	else if (userChoice < 0 || userChoice > 10)
	{	
		// if userChoice is outside of options
		// 10 is just going to be a place holder for now

		std::cin.ignore(999999, '\n');
		changeConsoleOutPutColor(consoleColor::Red);
		std::cerr << "ERROR: invalid option try again\n";
		changeConsoleOutPutColor(consoleColor::White);
		std::cout << ":";
	}
	
	// convert userchoice into the enum to be passed back to main
	switch (static_cast<RequestedMethod>(userChoice))
	{
	case RequestedMethod::LoadLibraryMethod:
	{
		return RequestedMethod::LoadLibraryMethod;
		break;
	}
	default:
	{
		break;
	}
	}

}