/* all the console ui printing logic should be in here try to avoid adding function logic all this should handle is the ui and nothing
else */
#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>
#include <iostream>

namespace UI {
	
	void success(std::string_view message);
	void error(std::string_view message);
	void info(std::string_view message);
	void processInfo(PROCESSENTRY32 pe32);
	
	void printMainMenu();
	void printInjectionMenu();
	
	enum Color {
		Red = 4,
		Green = 10,
		White = 7,
	};

	void changeOutPutColor(Color);

	void printIfTargetFound();
}