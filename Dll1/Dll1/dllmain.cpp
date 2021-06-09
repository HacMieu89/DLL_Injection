#include <windows.h>
#include <stdio.h>
#include <wininet.h>
#pragma comment(lib,"Wininet.lib")
BOOL APIENTRY DllMain(HINSTANCE hInst     /* Library instance handle. */,
	DWORD reason        /* Reason this function is being called. */,
	LPVOID reserved     /* Not used. */)
{
	
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(0, L"From DLL\nHello World",L"Process Attach", MB_ICONINFORMATION);
		break;
		
	case DLL_PROCESS_DETACH:
		MessageBox(0, L"From DLL\nHello World", L"Process Detach", MB_ICONINFORMATION);
		break;
		
	case DLL_THREAD_ATTACH:
		
		
		MessageBox(0, L"From DLL\nHello World", L"Thread Attach", MB_ICONINFORMATION);
		break;
		
	case DLL_THREAD_DETACH:
		MessageBox(0, L"From DLL\nHello World", L"Thread Detach", MB_ICONINFORMATION);
		break;
	}
	
	return TRUE;
}