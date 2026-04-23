#include "getAndPrintProcessList.h"
#include "changeConsoleTextColor.h"
#include "consoleColorEnums.h" // for color change while printing process list
#include "waitForKey.h"
#include <limits>

// take snapshot of all running process and print names and PID


void getAndPrintProcesslist()
{
	// retruns a handle to a snapshot of all running process's
	const HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// validate handle
	if (hProcessList == INVALID_HANDLE_VALUE)
	{
		std::cerr << "ERROR: CreateToolhelp32Snapshot returning invalid handle\n";
		CloseHandle(hProcessList);
		return;
		// write error to log file
	}

	// make container for process info
	PROCESSENTRY32 pe32;
	// set size of structure REQUIRED
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// we are both validating and putting info into pe32 here
	// ex. got to list grab first entry paste into pe32 return bool, if there is a next entry
	if (!Process32First(hProcessList, &pe32))
	{
		std::cerr << "ERROR: Process32First returned bad value for pe32\n";
		CloseHandle(hProcessList);
		return;
	}

	changeConsoleOutPutColor(consoleColor::Red);
	std::cout << "Listing all processes PID and names.....\n";
	changeConsoleOutPutColor(consoleColor::White);

	// print out process list
	do
	{
		std::cout << "========================================\n";
		std::wcout << "PROCESS NAME:" << pe32.szExeFile << "\n";
		std::wcout << "PID:" << pe32.th32ProcessID << "\n";

	} while (Process32Next(hProcessList, &pe32));
	std::cout << "========================================\n";
	changeConsoleOutPutColor(consoleColor::Green);
	std::cout << "Process list done printing\nPress any key to contuine:";
	changeConsoleOutPutColor(consoleColor::White);
	
	// clear buffer and wait for user to press a key
	waitForKey();
	// clear screen
	system("CLS");
	
	// clean up handle after we are done with it
	CloseHandle(hProcessList);

}