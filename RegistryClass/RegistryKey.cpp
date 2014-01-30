// RegistryKey.cpp: implementation of the CRegistryKey class.
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
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CRegistryKey::IsRegKey(HKEY hKey) {
#ifndef _WIN32_WCE
	switch((LONG)this->m_myKey) {
	case HKEY_CLASSES_ROOT:
	case HKEY_CURRENT_USER:
	case HKEY_LOCAL_MACHINE:
	case HKEY_USERS:
	case HKEY_CURRENT_CONFIG:
	case HKEY_DYN_DATA:
	case HKEY_PERFORMANCE_DATA:
		return TRUE;
		break;
	default:
		// Why does this not work on the HIVE registry keys???
		DWORD nUnused;
		return ::GetHandleInformation (hKey, &nUnused);
	}
#else //_WIN32_WCE
	return TRUE;
#endif //_WIN32_WCE
}

CRegistryKey::CRegistryKey(){}
CRegistryKey::~CRegistryKey() {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	::RegCloseKey (this->m_myKey);
}

// Opens an existing sub-key
CRegistryKey *CRegistryKey::OpenKey(LPCTSTR lpSubKey) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; CRegistryKey *newKey;
	HKEY hNewKey;
	
	// Open the existing registry key
	nRet = ::RegOpenKeyEx (this->m_myKey, lpSubKey, 0, KEY_ALL_ACCESS, &hNewKey);

	if (nRet!=ERROR_SUCCESS) return NULL;
	
	// Create a new registry key class, initialize it and return it
	newKey = new CRegistryKey;
	newKey->m_myKey = hNewKey;
	
	return newKey;
}

// Opens an existing sub-key
CRegistryKey *CRegistryKey::OpenKey(LPCTSTR lpSubKey, REGSAM accessDesired) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; CRegistryKey *newKey;
	HKEY hNewKey;
	
	// Open the existing registry key
	nRet = ::RegOpenKeyEx (this->m_myKey, lpSubKey, 0, accessDesired, &hNewKey);

	if (nRet!=ERROR_SUCCESS) return NULL;
	
	// Create a new registry key class, initialize it and return it
	newKey = new CRegistryKey;
	newKey->m_myKey = hNewKey;
	
	return newKey;
}


// Creates a new or opens an existing sub-key
CRegistryKey *CRegistryKey::CreateKey(LPCTSTR lpSubKey) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; CRegistryKey *newKey;
	HKEY hNewKey;
	
	// Create a new or open an existing registry key.
	nRet = ::RegCreateKeyEx (this->m_myKey, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hNewKey, NULL);
	
	if (nRet!=ERROR_SUCCESS) return NULL;

	// Create a new registry key class, initialize it and return it
	newKey = new CRegistryKey;
	newKey->m_myKey = hNewKey;
	
	return newKey;
}

// Creates a new or opens an existing sub-key
CRegistryKey *CRegistryKey::CreateKey(LPCTSTR lpSubKey, REGSAM accessDesired) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; CRegistryKey *newKey;
	HKEY hNewKey;
	
	// Create a new or open an existing registry key.
	nRet = ::RegCreateKeyEx (this->m_myKey, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, accessDesired, NULL, &hNewKey, NULL);
	
	if (nRet!=ERROR_SUCCESS) return NULL;

	// Create a new registry key class, initialize it and return it
	newKey = new CRegistryKey;
	newKey->m_myKey = hNewKey;
	
	return newKey;
}


// Deletes a sub-key
LONG CRegistryKey::DeleteKey(LPCTSTR lpSubKey) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegRecurDeleteKey(this->m_myKey, lpSubKey);
}

// Deletes a value
LONG CRegistryKey::DeleteValue(LPCTSTR lpValueName) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegDeleteValue(this->m_myKey, lpValueName);
}

// Sets a value of any type
LONG CRegistryKey::SetValue(LPCTSTR lpValueName, DWORD dwType, const BYTE* lpData, DWORD cbData) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegSetValueEx(this->m_myKey, lpValueName, 0, dwType, lpData, cbData);
}

// Sets a binary value
LONG CRegistryKey::SetBinaryValue(LPCTSTR lpValueName, const BYTE* lpData, DWORD cbData) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegSetValueEx(this->m_myKey, lpValueName, 0, REG_BINARY, lpData, cbData);
}

// Sets an integer value
LONG CRegistryKey::SetIntegerValue(LPCTSTR lpValueName, DWORD dwData) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegSetValueEx(this->m_myKey, lpValueName, 0, REG_DWORD, (BYTE*)&dwData, sizeof(dwData));
}

// Sets a string value
LONG CRegistryKey::SetStringValue(LPCTSTR lpValueName, LPCTSTR lpString) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegSetValueEx(this->m_myKey, lpValueName, 0, REG_SZ, (BYTE*)lpString, (lstrlen(lpString) + 1) * sizeof (TCHAR));
}

// Sets and expanding string value
LONG CRegistryKey::SetExpandStringValue(LPCTSTR lpValueName, LPCTSTR lpString) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	return ::RegSetValueEx(this->m_myKey, lpValueName, 0, REG_EXPAND_SZ, (BYTE*)lpString, (lstrlen(lpString) + 1) * sizeof (TCHAR));
}

// Gets a string registry value (REG_SZ/REG_EXPAND_SZ) or a string containing a integer value (REG_DWORD)
LONG CRegistryKey::GetStringValue(LPCTSTR lpValueName, CString *rString) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; BYTE *lpData = NULL; DWORD dwDataLen; ULONG nRegDataType;

	// Get value length and allocate buffer
	nRet = ::RegQueryValueEx(this->m_myKey, lpValueName, 0, &nRegDataType, NULL, &dwDataLen);
	lpData = (BYTE*)::malloc(dwDataLen);

	nRet = ::RegQueryValueEx(this->m_myKey, lpValueName, 0, &nRegDataType, lpData, &dwDataLen);
	if (nRet!=ERROR_SUCCESS) { ::free(lpData); return nRet; }

	// Lets convert any datatypes we understand
	switch(nRegDataType) {
	case REG_SZ:
		*rString = (LPCTSTR)lpData;
		break;
	case REG_EXPAND_SZ:
		*rString = (LPCTSTR)lpData;
		break;
	case REG_DWORD:
		(*rString).Format(_T("%u"), *(LPDWORD)lpData);
		break;
	default:
		::free(lpData);
		lpData = NULL;
		return ERROR_CANNOT_CONVERT_VALUE;
	}
	::free(lpData);
	lpData = NULL;
	return ERROR_SUCCESS;
}

// Gets the length of all the registry values
LONG CRegistryKey::QueryMaxValueLen() {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	ULONG nValLen;

	::RegQueryInfoKey(this->m_myKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &nValLen, NULL, NULL);
	return nValLen;
}

// Gets an integer value (REG_DWORD)
LONG CRegistryKey::GetIntegerValue(LPCTSTR lpValueName, LPDWORD lpdwValue) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; BYTE *lpData = NULL; DWORD dwDataLen; ULONG nValLen, nRegDataType;

	// Get value length and allocate buffer
	nRet = ::RegQueryValueEx(this->m_myKey, lpValueName, 0, &nRegDataType, NULL, &nValLen);
	lpData = (BYTE*)::malloc(nValLen);

	nRet = ::RegQueryValueEx(this->m_myKey, lpValueName, 0, &nRegDataType, lpData, &dwDataLen);
	if (nRet!=ERROR_SUCCESS) { ::free(lpData); return nRet; }

	// Lets convert any datatypes we understand
	switch(nRegDataType) {
	case REG_DWORD:
		*lpdwValue = *(LPDWORD)lpData;
		break;
	default:
		::free(lpData);
		lpData = NULL;
		return ERROR_CANNOT_CONVERT_VALUE;
	}
	::free(lpData);
	lpData = NULL;
	return ERROR_SUCCESS;
}

// Gets a value and returns a RegiatryValue class for advanced registry operations
LONG CRegistryKey::GetValue(LPCTSTR lpValueName, CRegistryValue &rValue) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	LONG nRet; BYTE *lpData = NULL; DWORD dwDataLen; ULONG nValLen, nRegDataType;

	// Get value length and allocate buffer
	nRet = ::RegQueryValueEx(this->m_myKey, lpValueName, 0, &nRegDataType, NULL, &nValLen);
	lpData = (BYTE*)::malloc(nValLen);

	nRet = ::RegQueryValueEx(this->m_myKey, lpValueName, 0, &nRegDataType, lpData, &dwDataLen);
	if (nRet!=ERROR_SUCCESS) { ::free(lpData); lpData = NULL; return nRet; }

	// Fill the value class with data... fun ay.
	rValue.SetValue (lpData, dwDataLen, nRegDataType);
	rValue.m_bSet = TRUE;
	
	::free(lpData);
	lpData = NULL;
	return ERROR_SUCCESS;	
}

LONG CRegistryKey::QueryMaxKeyNameLen() {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	ULONG nKeyLen;

	::RegQueryInfoKey(this->m_myKey, NULL, NULL, NULL, NULL, &nKeyLen, NULL, NULL, NULL, NULL, NULL, NULL);
	return nKeyLen;
}

LONG CRegistryKey::QueryMaxValueNameLen() {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	ULONG nValLen;

	::RegQueryInfoKey(this->m_myKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &nValLen, NULL, NULL, NULL);
	return nValLen;
}

BOOL CRegistryKey::GetKeyNames(CArray<CString,CString> *pStrArray) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	ULONG nKeyCount, nKeyNameLen, nLen; LPTSTR pszKeyNameBuf = NULL; ULONG i = 0; LONG nRet; CString szName;

	// Get information about the keys, and allocate a buffer for the names
	::RegQueryInfoKey(this->m_myKey, NULL, NULL, NULL, &nKeyCount, &nKeyNameLen, NULL, NULL, NULL, NULL, NULL, NULL);
	nKeyNameLen++; pszKeyNameBuf = (LPTSTR)::malloc(nKeyNameLen * sizeof(TCHAR));

	// Make sure the array is clean
	pStrArray->RemoveAll();

	// Collect the keys and add their name to the array
	for (i = 0;; i++) {
		nLen = nKeyNameLen;
		nRet = ::RegEnumKeyEx(this->m_myKey, i, pszKeyNameBuf, &nLen, NULL, NULL, NULL, NULL);
		if (nRet != ERROR_SUCCESS) break;
		szName = pszKeyNameBuf;
		pStrArray->Add(szName);
	}

	// Free up the name buffer
	::free(pszKeyNameBuf);
	return TRUE;
}

BOOL CRegistryKey::GetValueNames(CArray<CString,CString> *pStrArray) {
	ASSERT(this->IsRegKey(this->m_myKey));  // Seems to be an invalid key handle
	ULONG nValueCount, nValueNameLen, nLen; LPTSTR pszValueNameBuf = NULL; ULONG i = 0; LONG nRet; CString szName;

	// Get information about the keys, and allocate a buffer for the names
	::RegQueryInfoKey(this->m_myKey, NULL, NULL, NULL, NULL, NULL, NULL, &nValueCount, &nValueNameLen, NULL, NULL, NULL);
	nValueNameLen++; pszValueNameBuf = (LPTSTR)::malloc(nValueNameLen * sizeof(TCHAR));

	// Make sure the array is clean
	pStrArray->RemoveAll();

	// Collect the keys and add their name to the array
	for (i = 0; i < nValueCount; i++) {
		nLen = nValueNameLen;
		nRet = ::RegEnumKeyEx(this->m_myKey, i, pszValueNameBuf, &nLen, NULL, NULL, NULL, NULL);
		if (nRet != ERROR_SUCCESS) break;
		szName = pszValueNameBuf;
		pStrArray->Add(szName);
	}

	// Free up the name buffer
	::free(pszValueNameBuf);
	pszValueNameBuf = NULL;
	return TRUE;
}

// Copies a given sub-key to another registry key
BOOL CRegistryKey::CopyTo(CRegistryKey *pDestKey) {
	ASSERT(this->IsRegKey(this->m_myKey));		// Seems to be an invalid key handle
	ASSERT(pDestKey->IsRegKey(pDestKey->m_myKey));	// Bad key...
	return ::RegCopyKey(this->m_myKey, pDestKey->m_myKey);	
}
