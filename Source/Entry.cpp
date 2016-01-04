#include "pch.hpp"

BOOL WINAPI DllMain ( HMODULE base_addr, DWORD reason, LPCVOID reserved )
{
	
	if ( reason == DLL_PROCESS_ATTACH )
	{
		CreateThread ( nullptr, 0, MainThread, nullptr, 0, nullptr );
	}

	return TRUE;
}
