// Helpers.cpp: Unexported helper functions
//////////////////////////////////////////////////////////////////////
//
//   Copyright (C)2004 6XGate Incorporated
//
//   This file is part of RegistryClass.
//
//   RegistryClass is free software; you can redistribute it and/or modify
//   it under the terms of the GNU Lesser General Public License as published
//   by the Free Software Foundation; either version 2.1 of the License, or
//   (at your option) any later version.
//
//   RegistryClass is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU Lesser General Public License for more details.
//
//   You should have received a copy of the GNU Lesser General Public License
//   along with RegistryClass; if not, write to the Free Software
//   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Extra Non Exported Helper Functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
DWORD RegRecurDeleteKey (HKEY hOpenKey, LPCTSTR pszSubKey) {
	HKEY hKey;
	DWORD nKeyCount, nKeyNameLen, nLen; LPTSTR pszKeyNameBuf = NULL; DWORD dwRet; ULONG i;

	// Make sure we don't have a NULL SubKey string
	if (pszSubKey && lstrlen(pszSubKey)) {
		if ((dwRet = RegOpenKeyEx(hOpenKey, pszSubKey, 0, KEY_ALL_ACCESS, &hKey))==ERROR_SUCCESS) {
			// Get information about the keys, and allocate a buffer for the names
			RegQueryInfoKey(hKey, NULL, NULL, NULL, &nKeyCount, &nKeyNameLen, NULL, NULL, NULL, NULL, NULL, NULL);
			if (nKeyCount > 0) {
				nKeyNameLen++;
				pszKeyNameBuf = (LPTSTR)malloc(nKeyNameLen * sizeof(TCHAR));
				for (i = 0; i < nKeyCount; i++) {
					nLen = nKeyNameLen;
					dwRet = RegEnumKeyEx(hKey, 0, pszKeyNameBuf, &nLen, NULL, NULL, NULL, NULL);
					if (dwRet==ERROR_NO_MORE_ITEMS) break;
					else if (dwRet!=ERROR_SUCCESS) { free(pszKeyNameBuf); return dwRet; }
					dwRet = RegRecurDeleteKey(hKey, pszKeyNameBuf);
					if (dwRet!=ERROR_SUCCESS) { free(pszKeyNameBuf); return dwRet; }
				}
				free(pszKeyNameBuf);
				pszKeyNameBuf = NULL;
			}
			RegCloseKey(hKey);
			RegDeleteKey(hOpenKey, pszSubKey);
		} else return dwRet;
	} else return ERROR_BADKEY;
	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
// Copies a registry key all its subkeys and values to a destination
// key.
// Parameters:
//		hSrcKey:		The handle to an already opened key to copy
//		hDestKey:		The handle to an already opened key to copy to
BOOL RegCopyKey (HKEY hSrcKey, HKEY hDestKey) {
	ULONG c, nValueCount, nKeyCount, nValueNameLen, nKeyNameLen, nValueLen, nLen, nDLen;
	LPTSTR pszNameBuf = NULL;
	DWORD nRet, dwType = 0;
	HKEY hFromKey, hToKey;
	BYTE *pValueBuf = NULL;

	// Get the information from the key we need to copy it.
	nRet = ::RegQueryInfoKey(hSrcKey, NULL, NULL, NULL, &nKeyCount, &nKeyNameLen, NULL, &nValueCount, &nValueNameLen, &nValueLen, NULL, NULL);
	if (nRet!=ERROR_SUCCESS) return FALSE;

	// Make sure there is room for the null terminator character
	nKeyNameLen++; nValueNameLen++;

	// Alloc a name buffer
	pszNameBuf = (LPTSTR)malloc(nKeyNameLen);

	if (nKeyCount) for (c = 0; c < nKeyCount; c++) {
		// Get the key under the current key
		nLen = nKeyNameLen;
		nRet = ::RegEnumKeyEx(hSrcKey, c, pszNameBuf, &nLen, NULL, NULL, NULL, NULL);
		if (nRet!=ERROR_SUCCESS) { free(pszNameBuf); return FALSE; }

		// Open the source key
		nRet = ::RegOpenKeyEx(hSrcKey, pszNameBuf, 0, KEY_ALL_ACCESS, &hFromKey);
		if (nRet!=ERROR_SUCCESS) { free(pszNameBuf); return FALSE; }

		// Create a key with its name at the destination
		nRet = ::RegCreateKeyEx(hDestKey, pszNameBuf, NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &hToKey, NULL);
		if (nRet!=ERROR_SUCCESS) { free(pszNameBuf); return FALSE; }

		// Copy it and its keys
		nRet = ::RegCopyKey (hFromKey, hToKey);
		if (nRet!=TRUE) { free(pszNameBuf); return FALSE; }
		::RegCloseKey(hFromKey);
		::RegCloseKey(hToKey);
	}
	free(pszNameBuf);
	pszNameBuf = NULL;

	// Alloc a value buffer
	pValueBuf = (BYTE*)malloc(nValueLen);
	pszNameBuf = (LPTSTR)malloc(nValueNameLen);
	if (nValueCount) for (c = 0; c < nValueCount; c++) {
		// Now get the current value
		nLen = nValueNameLen;
		nDLen = nValueLen;
		nRet = ::RegEnumValue(hSrcKey, c, pszNameBuf, &nLen, NULL, &dwType, pValueBuf, &nDLen);
		if (nRet!=ERROR_SUCCESS) { free(pValueBuf); free(pszNameBuf); return FALSE; }

		// Copy the value to the new key
		nRet = ::RegSetValueEx(hDestKey, pszNameBuf, NULL, dwType, pValueBuf, nDLen);
		if (nRet!=ERROR_SUCCESS) { free(pValueBuf); free(pszNameBuf); return FALSE; }
	}
	free(pValueBuf);
	free(pszNameBuf);
	pValueBuf = NULL; pszNameBuf = NULL;
	return TRUE;
}