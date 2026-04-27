#pragma once
#include <string>

namespace InjectionOptions {
	void LoadLibraryWithRemoteThread(const int PID, std::wstring dllPath);
}