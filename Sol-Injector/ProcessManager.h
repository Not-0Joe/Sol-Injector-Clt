#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <TlHelp32.h>

#include <string>

namespace ProcessManager
{
	enum class UserChoice
	{
		PID,
		NAME,
		LIST,
		DISCORD,

		INVALID,
	};

	enum class RequestedMethod
	{
		loadLib
	};
	
	UserChoice getUserChoice();
	int getUserPID();
	bool FindTargetProcessWithPID(const DWORD PID);
	RequestedMethod getInjectionMethod();
	std::wstring getUserProcessName();
	bool FindTargetProcessWithName(const std::wstring& name);
	HANDLE getSnapShotHandle();
	PROCESSENTRY32 getProcessEntry();
	int getPIDFromName(const std::wstring& processName);


	
}