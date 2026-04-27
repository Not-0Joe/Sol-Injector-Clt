#include "InputHandler.h"
#include "UI.h"
#include "Utils.h"
#include <Windows.h>


InputHandler::RequestedOption InputHandler::getMainMenuOption() {
	// gets the main menu choice from the user and handles errors
	
	int option{ 0 };
	std::cin >> option;
	
	while(!std::cin || option < 1 || option >= 5)
	{
		Utils::clearAndIgnoreInput();
		UI::error("Invalid option try again");
		std::cin >> option;
	}
	// cast it into our enum, type the int will map the enumrators
	return static_cast<InputHandler::RequestedOption>(option);
	

}

InputHandler::InjectionMethod InputHandler::getInjectionMethod()
{
	int InjectionMethod{ 0 };
	std::cin >> InjectionMethod;

	if (!std::cin || InjectionMethod < 0 || InjectionMethod > 3)
	{
		Utils::clearAndIgnoreInput();
		UI::error("Invaild injection method try again");
		std::cin >> InjectionMethod;
	}
	// cast into enum return to caller
	return static_cast<InputHandler::InjectionMethod>(InjectionMethod);

}

int InputHandler::getUserPID()
{
	int PID{ 0 };
	std::cin >> PID;
	
	while(!std::cin)
	{
		Utils::clearAndIgnoreInput();
		UI::error("Invalid PID try again");
		Utils::waitForKey();
		std::cin >> PID;
	}

	return PID;

}

std::wstring InputHandler::getDllPath()
{
	OPENFILENAME ofn;
	WCHAR szFile[MAX_PATH]; // buffer used for the file path 260 is the max size for a file path in Windows

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFilter = L"DLL Files (*.dll)\0*.dll\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;


	if (GetOpenFileName(&ofn) == TRUE) {
		return std::wstring(ofn.lpstrFile);
	}
	else
	{
		UI::error("Unable to get dll path");
		return L"";
	}
}