/////////////////////////////////////////////////////////////////////////////
// Process Watching Functions - processes.cpp
/////////////////////////////////////////////////////////////////////////////
// Copyright (C)2004 6XGate Incorporated
//
// This file is part of Palemoon Preloader
//
// Palemoon Preloader is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Palemoon Preloader is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Palemoon Preloader; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
/////////////////////////////////////////////////////////////////////////////
// This file contains system specific process watching functions
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "processes.h"
#include <psapi.h>
#include <Tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Internal Declarations
/////////////////////////////////////////////////////////////////////////////

#define PSAPI_MAX_PROCESSES		1024

// Library Modules
HMODULE hKernel = NULL;		// Toolhelp32 Kernel handle
HMODULE	hPSAPI = NULL;		// PSAPI Library handle

// PSAPI Functions Pointers and Names
typedef BOOL (WINAPI *ENUMPROCESSES)(DWORD* lpidProcess, DWORD cb, DWORD* cbNeeded);
typedef BOOL (WINAPI *ENUMPROCESSMODULES)(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded);
typedef DWORD (WINAPI *GETMODULEBASENAME)(HANDLE hProcess, HMODULE hModule, LPTSTR lpBaseName, DWORD nSize);

ENUMPROCESSES				_EnumProcesses = NULL;
ENUMPROCESSMODULES			_EnumProcessModules = NULL;
GETMODULEBASENAME			_GetModuleBaseName = NULL;

#define _ENUMPROCESSES					"EnumProcesses"
#define _ENUMPROCESSMODULES				"EnumProcessModules"
#ifdef _UNICODE
#define _GETMODULEBASENAME				"GetModuleBaseNameW"
#else //_UNICODE
#define _GETMODULEBASENAME				"GetModuleBaseNameA"
#endif //_UNICODE

// Toolhelp32 Functions Pointers and Names
typedef HANDLE (WINAPI *CREATETOOLHELP32SNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID);
typedef BOOL (WINAPI *PROCESS32FIRST)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL (WINAPI *PROCESS32NEXT)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);

CREATETOOLHELP32SNAPSHOT	_CreateToolhelp32Snapshot = NULL;
PROCESS32FIRST				_Process32First = NULL;
PROCESS32NEXT				_Process32Next = NULL;

#define _CREATETOOLHELP32SNAPSHOT		"CreateToolhelp32Snapshot"
#ifdef _UNICODE
#define _PROCESS32FIRST					"Process32FirstW"
#define _PROCESS32NEXT					"Process32NextW"
#else //_UNICODE
#define _PROCESS32FIRST					"Process32First"
#define _PROCESS32NEXT					"Process32Next"
#endif //_UNICODE

// IsProcessActive Functions
typedef BOOL (WINAPI *ISPROCESSACTIVE)(LPCTSTR lpszModuleName);
BOOL WINAPI PSAPI_IsProcessActive(LPCTSTR lpszModuleName);
BOOL WINAPI TH32_IsProcessActive(LPCTSTR lpszModuleName);

ISPROCESSACTIVE		_IsProcessActive = NULL;

/////////////////////////////////////////////////////////////////////////////

BOOL WINAPI InitializeProcessWatcher(void) {
	// Initialize the OSVersionInfo
	OSVERSIONINFO ov; ZeroMemory(&ov, sizeof(OSVERSIONINFO));
	ov.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	// Get the version
	// GetVersionEx(&ov); // The following is depreciated
	// NT Platforms will use the PSAPI library
	//if (ov.dwPlatformId == VER_PLATFORM_WIN32_NT) {
		//if (ov.dwMajorVersion >= 4) {
			hPSAPI = LoadLibrary(_T("PSAPI.DLL"));
			if (hPSAPI == NULL) {
				MessageBox(NULL, _T("Unable to load PSAPI.DLL."), _T("Error Loading Library"), MB_OK);
				return FALSE;
			}
			
			// Get the functions
			_EnumProcesses = (ENUMPROCESSES)GetProcAddress(hPSAPI, _ENUMPROCESSES);
			_EnumProcessModules = (ENUMPROCESSMODULES)GetProcAddress(hPSAPI, _ENUMPROCESSMODULES);
			_GetModuleBaseName = (GETMODULEBASENAME)GetProcAddress(hPSAPI, _GETMODULEBASENAME);
			_IsProcessActive = PSAPI_IsProcessActive;
			::OutputDebugString(_T("Using PSAPI Process Watching\r\n"));

		/*} else return FALSE;
	// 9X Platforms will use the Toolhelp32 functions
	} else {
		if (ov.dwMajorVersion < 4) return FALSE;
		hKernel = GetModuleHandle(_T("kernel32.dll"));
		if (hKernel == NULL) return FALSE;

		// Get the functions
		_CreateToolhelp32Snapshot = (CREATETOOLHELP32SNAPSHOT)GetProcAddress(hKernel, _CREATETOOLHELP32SNAPSHOT);
		_Process32First = (PROCESS32FIRST)GetProcAddress(hKernel, _PROCESS32FIRST);
		_Process32Next = (PROCESS32NEXT)GetProcAddress(hKernel, _PROCESS32NEXT);
		_IsProcessActive = TH32_IsProcessActive;
		::OutputDebugString(_T("Using Toolhelp32 Process Watching\r\n"));

	} */

	return TRUE;
}

BOOL WINAPI DeInitializeProcessWatcher(void) {
	if (hPSAPI != NULL) FreeLibrary(hPSAPI);
	return TRUE;
}

BOOL WINAPI IsProcessActive(LPCTSTR lpszModuleName) { 
	return _IsProcessActive(lpszModuleName);
}

BOOL WINAPI PSAPI_IsProcessActive(LPCTSTR lpszModuleName) {
	DWORD dwProcesses[PSAPI_MAX_PROCESSES], dwRet = 0, dwDummy = 0;
	DWORD i = 0; HANDLE hProc = NULL; HMODULE hModule = NULL; TCHAR szProcessName[MAX_PATH];

	// Enumerate the processes
	if (_EnumProcesses(dwProcesses, sizeof(dwProcesses), &dwRet)) for (; i < dwRet; i++) {
		hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcesses[i]);

		// Get and compare the processes base name
		if (hProc != NULL) {
			if (_EnumProcessModules(hProc, &hModule, sizeof(hModule), &dwDummy))
				if (_GetModuleBaseName(hProc, hModule, szProcessName, MAX_PATH * sizeof(TCHAR)))
				if (_tcsicmp(szProcessName, lpszModuleName) == 0) { CloseHandle(hProc); return TRUE; }
			CloseHandle(hProc);
		}
	}

	return FALSE;
}

BOOL WINAPI TH32_IsProcessActive(LPCTSTR lpszModuleName) {
	HANDLE hSnapShot; PROCESSENTRY32 pe; 
 	
	// Get a snapshot
	hSnapShot = _CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE) return FALSE;
	
	// Initialize the Process structure
	ZeroMemory(&pe, sizeof(PROCESSENTRY32));
	pe.dwSize = sizeof(PROCESSENTRY32);

	// If the first 
	if (_Process32First(hSnapShot, &pe)) {
		do if (_tcsicmp(pe.szExeFile, lpszModuleName) == 0) { CloseHandle(hSnapShot); return TRUE; } while (_Process32Next(hSnapShot, &pe));
		CloseHandle(hSnapShot); 
	}

	return FALSE;
}
