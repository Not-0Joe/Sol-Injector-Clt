#include "ProcessManager.h"
#include "UI.h"
#include <tlhelp32.h>
#include <vector>
#include <string>

bool ProcessManager::checkProcessListForTarget(const int PID)
{
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hProcessList)
	{
		UI::error("Handle to process list returned null");
		return false;
	}
	// Create the structure to hold our data
	PROCESSENTRY32 pe32;
	// Set the size of the structure
	pe32.dwSize = sizeof(pe32);

	// If the first entry in the list fails, close the handle and return to the caller
	if (!Process32First(hProcessList, &pe32))
	{
		UI::error("First Entry in process list failed");
		CloseHandle(hProcessList);
		return false;
	}

	do
	{
		if (pe32.th32ProcessID == PID)
		{
			UI::success("Process was found!");
			CloseHandle(hProcessList);
			return true;
		}

	} while (Process32Next(hProcessList, &pe32));

	CloseHandle(hProcessList);
	return false;

}

void ProcessManager::listAllProcesses()
{
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hProcessList)
	{
		UI::error("Handle to process list returned null");
	}

	// Create the structure to hold our data
	PROCESSENTRY32 pe32;
	// Set the size of the structure
	pe32.dwSize = sizeof(pe32);

	// If the first entry in the list fails, close the handle and return to the caller
	if (!Process32First(hProcessList, &pe32))
	{
		UI::error("First Entry in process list failed");
		CloseHandle(hProcessList);
		return;
	}

	do
	{
		UI::processInfo(pe32);

	} while (Process32Next(hProcessList, &pe32));

	CloseHandle(hProcessList);
	

}