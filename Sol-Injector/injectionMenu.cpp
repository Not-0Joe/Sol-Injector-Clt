// logic for printing the injection menu options

#include "injectionMenu.h"

void printInjectionMenU()
{
	std::string injectionMenuArt{ R"(        
	|_______________________           
|_______|  |  |  |  |  |  |  |  |__        
|_______|  6  5  4  3  3  2  1  |__|-------  
|       |_______________________|          
	|                                  )" };


	changeConsoleOutPutColor(consoleColor::Red);
	std::cout << injectionMenuArt << "\n";
	changeConsoleOutPutColor(consoleColor::Green);

	std::cout << "Please pick an injection method\n";
	std::cout << "=====================================================================\n";
	std::cout << "[0] LoadLibrary via CreateRemoteThead\n[1] More options soon...\n";

}