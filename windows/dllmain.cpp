#pragma once
#include "pch.h"

#include "../Kontrollneger.h"

DWORD WINAPI nigga(HMODULE hModule)
{
	AllocConsole();
	FILE* fConsole;
	freopen_s(&fConsole, "CONOUT$", "w", stdout);

	DWORD procId = GetProcId(L"csgo.exe");
	DWORD clientBaseAddr = GetModuleBaseAddress(procId, L"client_panorama.dll");
	DWORD engineBaseAddr = GetModuleBaseAddress(procId, L"engine.dll");

	Kontrollneger kontrollneger(clientBaseAddr, engineBaseAddr);

	while (kontrollneger.isRunning() && !(GetAsyncKeyState(VK_NUMPAD5) & 0x8000))
	{
		if (kontrollneger.update())
		{
			Sleep(6);
		}
	}

	fclose(fConsole);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(0, L"ICH FICGHE DEINE MUDDA", L"ERROR", MB_ICONINFORMATION || MB_ABORTRETRYIGNORE);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)nigga, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
