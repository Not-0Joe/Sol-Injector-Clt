#include "printUI.h"

void printUI()
{
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

}

