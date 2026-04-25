#include "InjectorClass.h"
#include "ConsoleUI.h"
#include "Utils.h"

void InjectorClass::loadLibraryInjection(const DWORD PID, const std::wstring& dllPath) const
{
	// GET HANDLE TO TARGET PROCESS
	//=========================================================================================================================
   
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	std::cout << "Attempting to open handle to process with PID: " << PID << "...\n";

    // check if the handle is valid
    if (!hProcess)
    {
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
        std::cerr << "ERROR: OpenProcess returned invalid handle\nExiting ...";
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
        Utils::waitForKey();
        exit(1);
    }
    else
    {
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
		std::cout << "Successfully opened handle to process with PID: " << PID << "\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
    }
    // ========================================================================================================================
    // Allocate memory in the target process for the DLL path
    // LPVOID is a pointer to any type
    // we pass in the handle to the target process
    // Null meaing we don't care where the memory is allocated and let windows decide
    // size of the string 
    // and we allocate the same size as the string plus 1 for the null terminator, this is important to avoid a buffer overflow
    // MEM_COMMIT tells windows to commit the memory, this means that the memory will be allocated and initialized to zero, this is important to avoid any issues with uninitialized memory
    // PAGE_READWRITE tells windows we want to be able to read and write to the memory, this is important because we will be writing the DLL path
    
    // we need to get the size of the dll path in bytes, and since we are using a std::stringw 
    SIZE_T pathSize = (dllPath.length() + 1) * sizeof(wchar_t);
    
    LPVOID pRemotePath = VirtualAllocEx(hProcess, NULL, pathSize, MEM_COMMIT, PAGE_READWRITE);
	// check if the memory allocation was successful
	if (!pRemotePath)
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cerr << "ERROR: VirtualAllocEx failed to allocate memory in the target process\nExiting ...";
        CloseHandle(hProcess);
		Utils::waitForKey();
		exit(1);
	}
    else
    {
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
		std::cout << "Successfully allocated memory in the target process for the DLL path\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
    }
    
    // this checks and validates if the memory was allocated
	if (!WriteProcessMemory(hProcess, pRemotePath, dllPath.c_str(), pathSize, NULL))
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cerr << "ERROR: WriteProcessMemory failed to write the DLL path to the target process\nExiting ...";
		Utils::waitForKey();
        CloseHandle(hProcess);
		exit(1);
	}
    else
    {
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
		std::cout << "Successfully wrote the DLL path to the target process\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
    }

	// this gets the address of LoadLibraryA in kernel32.dll, this is important because we will be using this function to load the DLL into the target process
    LPVOID pLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryW");
	// check if we got the address of LoadLibraryA
	if (!pLoadLibrary)
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cerr << "ERROR: GetProcAddress failed to get the address of LoadLibraryA\nExiting ...";
		Utils::waitForKey();
		exit(1);
	}
	else
    {
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
		std::cout << "Successfully got the address of LoadLibraryA\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
	}

    // 5. Start a new thread in the victim process that calls LoadLibraryA(pRemotePath)
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pRemotePath, 0, NULL);
    
	if (!hThread)
	{
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		std::cerr << "ERROR: CreateRemoteThread failed to create a remote thread in the target process\nExiting ...";
		Utils::waitForKey();
		exit(1);
	}
    else
    {
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
		std::cout << "Successfully created a remote thread in the target process to load the DLL\n";
		ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
    }

	Utils::waitForKey();
   
    // clean up
    if (hThread) {
        CloseHandle(hThread);
        CloseHandle(hProcess);
    }
 
}



std::wstring InjectorClass::getDLLPath()
{
   // we don't want to force the user to type out the absoule path since thats user prone to user error
   // so we will use OPENFILENAME to open a windows and let the user pick the dll
    OPENFILENAME ofn;
	WCHAR szFile[MAX_PATH]; // buffer used for the file path 260 is the max size for a file path in Windows
    
    // replaces all the memory at the location of ofn with 0, to clear any old data
	ZeroMemory(&ofn, sizeof(ofn)); 
    // sets the size of the structure, this is a required step for Windows
    ofn.lStructSize = sizeof(ofn);
    // tells windows there is no owner to the dialog box
	ofn.hwndOwner = NULL;
	// sets the size of the buffer for the file path, this is a required step for Windows
    ofn.lpstrFile = szFile; 
	// sets the filters for the dialog box, this will only show .dll files and all files there is alot going on here i have write up in my personal notes
	// more or less its the lable and the filter for showing the acual files, the \0 is used to separate the different filters and the last \0 is used to indicate the end of the filter string
	// needed to prefix with L for long since lpstrFilter is a pointer to a WCHAR 
    ofn.lpstrFilter = L"DLL Files (*.dll)\0*.dll\0All Files (*.*)\0*.*\0";
    // sets the first character of the file path buffer to null terminator, this is a required step for Windows
	ofn.lpstrFile[0] = '\0'; 
	// sets the max size of the buffer so we don't have a buffer overflow if the user selects a file path that is too long
	ofn.nMaxFile = sizeof(szFile);
    // tells the opened window to have the first filter option selected by default
    ofn.nFilterIndex = 1;
	// seprate buffer if u wanted just the file name without path
    // Null meaning only worry about the full path
    ofn.lpstrTitle = NULL;
	ofn.nMaxFileTitle = 0;
    // use default logic when decideing what folder to open starting with last used
    ofn.lpstrInitialDir = NULL;
	// flag to control the behavior of the dialog box, this will make sure the user selects a file that exists and a path that exists, and it will not change the current working directory of the program when the dialog box is closed
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        

            if (GetOpenFileName(&ofn) == TRUE) {
                return std::wstring(ofn.lpstrFile);
            }
            else
            {
		        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
		        std::cerr << "ERROR: GetOpenFileName failed or user cancelled the dialog\nExiting ...";
                ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
		        Utils::waitForKey();
                exit(1);
            }
    
    // did write up on all functions and fully understand structure, dispite more ai use then i would have liked for the last few functions
    // write up and notes on community server if intrested in a more in depth explanation of flags
}
