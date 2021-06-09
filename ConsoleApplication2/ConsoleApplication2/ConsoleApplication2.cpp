#include <iostream>
#include "windows.h"
#include <wininet.h>
#include <tlhelp32.h>
#include <string>
#include <cstdio>

using namespace std;
//DWORD FindProcessId(const std::wstring& processName);
DWORD GetProcessIdByName();
const wchar_t *processname;// = L"putty.exe";
int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		LPCSTR dllName;// = "C:\\Users\\USER\\source\\repos\\Dll1\\Debug\\Dll1.dll";
		string name;
		string stringPath;
		//Get name file target
		stringPath = argv[1];
		wstring wstrPath = wstring(stringPath.begin(), stringPath.end());
		processname = wstrPath.c_str();
		//Get PID process target
		INT pId = GetProcessIdByName();
		
		//Get name file DLL
		name = argv[2];
		dllName = name.c_str();
		cout <<"PID:"<< pId<<"\nPath DLL:" << dllName;

		HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
		LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
		LPVOID dereercomp = VirtualAllocEx(h, NULL, strlen(dllName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		WriteProcessMemory(h, dereercomp, dllName, strlen(dllName), NULL);

		HANDLE asdc = CreateRemoteThread(h, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, dereercomp, 0, NULL);

		WaitForSingleObject(asdc, INFINITE);
		VirtualFreeEx(h, dereercomp, strlen(dllName), MEM_RELEASE);
		CloseHandle(asdc);
		CloseHandle(h);
	}
	else
	{
		cout << "Error:: \nCMD: ConsoleApplication2.exe <nametarget> <DLL_Path>";
	}
	return 0;
}

DWORD GetProcessIdByName() {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_wcsicmp(entry.szExeFile, processname) == 0)
			{
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);
	return 0;
}


