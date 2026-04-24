#include "ConsoleUI.h"
#include "Utils.h"
#include <Windows.h>

void ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor color)
{
    // our handle to the std output so we can access
    // and change the color of the output text
    HANDLE hConsloe = GetStdHandle(STD_OUTPUT_HANDLE);

    // Validate HANDLE

    if (hConsloe == INVALID_HANDLE_VALUE)
    {
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
        std::cerr << "ERROR: getStdHandle returned invalid handle exiting";
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
        // todo: add writing error to log file logic here
    }

    // API Function uses the handle to the console and sets the text attribute
    // we static cast the class enum to avoid error, tells compiler "yes i know u want a WORD type"
    SetConsoleTextAttribute(hConsloe, static_cast<WORD>(color));

    // closing the handle here is not needed as STD_OUTPUT_HANDLE is managed by the OS
    // and will clean up after the program is closed, STD_OUTPUT_HANDLE is a Global "pipe"
}

void ConsoleUI::printUI()
{
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
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
    )" };
    printf("%s", ConsoleArt.c_str());

    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
    std::cout << "\nThanks for using Sol Injector!, Options Below If you paid for this you got scammed\n";

    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
    std::cout << "[0] Select Process wth PID | [1] Select Process with name | [2] List all running processes | [3] Discord Link\n:";
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

}

void printInjectionMenU()
{
    std::string injectionMenuArt{ R"(        
	|_______________________           
|_______|  |  |  |  |  |  |  |  |__        
|_______|  6  5  4  3  3  2  1  |__|-------  
|       |_______________________|          
	|                                  )" };


    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
    std::cout << injectionMenuArt << "\n";
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);

    std::cout << "Please pick an injection method\n";
    std::cout << "=====================================================================\n";
    std::cout << "[0] LoadLibrary via CreateRemoteThead\n[1] More options soon...\n";

}

ConsoleUI::RequestedMethod ConsoleUI::getInjectionMethod()
{
    int userChoice{ 0 };
    std::cin >> userChoice;

    // if user enters a char clear and ignore it
    if (!std::cin)
    {
        Utils::clearInputBuffer();
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
        std::cerr << "ERROR: invalid option try again\n:";
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
    }
    else if (userChoice < 0 || userChoice > 10)
    {
        // if userChoice is outside of options
        // 10 is just going to be a place holder for now

        Utils::clearInputBuffer();
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
        std::cerr << "ERROR: invalid option try again\n";
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
        std::cout << ":";
    }

    // if both checks are passed

    // convert userchoice into the enum to be passed back to main
    switch (static_cast<ConsoleUI::RequestedMethod>(userChoice))
    {
    case ConsoleUI::RequestedMethod::LoadLibraryMethod:
    {
        return ConsoleUI::RequestedMethod::LoadLibraryMethod;
        break;
    }
    default:
    {
        break;
    }
    }

}

void ConsoleUI::printInjectionMenU()
{
    std::string injectionMenuArt{ R"(        
	|_______________________           
|_______|  |  |  |  |  |  |  |  |__        
|_______|  6  5  4  3  3  2  1  |__|-------  
|       |_______________________|          
	|                                  )" };


    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
    std::cout << injectionMenuArt << "\n";
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);

    std::cout << "Please pick an injection method\n";
    std::cout << "=====================================================================\n";
    std::cout << "[0] LoadLibrary via CreateRemoteThead\n[1] More options soon...\n";

}

void ConsoleUI::getAndPrintProcesslist()
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

    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
    std::cout << "Listing all processes PID and names.....\n";
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

    // print out process list
    do
    {
        std::cout << "========================================\n";
        std::wcout << "PROCESS NAME:" << pe32.szExeFile << "\n";
        std::wcout << "PID:" << pe32.th32ProcessID << "\n";

    } while (Process32Next(hProcessList, &pe32));
    std::cout << "========================================\n";
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Green);
    std::cout << "Process list done printing\nPress any key to contuine:";
    ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);

    // clear buffer and wait for user to press a key
    Utils::waitForKey();
    // clear screen
    system("CLS");

    // clean up handle after we are done with it
    CloseHandle(hProcessList);

}