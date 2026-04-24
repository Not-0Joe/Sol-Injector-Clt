#pragma once

// cotains helper functions and other things i could not fit into the other 2 header

#include <iostream>
#include <string>
#include <limits>
#include <cstring> // for memcpy
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <fcntl.h>


namespace Utils
{
	void clearInputBuffer();
	void copyToClipboard(const std::string& text);
	void waitForKey();
}