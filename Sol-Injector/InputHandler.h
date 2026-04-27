// header contains all of our function declarations and related enums
#pragma once
#include <iostream>

namespace InputHandler {
	
	enum RequestedOption
	{
		GetTargetProcessWithPID = 1, // 1 since our menu options start at 1
		ListAllProcesses,
		CopyDiscordLink,
	};

	enum InjectionMethod {
		loadlibraryWithRemoteThread = 1,
		ThreadHijacking,
	};

	RequestedOption getMainMenuOption();
	InjectionMethod getInjectionMethod();
	int getUserPID();
	std::wstring getDllPath();

}

