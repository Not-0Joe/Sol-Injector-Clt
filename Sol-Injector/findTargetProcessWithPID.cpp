// get list of PIDs put them into a vector then walk the list and compare with the PID
// the user enterd

#include "findTargetProcessWithPID.h"
#include "changeConsoleTextColor.h"
#include "waitForKey.h"

// get PID

bool FindTargetProcessWithPID(const DWORD PID)
{
	// Clear screen
	system("CLS");
	changeConsoleOutPutColor(consoleColor::Green);
	std::cout << "Checking running processes for PID match...\n";
	changeConsoleOutPutColor(consoleColor::White);

	// snapshot process and put pids into a vector to compare to

	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessList == INVALID_HANDLE_VALUE)
	{
		changeConsoleOutPutColor(consoleColor::Red);
		std::cerr << "ERROR: Handle to process list is NULL\n";
		changeConsoleOutPutColor(consoleColor::White);
		CloseHandle(hProcessList);
		return false;
	}

	PROCESSENTRY32 pe32;
	// set dwSzie
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// both checks for error and grabs the first entry
	if (!Process32First(hProcessList, &pe32))
	{
		changeConsoleOutPutColor(consoleColor::Red);
		std::cerr << "ERROR: Process32First Failed to get first snapshot entry\n";
		changeConsoleOutPutColor(consoleColor::White);
		CloseHandle(hProcessList);
		return false;
	}
	
	// vectors to store pid list and name 
	std::vector<DWORD> pidList;
	std::vector<std::wstring> processName;

	// while there is a next entry in the list push it onto the vector to make the list
	do
	{
		pidList.push_back(pe32.th32ProcessID);
		processName.push_back(pe32.szExeFile);

	} while (Process32Next(hProcessList, &pe32));

	// index that list compare if the users PID matchs one found in the list

	bool found = false;

	for (size_t i{ 0 }; i < pidList.size(); i++)
	{
		if (pidList[i] == PID)
		{
			changeConsoleOutPutColor(consoleColor::BrightGreen);
	

			// print name and pid
			std::cout << "PROCESS FOUND!\n";
			std::cout << "=============================================\n";
			std::wcout << "NAME: " << processName[i] << "\n";
			std::cout << "PID:  " << pidList[i] << "\n";
			std::cout << "=============================================\n";
			std::cout << "Press enter to see injection methods:";
			
			// clear input buffer and wait for key
			waitForKey();
			// Clear screen for next menu
			system("CLS");
			found = true;
			break;
		}
		
		
	}
	if (found == false)
	{
		changeConsoleOutPutColor(consoleColor::Red);
		std::cout << "Process not found make sure the process is running and try again\n";
		changeConsoleOutPutColor(consoleColor::White);
		
		// wait for key and return to menu
		waitForKey();
		system("CLS");

	}
	// clean up handle
	CloseHandle(hProcessList);
	return found;

}