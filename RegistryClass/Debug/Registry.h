// Registry.h: interface for the CRegistry class.
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

#if !defined(_REGISTRY_H_)
#define _REGISTRY_H_

#include <RegistryValue.h>
#include <RegistryKey.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CUSTOM_BIT		0x20000000
#define FACILITY_MASK	0x0FFF0000
#define ECODE_MASK		0x0000FFFF
#define SEVERITY_MASK	0xC0000000

#define FACILITY_CREG	0x0F0

// Can not convert the value to this type of data.
#define ERROR_CANNOT_CONVERT_VALUE	CUSTOM_BIT|(FACILITY_CREG<<16)|1L

class AFX_CLASS_EXPORT CRegistry
{
public:
	CRegistry();
	virtual ~CRegistry();
	// Functions to retrieve predefined key handles
	CRegistryKey *KeyClassRoot();
	CRegistryKey *KeyCurrentUser();
	CRegistryKey *KeyLocalMachine();
	CRegistryKey *KeyUsers();
#ifndef _WIN32_WCE
	CRegistryKey *KeyCurrentConfig();
	CRegistryKey *KeyDynData();
	CRegistryKey *KeyPerformanceData();
#endif //_WIN32_WCE

protected:
	// Predefined key handles
	CRegistryKey m_keyClassRoot;
	CRegistryKey m_keyCurrentUser;
	CRegistryKey m_keyLocalMachine;
	CRegistryKey m_keyUsers;
#ifndef _WIN32_WCE
	CRegistryKey m_keyCurrentConfig;
	CRegistryKey m_keyDynData;
	CRegistryKey m_keyPerformanceData;
#endif //_WIN32_WCE
};

#endif // !defined(_REGISTRY_H_)
