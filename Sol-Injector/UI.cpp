#include "UI.h"
#include <Windows.h>
// USED FOR SUCCESS MESSAGES
void UI::success(std::string_view message) {
    
    UI::changeOutPutColor(Color::Green);
	std::cout << "Success: " << message << "\n:";
    UI::changeOutPutColor(Color::White);
}
// USED FOR ERROR MESSAGES
void UI::error(std::string_view message) {
    
    UI::changeOutPutColor(Color::Red);
	std::cerr << "Error: " << message << "\n:";
    UI::changeOutPutColor(Color::White);
}
// USED FOR GENERAL INFO
void UI::info(std::string_view message) {
    
    UI::changeOutPutColor(Color::Green);
	std::cout << "Info: " << message << "\n:";
    UI::changeOutPutColor(Color::White);
}
// USED FOR PRINTING THE CURRENT RUNNING PROCESSS
void UI::processInfo(PROCESSENTRY32 pe32)
{
    std::cout << "=========================================\n";
    std::wcout << L"Process name: " << pe32.szExeFile << "\n";
    std::cout << "Process PID:  ";
    UI::changeOutPutColor(Color::Green);
    std::cout << pe32.th32ProcessID << "\n";
    UI::changeOutPutColor(Color::White);
}

void UI::changeOutPutColor(Color color) {
	// static so we can keep this handle for the entire program lifetime avoids needing to get a handle on every call
	static HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!SetConsoleTextAttribute(hStdOutput, static_cast<WORD>(color)))
	{
		UI::error("Failed to set consoleTextAttribute");
		return;
	}

}

void UI::printMainMenu()
{
    UI::changeOutPutColor(Color::Red);
    std::string ConsoleArt{ R"(          
                                   |
                              \    |    /
                          `.   \   |   /   .'
                            `.  \  |  /  .'
                          -.  `. \d8b/ .'  .-'
                            `-. do0o88b .-'
                         <~~~~ 8o0O0o888 ~~~~>
            _____       _   _____       _           _                   
           / ____|     | | |_   _|     (_)         | |            
          | (___   ___ | |   | |  _ __  _  ___  ___| |_ ___  _ __ 
           \___ \ / _ \| |   | | | '_ \| |/ _ \/ __| __/ _ \| '__|  
           ____) | (_) | |  _| |_| | | | |  __/ (__| || (_) | |   
          |_____/ \___/|_| |_____|_| |_| |\___|\___|\__\___/|_|   
                                  _/ |                        
                                 |__/                                                                
                         <~~~~ 8o00o8888 ~~~~>
                            _-' qoo888p '-_   
                         ,-'  ,' /q8p\ `.  `-.   
                            ,'  /  |  \  `.
                          ,'   /   |   \   `.
                              /    |    \
                                   |
    )"};
    std::cout << ConsoleArt << "\n";
    UI::changeOutPutColor(Color::Green);
    std::cout << "\nThanks for using Sol Injector!, Options Below If you paid for this you got scammed\n";
    std::cout << "[1] Select Process wth PID\n[2] List all running processes\n[3] Discord Link\n:";
    UI::changeOutPutColor(Color::White);
}

void UI::printInjectionMenu() {
    
    UI::changeOutPutColor(Color::Red);
    std::string injectionMenuArt{ R"(        
	|_______________________           
|_______|  |  |  |  |  |  |  |  |__        
|_______|  6  5  4  3  3  2  1  |__|-------  
|       |_______________________|          
	|                                  )" };

    std::cout << injectionMenuArt << "\n";
    UI::changeOutPutColor(Color::Green);
    std::cout << "Please pick an injection method\n";
    std::cout << "=====================================\n";
    std::cout << "[1] LoadLibrary via CreateRemoteThead\n[2] More options soon...\n";
}