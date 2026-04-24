#pragma once

#include <Windows.h>
#include <iostream>

namespace ConsoleUI
{
    enum class consoleColor
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Yellow = 6,
        White = 7,
        Gray = 8,
        BrightBlue = 9,
        BrightGreen = 10,
        BrightCyan = 11,
        BrightRed = 12,
        BrightMagenta = 13,
        BrightYellow = 14,
        BrightWhite = 15
    };

    enum class RequestedMethod
    {
        LoadLibraryMethod,

    };

	void printUI();
	void changeConsoleOutPutColor(consoleColor color);
    RequestedMethod getInjectionMethod();
    void getAndPrintProcesslist();
    void printInjectionMenU();

}