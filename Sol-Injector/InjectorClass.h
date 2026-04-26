#pragma once

#include "Utils.h"

class InjectorClass
{
public:
	InjectorClass() = default;

	void loadLibraryInjection(const DWORD PID, const std::wstring& dllPath) const;
	std::wstring getDLLPath();

private:
};