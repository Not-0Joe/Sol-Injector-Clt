// contains the changeConsoleOutPutColor function logic

#include "consoleColorEnums.h"

void changeConsoleOutPutColor(consoleColor color)
{
	// our handle to the std output so we can access
	// and change the color of the output text
	HANDLE hConsloe = GetStdHandle(STD_OUTPUT_HANDLE);

	// Validate HANDLE

	if (hConsloe == INVALID_HANDLE_VALUE)
	{
		changeConsoleOutPutColor(consoleColor::Red);
		std::cerr << "ERROR: getStdHandle returned invalid handle exiting";
		changeConsoleOutPutColor(consoleColor::White);
		// todo: add writing error to log file logic here
	}

	// API Function uses the handle to the console and sets the text attribute
	// we static cast the class enum to avoid error, tells compiler "yes i know u want a WORD type"
	SetConsoleTextAttribute(hConsloe, static_cast<WORD>(color));

	// closing the handle here is not needed as STD_OUTPUT_HANDLE is managed by the OS
	// and will clean up after the program is closed, STD_OUTPUT_HANDLE is a Global "pipe"
}