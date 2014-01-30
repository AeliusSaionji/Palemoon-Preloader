// RegistryKey.h: interface for the CRegistryKey class.
//////////////////////////////////////////////////////////////////////
//
//   Copyright (C)2004 6XGate Systems, Inc.
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

#if !defined(_REGISTRYKEY_H_)
#define _REGISTRYKEY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_CLASS_EXPORT CRegistryKey
{
	friend class CRegistry;
public:
	BOOL CopyTo(CRegistryKey *pDestKey);
	BOOL GetValueNames(CArray<CString,CString> *pStrArray);
	BOOL GetKeyNames(CArray<CString,CString> *pStrArray);
	CRegistryKey();
	BOOL IsRegKey(HKEY hKey);
	virtual ~CRegistryKey();
	CRegistryKey *OpenKey(LPCTSTR lpSubKey);
	CRegistryKey *CreateKey (LPCTSTR lpSubKey);
	LONG SetValue(LPCTSTR lpValueName, DWORD dwType, const BYTE* lpData, DWORD cbData);
	LONG SetBinaryValue(LPCTSTR lpValueName, const BYTE* lpData, DWORD cbData);
	LONG SetIntegerValue(LPCTSTR lpValueName, DWORD dwData);
	LONG SetStringValue(LPCTSTR lpValueName, LPCTSTR lpString);
	LONG SetExpandStringValue(LPCTSTR lpValueName, LPCTSTR lpString);
	LONG DeleteValue(LPCTSTR lpValueName);
	LONG DeleteKey (LPCTSTR lpSubKey);
	LONG GetValue(LPCTSTR lpValueName, CRegistryValue &rValue);
	LONG GetStringValue(LPCTSTR lpValueName, CString *rString);
	LONG GetIntegerValue(LPCTSTR lpValueName, LPDWORD lpdwValue);
	LONG QueryMaxKeyNameLen();
	LONG QueryMaxValueLen();
	LONG QueryMaxValueNameLen();
protected:
	HKEY m_myKey;
};

#endif // !defined(_REGISTRYKEY_H_)
