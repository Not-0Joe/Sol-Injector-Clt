// Consolidated ProcessManager implementations
#include "ProcessManager.h"
#include "ConsoleUI.h"
#include "Utils.h"

#include <iostream>
#include <limits>
#include <vector>
#include <string>

// getUserChoice implementation
ProcessManager::UserChoice ProcessManager::getUserChoice()
{
	// handle and sanitize user input
	int userChoice{};
	int ValidChoice = false;

	while (ValidChoice == false)
	{
		std::cin >> userChoice;
		// make use choice is not a char or string
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "ERROR: Invalid option try again\n:";
		}
		// make sure choice is not outside bounds
		if (userChoice < 0 || userChoice > 3)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "ERROR: Invalid option try again\n:";
		}
		else
		{
			ValidChoice = true;
		}
	}

	// return enum so main can use in a switch for options
	switch (static_cast<ProcessManager::UserChoice>(userChoice))
	{
	case ProcessManager::UserChoice::PID:
	{
		return ProcessManager::UserChoice::PID;
		break;
	}
	case ProcessManager::UserChoice::NAME:
	{
		return ProcessManager::UserChoice::NAME;
		break;
	}
	case ProcessManager::UserChoice::LIST:
	{
		return ProcessManager::UserChoice::LIST;
		break;
	}
	case ProcessManager::UserChoice::DISCORD:
	{
		return ProcessManager::UserChoice::DISCORD;
		break;
	}
	default: // should never happen
	{
		std::cerr << "ERROR: defualt case hit in getUserChoice\n";
		return ProcessManager::UserChoice::INVALID;
	}
	}

}

// getUserPID implementation
int ProcessManager::getUserPID()
{
	int PID{ 0 };

	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
	std::cout << "Enter target PID:";
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

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
			Utils::clearInputBuffer();
			ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
			std::cerr << "ERROR: Invaild PID\n:";
			ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
		}
	}

}

std::wstring ProcessManager::getUserProcessName()
{
	std::wstring name{};
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
	std::cout << "Enter target process name (ex. notepad.exe):";
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
	std::wcin >> name;
	return name;
}

// FindTargetProcessWithPID implementation (moved here)
bool ProcessManager::FindTargetProcessWithPID(const DWORD PID)
{
	// Clear screen
	system("CLS");
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
	std::cout << "Checking running processes for PID match...\n";
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

	// snapshot process and put pids into a vector to compare to

	// Gets handle and does error check 
	HANDLE hProcessList = getSnapShotHandle();
	
	// gets first entry and does error check
	PROCESSENTRY32 pe32 = getProcessEntry();

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
			ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::BrightGreen);

			// print name and pid
			std::cout << "PROCESS FOUND!\n";
			std::cout << "=============================================\n";
			std::wcout << "NAME: " << processName[i] << "\n";
			std::cout << "PID:  " << pidList[i] << "\n";
			std::cout << "=============================================\n";
			std::cout << "Press enter to see injection methods:";

			// clear input buffer and wait for key
			Utils::waitForKey();
			// Clear screen for next menu
			system("CLS");
			found = true;
			break;
		}


	}
	if (found == false)
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cout << "Process not found make sure the process is running and try again\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

		// wait for key and return to menu
		Utils::waitForKey();
		system("CLS");

	}
	// clean up handle
	CloseHandle(hProcessList);
	return found;

}
// redundant code but works for now maybe i will improve it later
bool ProcessManager::FindTargetProcessWithName(const std::wstring& name)
{
	// Clear screen
	system("CLS");
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
	std::cout << "Checking running processes for name match...\n";
	ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

	// snapshot process and put pids into a vector to compare to

	// Gets handle and does error check 
	HANDLE hProcessList = getSnapShotHandle();
	
	// gets first entry and does error check
	PROCESSENTRY32 pe32 = getProcessEntry();

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

	for (size_t i{ 0 }; i < processName.size(); i++)
	{
		if (processName[i] == name)
		{
			ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::BrightGreen);

			// print name and pid
			std::cout << "PROCESS FOUND!\n";
			std::cout << "=============================================\n";
			std::wcout << "NAME: " << processName[i] << "\n";
			std::cout << "PID:  " << pidList[i] << "\n";
			std::cout << "=============================================\n";
			std::cout << "Press enter to see injection methods:";

			// clear input buffer and wait for key
			Utils::waitForKey();
			// Clear screen for next menu
			system("CLS");
			found = true;
			break;
		}


	}
	if (found == false)
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cout << "Process not found make sure the process is running and try again\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

		// wait for key and return to menu
		Utils::waitForKey();
		system("CLS");

	}
	// clean up handle
	CloseHandle(hProcessList);
	return found;
}

HANDLE ProcessManager::getSnapShotHandle()
{
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessList == INVALID_HANDLE_VALUE)
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cerr << "ERROR: Handle to process list is NULL\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
		// would return an invalid handle but the caller should check for that and handle it, this is just to avoid a crash if the caller does not check
		return hProcessList;
	}
	
	return hProcessList;

}

PROCESSENTRY32 ProcessManager::getProcessEntry()
{
	PROCESSENTRY32 pe32;
	// set dwSzie
	pe32.dwSize = sizeof(PROCESSENTRY32);
	// both checks for error and grabs the first entry
	if (!Process32First(getSnapShotHandle(), &pe32))
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cerr << "ERROR: Process32First Failed to get first snapshot entry\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
		CloseHandle(getSnapShotHandle());
		return pe32;
	}
	return pe32;
}

int ProcessManager::getPIDFromName(const std::wstring& processName)
{
	HANDLE hProcessList = getSnapShotHandle();
	PROCESSENTRY32 pe32 = getProcessEntry();

	do
	{
		if (processName == pe32.szExeFile)
		{
			return pe32.th32ProcessID;
		}

	} while (Process32Next(hProcessList, &pe32));


}