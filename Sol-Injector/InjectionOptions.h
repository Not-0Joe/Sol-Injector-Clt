#pragma once
#include <string>

namespace InjectionOptions {
	bool LoadLibraryWithRemoteThread(const int PID, std::wstring dllPath);
}