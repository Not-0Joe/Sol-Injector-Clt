#include "InjectorClass.h"
#include "ConsoleUI.h"
#include "Utils.h"

void InjectorClass::loadLibraryInjection(const DWORD PID, const std::wstring& dllPath) const
{
	
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
