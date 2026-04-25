// function logic for utils functions

#include "Utils.h"
#include <limits>
#include <conio.h>

void Utils::copyToClipboard(const std::string& text)
{

	// open and stop other programs from using the clipboard and error check
	// NULL telling windows its for this task / program
	if (!OpenClipboard(NULL))
	{
		std::cerr << "ERROR: OpenClipboard returned false\n";
		return;
	}

	// Empty content of clipbord if any
	EmptyClipboard();

	// get a handle to the global memory on the public shared heap
	// allocate the segment and tell windows we want it to be movable via GMEM_MOVEABLE
	// tell the size to be allocated, will be the size of the string + 1 byte for the null terminator
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);

	// error check

	if (hGlobal == NULL)
	{
		std::cerr << "Error: Handle to Global memory returned NULL\n";
		CloseClipboard();
		return;
	}

	// copy the data into the segment and lock the memory
	void* pMem = GlobalLock(hGlobal);

	// memcpy can not use the handle directly to access the buffer we need to provided it the address
	memcpy(pMem, text.c_str(), text.size() + 1);
	// unlock the memory so windows can nicely move it again if needed
	GlobalUnlock(hGlobal);

	// error check and set the data
	if (!SetClipboardData(CF_TEXT, hGlobal))
	{
		std::cerr << "ERROR: SetClipboardData failed\n";
		GlobalFree(hGlobal);
	}
	// clean up after use
	CloseClipboard();

}

void Utils::clearInputBuffer()
{
	if (!std::cin)
	{
		std::cin.clear();
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Utils::waitForKey()
{
	// this avoids the newline issue i was having with std::cin.get();
	 _getch();
}

bool Utils::admincheck()
{
	// varible we will hand back to caller as yes or no
	bool elevated = false;
	// empty handle used to store the token handle we will get from the process
	HANDLE token = NULL;

	// OpenProcessToken opens a handle to the token of the current process 
	// OpenProcessToken syntax: OpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
	// GetCurrentProcess() returns a pseudo handle to the current process,
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
	{
		// structure used to store the elevation information we will get from the token
		TOKEN_ELEVATION elevation;
		// setting the size of the structure for the API call, this is a required step for Windows
		DWORD size = sizeof(TOKEN_ELEVATION);
		// GetTokenInformation retrieves a specified type of information about an access token
		// it takes the handle to the token its checking, what type of information we want to get
		// &elevation is the address of the structure we want to fill with the information
		// the lenght of the structure its size in bytes 
		// &size it writes how much data it actually wrote to the structure, this is used for error checking and to make sure we got all the information we expected
		if (GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &size))
		{
			// we save the result of the check into the elevated variable to return to the caller, this will be true if the token is elevated and false if it is not
			elevated = elevation.TokenIsElevated;
		}

		// if token returns a valid handle we close the handle then reutrn the result
		if (token) CloseHandle(token);
		return elevated;
	}
	else
	{
		// log to error file or use error logging lib maybe?

		std::cerr << "ERROR: OpenProcessToken failed\n";
		return false;

	}

}


void Utils::reluchWithAdminPrivileges()
{
	char szPath[MAX_PATH];
	GetModuleFileNameA(NULL, szPath, MAX_PATH);

	// This is the structure we will pass to ShellExecuteExA
	SHELLEXECUTEINFOA sei{ sizeof(sei) };
	sei.lpVerb = "runas"; // this tells windows to run the program with admin privileges
	sei.lpFile = szPath; // this is the path to our executable
	sei.hwnd = NULL; // this is the handle to the parent window, we don't have one so we set it to NULL
	sei.nShow = SW_NORMAL; // this tells windows how to show the new process, we want it to be normal so we set it to SW_NORMAL

	if (!ShellExecuteExA(&sei))
	{
		std::cerr << "\nERROR: ShellExecuteExA failed to relaunch with admin privileges\n";
	}
}