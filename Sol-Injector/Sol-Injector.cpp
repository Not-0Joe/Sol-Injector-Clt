// This file contains the 'main' function. Program execution begins and ends there.

// Basic process injector made by sol this is a free and open source injector, if you use and complie the project
// please leave feed back on improvments that could be made if you have any 

// project source and header files will contain lots of comments as i am still leaning both c++ and the windows api


// utils header 
#include "Utils.h"

// UI Interface header
#include "ConsoleUI.h"

// Process manangment header
#include "ProcessManager.h"

// injecton class
#include "InjectorClass.h"

int main()
{ 

    bool isAdmin = Utils::admincheck();

    if (isAdmin == false)
    {

        // recode to have this notify the user to run as admin then exit and self reluch with admin privleges

        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::Red);
        std::cerr << "ERROR: Injector is not running with admin privileges, please run as admin and try again\nExiting ...";
        ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
        Utils::waitForKey();
        return 1;
    }
    
    // Set up varibles
    int targetPID{ 0 };
    std::string targetName{ "Null" };
    int menuOption{ 0 };
    bool targetFound = false;
    
    // Print the UI
    ConsoleUI::printUI();
    
    // USER CHOICE LOGIC
    bool backToMenu = true;
    while (backToMenu == true)
    {
         ProcessManager::UserChoice userChoice = ProcessManager::getUserChoice();

          if (userChoice == ProcessManager::UserChoice::PID)
          {
              const DWORD PID = ProcessManager::getUserPID();

              targetFound = ProcessManager::FindTargetProcessWithPID(PID);

              if (targetFound == true)
              {
                  backToMenu = false;
                  // clear screen print injection options
                  ConsoleUI::printInjectionMenU();
                  
                  // returns and enum to be used with the injection class
                  // the injection class will hold all of the injection methods
                  // used the enum here to avoid magic numbers 
                  ConsoleUI::RequestedMethod injectionMethod = ConsoleUI::getUserInjectionChoice();

                  switch (injectionMethod)
                  {
                  case ConsoleUI::RequestedMethod::LoadLibraryMethod:
                  {
                      InjectorClass injector{};
					  const std::wstring dllPath = injector.getDLLPath();

                       // do injection

                  }
                   }

               }
              else
              {
                  ConsoleUI::printUI();
              }



          }
          else if (userChoice == ProcessManager::UserChoice::NAME)
          {
              // Find Process by name

              const std::wstring name = ProcessManager::getUserProcessName();

              targetFound = ProcessManager::FindTargetProcessWithName(name);

              if (targetFound == true)
              {
                  backToMenu = false;
                  // clear screen print injection options
                  ConsoleUI::printInjectionMenU();

                  // returns and enum to be used with the injection class
                  // the injection class will hold all of the injection methods
                  // used the enum here to avoid magic numbers 
                  ConsoleUI::RequestedMethod injectionMethod = ConsoleUI::getUserInjectionChoice();

                  switch (injectionMethod)
                  {
                  case ConsoleUI::RequestedMethod::LoadLibraryMethod:
                  {
                      InjectorClass injector{};
                      const std::wstring dllPath = injector.getDLLPath();


                  }
                  }

               }
              else
              {
                  ConsoleUI::printUI();
              }
           }
           else if (userChoice == ProcessManager::UserChoice::LIST)
           {
              ConsoleUI::getAndPrintProcesslist();
              ConsoleUI::printUI();
           }
           else if (userChoice == ProcessManager::UserChoice::DISCORD)
           {
              const std::string discordLink = "https://discord.gg/yCEmcGeq3a";
              Utils::copyToClipboard(discordLink);
              ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::BrightCyan);
              std::cout << discordLink << " copied to clipboard...\n";
              ConsoleUI::changeConsoleOutPutColor(ConsoleUI::consoleColor::White);
              
              Utils::waitForKey();
              Utils::clearInputBuffer();
              // clear screen and reprint ui
              system("CLS");
              ConsoleUI::printUI();
            }

    }

}
