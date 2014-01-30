/////////////////////////////////////////////////////////////////////////////
// Global helper functions - Helpers.cpp
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
// This file contains helper functions
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"		// main symbols
#include "DefaultDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Finds the path to Palemoon in the registry using the key for the latest version
/////////////////////////////////////////////////////////////////////////////
// pszPalemoonPathBuffer can be NULL to simply test if we can even find
// a valid path to Palemoon.

BOOL IsFileExists(LPCTSTR pszFilename) {
	HANDLE hFF; WIN32_FIND_DATA ffData; UINT nLen;
	
	hFF = FindFirstFile(pszFilename, &ffData);
	if (hFF == INVALID_HANDLE_VALUE) return FALSE;
	FindClose(hFF);

	if (FAILED(StringCchLength(ffData.cFileName, MAX_PATH, &nLen))) return FALSE;
	if (nLen == 0) return FALSE;
	return TRUE;
}

BOOL GetCurrentPalemoonProfile(CString *pszProfilePathBuffer) {
	CRegistry cReg;						// Registry class
	CString								// String variables
		szADataPath,					// Application Data path
		szProfilePath,					// Profile path
		szProfileFile,					// profiles.ini path
		szUseful;						// Extra, useful string
	TCHAR szMiniBuf[4];					// Mini-buffer to check for the existance of a profile section
	HANDLE hUseful;						// Extra, useful handle
	int									// Integer variables
		i,								// Good old i counter, we all love him
		nDefaultProfile = -1;			// Default profile, -1 = none
	UINT nRet;							// Unsigned integer return
	DWORD dwRet;						// Double-Word return

	// Get the Application Data location
	CRegistryKey *sfKey = cReg.KeyCurrentUser()->OpenKey(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"), KEY_READ);
	if (sfKey == NULL) return FALSE;
	szADataPath.Empty();
	sfKey->GetStringValue(_T("AppData"), &szADataPath);
	delete sfKey;
	if (szADataPath.IsEmpty()) return FALSE;
	::OutputDebugString(_T("Found the Application Data Folder\r\n"));

	// Trim the \ off if it is there and add the Mozilla\Palemoon
	if (szADataPath[szADataPath.GetLength() - 1] == _T('\\')) szADataPath.TrimRight(_T('\\'));
	szADataPath += "\\Mozilla\\Palemoon";
	
	// Make sure that the profiles.ini file exist
	szProfileFile = szADataPath; szProfileFile += "\\profiles.ini";
	hUseful = CreateFile(szProfileFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hUseful == INVALID_HANDLE_VALUE) return FALSE;
	::OutputDebugString(_T("Found the Mozilla Palemoon profiles.ini\r\n"));
	CloseHandle(hUseful);

	// Move through the profiles to find the default
	for (i = 0;; i++) {
		szUseful.Format(_T("Profile%d"), i);
		if (GetPrivateProfileSection(szUseful, szMiniBuf, 4, szProfileFile) == 0) break;
		nRet = GetPrivateProfileInt(szUseful, _T("Default"), 0, szProfileFile);
		if (nRet > 0) nDefaultProfile = i;
	}

	// Make sure we found the default profile
	if (nDefaultProfile == -1) return FALSE;
	::OutputDebugString(_T("We found the default profile\r\n"));
	
	// Now let get the path
	szProfilePath.Empty();
	szUseful.Format(_T("Profile%d"), nDefaultProfile);
	dwRet = GetPrivateProfileString(szUseful, _T("Path"), _T(""), szProfilePath.GetBufferSetLength(MAX_PATH), MAX_PATH, szProfileFile);
	if (dwRet == 0) return FALSE;

	::OutputDebugString(_T("We have \""));
	::OutputDebugString(szProfilePath);
	::OutputDebugString(_T("\" as the path.\r\n"));

	szProfilePath.Insert(0, _T("\\"));
	szProfilePath.Insert(0, szADataPath);
	szProfilePath.Replace(_T('/'), _T('\\'));

	// Return the profile path
	if (szProfilePath[szProfilePath.GetLength() - 1] == _T('\\')) szProfilePath.TrimRight(_T('\\'));
	if (pszProfilePathBuffer != NULL) *pszProfilePathBuffer = szProfilePath;

	return TRUE;
}

BOOL GetLatestPalemoonInstallDir(CString *pszPalemoonPathBuffer) {
	CRegistry cReg;								// Registry class
	CRegistryKey								// Registry keys
		*mozvKey = NULL;						// Version key
	float										// Float variables
		fLastVer = 0.0,							// Latest validated version we have
		fCurrentVer = 0.0;						// Current version being validated
	CString										// String variables
		szPath,									// Latest version's path
		szMainKey,								// The "{version}\Main" key
		szCurrentPath,							// The currnet path being validated
		szFFExe;								// Some strings
	CArray<CString,CString> aMozVerNames;		// An array
	HANDLE hFFExe;								// A file handle
	int i;										// And the good old i counter

	// Check for the registry key need to use autofind
	CRegistryKey *moziKey = cReg.KeyLocalMachine()->OpenKey(_T("SOFTWARE\\Mozilla\\Mozilla Palemoon"), KEY_READ);
	if (moziKey == NULL) return FALSE;

	// Empty the path so we are sure that it is, we will check to see if it is still empty to determin our success
	szPath.Empty();

	// Get the key names
	moziKey->GetKeyNames(&aMozVerNames);
	if (aMozVerNames.GetSize() == 0) { delete moziKey; return FALSE; }
	::OutputDebugString(_T("Found Mozilla Palemoon's root key\r\n"));

	for (i = 0; i < aMozVerNames.GetSize(); i++) {
		
		// Open the current key
		szMainKey = aMozVerNames[i];
		szMainKey += _T("\\Main");
		mozvKey = moziKey->OpenKey(szMainKey, KEY_READ);

		// If the key was opened successfully
		if (mozvKey != NULL) {
			::OutputDebugString(_T("Found:"));
			::OutputDebugString(szMainKey);

			// Get the version number
			_stscanf(aMozVerNames[i], _T("%f"), (int)&fCurrentVer);

			// If the new key is a greater version than the last,
			if (fCurrentVer > fLastVer) {

				// Lets make sure there is a valid Install Directory value
				if (mozvKey->GetStringValue(_T("Install Directory"), &szCurrentPath) == ERROR_SUCCESS) {
				
					// Trim the \ off if it is there
					if (szCurrentPath[szCurrentPath.GetLength() - 1] == _T('\\')) szCurrentPath.TrimRight(_T('\\'));

					// Make the palemoon.exe path
					szFFExe = szCurrentPath;
					szFFExe += _T("\\palemoon.exe");

					// See if palemoon.exe exists in the path by opening it, only then do we have the right key
					hFFExe = CreateFile(szFFExe, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (hFFExe != INVALID_HANDLE_VALUE) {
						::OutputDebugString(_T(": Palemoon.exe Found!"));

						// Update latest version, and set that path
						fLastVer = fCurrentVer;
						szPath = szCurrentPath;
						CloseHandle(hFFExe);
					} else ::OutputDebugString(_T(": Palemoon.exe not found or invalid"));				
				} else ::OutputDebugString(_T(": No \"Install Directory\""));
			} // fCurrentVer > fLastVepalemoon
			
			::OutputDebugString(_T("\r\n"));
			delete mozvKey;
		}
	}

	if (szPath.IsEmpty()) { delete moziKey; return FALSE; }
	if (pszPalemoonPathBuffer != NULL) *pszPalemoonPathBuffer = szPath;

	delete moziKey;
	return TRUE;
}

BOOL ErrorMessage(HWND hWndParent, LPCTSTR pszMessage, DWORD dwErrorCode) {
	LPVOID pszErrorMsgBuf;		// System error message buffer
	LPTSTR pszMsgBug;			// Format message buffer
	UINT						// Unsigned integer variables
		nEMBLen,				// System error message buffer length
		nMLen;					// Passed and formated message buffer length
	HANDLE hHeap;				// Heap handle
	CString szTitle;			// MessageBox title resources
	
	// Get the system error message
	if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
		dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &pszErrorMsgBuf, 0, NULL )) return FALSE;

	// The the length of the messages
	StringCchLength((LPTSTR)pszErrorMsgBuf, STRSAFE_MAX_CCH, &nEMBLen);
	StringCchLength(pszMessage, STRSAFE_MAX_CCH, &nMLen);

	// Get the heap handle
	hHeap = GetProcessHeap();

	// Figure and allocate the the buffer to make the displayed message
	nMLen = (nEMBLen + nMLen + 4) * sizeof(TCHAR);
	pszMsgBug = (LPTSTR)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, nMLen);
	if (pszMsgBug == NULL) {
		MessageBox(hWndParent, _T("There was a memory error and this program must\r\nend to protect your system from damage."), _T("Memory Error"), MB_OK | MB_ICONERROR);
		AfxAbort();
	}

	// Combine the message
	StringCbCat(pszMsgBug, nMLen, pszMessage);
	StringCbCat(pszMsgBug, nMLen, _T(":\r\n"));
	StringCbCat(pszMsgBug, nMLen, (LPTSTR)pszErrorMsgBuf);

	// Get the title
	szTitle.LoadString(IDS_ERROR_TITLE);

	// Display the string.
	MessageBox(hWndParent, pszMsgBug, szTitle, MB_OK | MB_ICONERROR);

	// Free resources
	LocalFree(pszErrorMsgBuf);
	HeapFree(hHeap, 0, (LPVOID)pszMsgBug);

	// There was no problems, except the one that the user was informed about
	SetLastError(ERROR_SUCCESS);
	return TRUE;
}

// Load and Wait for Palemoon working thread function
UINT LoadAndWaitForPalemoon(LPVOID pParam) {
	CString										// String Variables
		szFF,									// Palemoon.exe path and command-line
		szMessage,								// MessageBox message resources
		szTitle;								// MessageBox title resources
	STARTUPINFO si; PROCESS_INFORMATION pi;		// Create process structures
	LPVOID pszErrorMsgBuf;						// Error message buffer
	DWORD dwErr;								// Error codes
	CDefaultDlg *pDlg = (CDefaultDlg*)pParam;	// The default dialog

	CMutex mutex(TRUE, WAIT_MUTEX);

	if (!mutex.Lock(1000)) {
		::OutputDebugString(_T("Unable to lock loading Mutex, palemoon may still be loaded\r\n"));
		return FALSE;
	}

	// Create the command-line to start Palemoon
	szFF = pDlg->p_szPalemoonPath;
	szFF += _T("\\palemoon.exe -chrome \"chrome://browser/content/web-panels.xul\"");
	
	// Initialize the structures
	::ZeroMemory(&si, sizeof(STARTUPINFO));
	::ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW;

	::OutputDebugString(szFF);
	::OutputDebugString(_T("\r\n"));

	// Load palemoon, hidden
	if (!::CreateProcess(NULL, szFF.GetBuffer(szFF.GetLength()), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, pDlg->p_szPalemoonPath, &si, &pi)) {
		::OutputDebugString(_T("Palemoon failed to run...\r\n"));

		// Since we had an error lets get the error code and kill the timer so it doesn't interupt us
		dwErr = ::GetLastError();
		pDlg->KillTimer(1);
		szTitle.LoadString(IDS_ERROR_TITLE);
		
		switch (dwErr) {

		// If it is a common file or drive error, tell the user what happened and present the option dialog box to change the path
		case ERROR_FILE_NOT_FOUND:
		case ERROR_INVALID_DRIVE:
		case ERROR_PATH_NOT_FOUND:
		case ERROR_NOT_READY:
			szMessage.LoadString(IDS_UNABLETOLOAD_FILE);
			::OutputDebugString(_T("File based error\r\n"));
			
			// Get the system error message
			if (!::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
				dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &pszErrorMsgBuf, 0, NULL )) return FALSE;

			// Format and display the message
			szMessage.FormatMessage(szMessage, pszErrorMsgBuf);
			pDlg->MessageBox(szMessage, szTitle, MB_OK | MB_ICONERROR);

			// Free resources
			::LocalFree(pszErrorMsgBuf);
			
			if (pDlg->ShowPreloaderOptionsDlg() != IDOK) {
				::OutputDebugString(_T("The user click cancel\r\n"));
				szMessage.LoadString(IDS_ENDING_MUSTBEVALID);
				pDlg->MessageBox(szMessage, szTitle, MB_OK | MB_ICONWARNING);
				pDlg->EndDialog(IDCANCEL);
				return FALSE;
			}
			break;

		// Otherwise, tell the user what happened and give the user the choice to present the option dialog box to change the path
		default:
			szMessage.LoadString(IDS_UNABLETOLOAD_OTHER);
			::OutputDebugString(_T("Other error\r\n"));
			
			// Get the system error message
			if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
				dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &pszErrorMsgBuf, 0, NULL )) return FALSE;

			// Format the error message then free the error message buffer
			szMessage.FormatMessage(szMessage, pszErrorMsgBuf);
			::LocalFree(pszErrorMsgBuf);
			
			// Display the message giving the user a choice to display the options dialog
			if (pDlg->MessageBox(szMessage, szTitle, MB_YESNO | MB_ICONERROR) == IDYES) {
				::OutputDebugString(_T("The user chooses to change path\r\n"));

				// If the user selects Yes, display the options dialog
				if (pDlg->ShowPreloaderOptionsDlg() != IDOK) {

					// Make sure that a valid path was entered
					::OutputDebugString(_T("The user clicked cancel\r\n"));
					szMessage.LoadString(IDS_ENDING_MUSTBEVALID);
					pDlg->MessageBox(szMessage, szTitle, MB_OK | MB_ICONWARNING);
					pDlg->EndDialog(IDCANCEL);
					return FALSE;
				}
			} else {

				// The user selected No, so end the Preloader
				szMessage.LoadString(IDS_ENDING);
				pDlg->MessageBox(szMessage);
				pDlg->EndDialog(IDCANCEL);
				return FALSE;
			}
			break;
		}

		// Set the timer
		if (pDlg->p_bTimer == FALSE) {
			pDlg->SetTimer(1, pDlg->p_nTimerInt, NULL);
			pDlg->p_bTimer = TRUE;
		}
	}

	if (::WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED) ::OutputDebugString(_T("Wait Fialed"));

	::OutputDebugString(_T("Unlocking loading mutex...\r\n"));
	mutex.Unlock();
	return TRUE;

}
