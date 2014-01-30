// RegistryValue.h: interface for the CRegistryValue class.
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

#if !defined(_REGISTRYVALUE_H_)
#define _REGISTRYVALUE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_CLASS_EXPORT CRegistryValue
{
	friend class CRegistryKey;
public:
	ULONG Type();
	DWORD GetLength();
	LPBYTE GetData();
	CRegistryValue();
	virtual ~CRegistryValue();

protected:
	SetValue(LPBYTE lpData, DWORD dwDataSize, ULONG nDataType);
	DWORD m_dwSize;
	LPBYTE m_lpData;
	ULONG m_nType;
	BOOL m_bSet;
};

#endif // !defined(_REGISTRYVALUE_H_)
