#pragma once

// class used to hold all the injection methods and logic for the injector.

#include "Utils.h"

class InjectorClass
{
public:
	InjectorClass() = default;

	void loadLibraryInjection(const DWORD PID, const std::wstring& dllPath) const;
	std::wstring getDLLPath();

private:
};