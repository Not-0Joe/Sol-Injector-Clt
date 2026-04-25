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
	// check if the program is running with admin privileges, required for injection if not relunch as admin

	return true;
}
