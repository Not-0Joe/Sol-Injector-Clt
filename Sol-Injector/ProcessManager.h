#pragma once
#include <Windows.h>

namespace ProcessManager
{
	bool checkProcessListForTarget(const int PID);
	void listAllProcesses();
}