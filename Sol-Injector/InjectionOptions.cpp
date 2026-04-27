#include "InjectionOptions.h"
#include "UI.h"
#include "Utils.h"
#include <Windows.h>

void InjectionOptions::LoadLibraryWithRemoteThread(const int PID, const std::wstring dllPath)
{
	// get a handle to the target process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	if (!hProcess)
	{
		UI::error("Handle to target process returned NULL");
		return;
	}

	// Calculate memory size needed for the DLL path in the target process
	// wchar_t is 2 bytes, so we multiply the string length by sizeof(wchar_t)
	// Example: 24 characters × 2 bytes = 48 bytes total needed
	SIZE_T remoteMemorySize = (dllPath.size() * sizeof(wchar_t));

	//LPVOID VirtualAllocEx( [in] HANDLE hProcess, [in, optional] LPVOID lpAddress, [in] SIZE_T dwSize, [in] DWORD  flAllocationType, [in] DWORD  flProtect
	// we provide the handle to the target process
	// we use nullptr to tell windows we don't care where its allocated
	// we set the size of the allocated memory to the size of the dllPath since we can't use less and Don't need more, the + 2 is for the null terminator
	// + 2 since a wchar is 2 bytes not 1
	// we set the allocation type to MEM_COMMIT to insure the memory is set to 0 when we later access it
	// we set the file protection to PAGE_READWRITE to allow process our thead in this case to read and write to the memory reagion
	LPVOID remoteMemory = VirtualAllocEx(hProcess, nullptr, remoteMemorySize + 2, MEM_COMMIT, PAGE_READWRITE);

	if (!remoteMemory)
	{
		UI::error("RemotePath return Null");
		CloseHandle(hProcess);
		return;
	}

	// this is not needed but we can use it to check the exact number of bytes written to the memory space
	// the total should be equal to out remoteMemorySize will just be to test 
	SIZE_T numberOFBytesWriten{};

	// we need to write the dllPath into memory we allocated we can do this by using 
	if (!WriteProcessMemory(hProcess, remoteMemory, dllPath.c_str(), remoteMemorySize + 2, &numberOFBytesWriten))
	{
		UI::error("WriteProcessMemory Failed and returned 0");
		VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return;
	}

	UI::success("Number of bytes written into target");
	std::cout << numberOFBytesWriten << "\n";

	// we need the address of loadlibrary to pass to our remote thread
	// GetProcAddress [in] HMODULE hModule [in] LPCSTR  lpProcName
	// GetModuleHandleA [in, optional] LPCSTR lpModuleName
	FARPROC loadlibAddr = GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryW");

	if (!loadlibAddr)
	{
		UI::error("GetProcAddress failed and returnd NULL");
		CloseHandle(hProcess);
		return;
	}

	// CreateRemoteThread and have it run loadlibrary
	// 1 Handle to the target process
	// 2 Thread security attributes (nullptr = default)
	// 3 Stack size (0 = default)
	// 4 Function to execute (LoadLibrary)
	// 5 Parameter for the function (The DLL path address)
	// 6 Creation flags (0 = start immediately)
	// 7 Output variable for thread ID (nullptr = not needed)
	HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)loadlibAddr, remoteMemory, 0, nullptr);

	if (!hThread)
	{
		UI::error("CreateRemoteThread failed and returned NULL");
		CloseHandle(hProcess);
		return;
	}

	// wait for thread to complete and store its exit code
	DWORD exitCode = WaitForSingleObject(hThread, INFINITE);

	if (exitCode == WAIT_OBJECT_0)
	{
		UI::success("Thread Completed execution of LoadLibrary In Target Process");
	}
	else
	{
		UI::error("Thread provided error code");
	}
	
	Utils::clearAndIgnoreInput();
	Utils::waitForKey();
	CloseHandle(hProcess);
	CloseHandle(hThread);
	VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
	return; 

}