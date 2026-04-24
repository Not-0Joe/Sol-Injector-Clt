// This file contains the 'main' function. Program execution begins and ends there.

// Basic process injector made by sol this is a free and open source injector, if you use and complie the project
// please leave feed back on improvments that could be made if you have any 

// project source and header files will contain lots of comments as i am still leaning both c++ and the windows api

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>


#include "printUI.h"
#include "changeConsoleTextColor.h"
#include "consoleColorEnums.h"
#include "getUserChoice.h"
#include "userChoiceEnum.h"
#include "getAndPrintProcessList.h"
#include "copyToClipboard.h"
#include "getUserTargetPID.h"
#include "findTargetProcessWithPID.h"
#include "injectionMenu.h"
#include "requestedMethodEnum.h"
#include "getInjectionMethod.h"

int main()
{
    // Set up varibles
    int targetPID{ 0 };
    std::string targetName{ "Null" };
    int menuOption{ 0 };
    
    // Print the UI
    
    printUI();


    // USER CHOICE LOGIC
    
    bool backToMenu = true;
    while (backToMenu == true)
    {
         UserChoice userChoice = getUserChoice();

          if (userChoice == UserChoice::PID)
          {
              const DWORD PID = getUserPID();

              bool targetFound = false;
              targetFound = FindTargetProcessWithPID(PID);

              if (targetFound == true)
              {
                  backToMenu = false;
                  // clear screen print injection options
                  printInjectionMenU();
                  
                  // returns and enum to be used with the injection class
                  // the injection class will hold all of the injection methods
                  // used the enum here to avoid magic numbers 
                   RequestedMethod injectionMethod = getInjectionMethod();

                  // go to injection options class
              }
              else
              {
                  printUI();
              }



          }
          else if (userChoice == UserChoice::NAME)
          {
              // Find Process by name
          }
          if (userChoice == UserChoice::LIST)
          {
              getAndPrintProcesslist();
              printUI();
          }
          else if (userChoice == UserChoice::DISCORD)
          {
              const std::string discordLink = "https://discord.gg/yCEmcGeq3a";
              copyToClipboard(discordLink);
              changeConsoleOutPutColor(consoleColor::BrightCyan);
              std::cout << discordLink << " copied to clipboard...\n";
              changeConsoleOutPutColor(consoleColor::White);
              
              std::cin.ignore(99999999, '\n');
              std::cin.get();
              // clear screen and reprint ui
              system("CLS");
              printUI();

          }

    }


}
