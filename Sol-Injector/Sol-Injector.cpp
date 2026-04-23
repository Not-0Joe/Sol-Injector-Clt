// This file contains the 'main' function. Program execution begins and ends there.

// Basic process injector made by sol this is a free and open source injector, if you use and complie the project
// please leave feed back on improvments that could be made if you have any 

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "changeConsoleTextColor.h"
#include "consoleColorEnums.h"
#include "getUserChoice.h"
#include "userChoiceEnum.h"
#include "getAndPrintProcessList.h"
#include "copyToClipboard.h"
#include "getUserTargetPID.h"
#include "findTargetProcessWithPID.h"

int main()
{
    // Set up varibles
    int targetPID{ 0 };
    std::string targetName{ "Null" };
    int menuOption{ 0 };


    changeConsoleOutPutColor(consoleColor::Red);
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

    changeConsoleOutPutColor(consoleColor::White);
    std::cout << "\nThanks for using Sol Injector!, Options Below If you paid for this you got scammed\n";

    changeConsoleOutPutColor(consoleColor::Green);
    std::cout << "[0] Select Process wth PID | [1] Select Process with name | [2] List all running processes | [3] Discord Link\n:";
    changeConsoleOutPutColor(consoleColor::White);

    // USER CHOICE LOGIC
    UserChoice userChoice = getUserChoice();

    // if else chain for first options
    if (userChoice == UserChoice::PID)
    {
        int PID = getUserPID();

        bool targetFound = false;
        targetFound = FindTargetProcessWithPID(PID);

        if (targetFound == true)
        {
            // go to injection option
        }

    }
    else if (userChoice == UserChoice::NAME)
    {
        // Find Process by name
    }
    else if (userChoice == UserChoice::LIST)
    {
        getAndPrintProcesslist();
    }
    else if (userChoice == UserChoice::DISCORD)
    {
        const std::string discordLink = "https://discord.gg/yCEmcGeq3a";
        copyToClipboard(discordLink);
        changeConsoleOutPutColor(consoleColor::BrightCyan);
        std::cout << discordLink << " copied to clipboard...\n";
        changeConsoleOutPutColor(consoleColor::White);
    }


}
