// gets the PID from the user to be used with findTargetProcessWithPID

#include "getUserTargetPID.h"
#include "changeConsoleTextColor.h"

int getUserPID()
{
	int PID{ 0 };

	changeConsoleOutPutColor(consoleColor::Green);
	std::cout << "Enter target PID:";
	changeConsoleOutPutColor(consoleColor::White);

	while (true)
	{
		std::cin >> PID;
		
		if (std::cin)
		{
			return PID;
			break; 
		}
		else
		{
			// clear fail state if user enter a char or string, and clear the buffer
			std::cin.clear();
			std::cin.ignore(9999999999, '\n');
			changeConsoleOutPutColor(consoleColor::Red);
			std::cerr << "ERROR: Invaild PID\n:";
			changeConsoleOutPutColor(consoleColor::White);
		}
	}


}