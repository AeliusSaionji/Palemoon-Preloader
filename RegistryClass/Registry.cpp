// Registry.cpp: implementation of the CRegistry class.
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

CRegistry::~CRegistry(){}
CRegistry::CRegistry() {
	this->m_keyClassRoot.m_myKey = HKEY_CLASSES_ROOT;	
	this->m_keyCurrentUser.m_myKey = HKEY_CURRENT_USER;	
	this->m_keyLocalMachine.m_myKey = HKEY_LOCAL_MACHINE;	
	this->m_keyUsers.m_myKey = HKEY_USERS;	
#ifndef _WIN32_WCE
	this->m_keyCurrentConfig.m_myKey = HKEY_CURRENT_CONFIG;	
	this->m_keyDynData.m_myKey = HKEY_DYN_DATA;
	this->m_keyPerformanceData.m_myKey = HKEY_PERFORMANCE_DATA;
#endif //_WIN32_WCE
}

// Preopened registry keys
CRegistryKey *CRegistry::KeyClassRoot() { return &(this->m_keyClassRoot); }
CRegistryKey *CRegistry::KeyCurrentUser() { return &(this->m_keyCurrentUser); }
CRegistryKey *CRegistry::KeyLocalMachine() { return &(this->m_keyLocalMachine); }
CRegistryKey *CRegistry::KeyUsers() { return &(this->m_keyUsers); }
#ifndef _WIN32_WCE
CRegistryKey *CRegistry::KeyCurrentConfig() { return &(this->m_keyCurrentConfig); }
CRegistryKey *CRegistry::KeyDynData() { return &(this->m_keyDynData); }
CRegistryKey *CRegistry::KeyPerformanceData() { return &(this->m_keyPerformanceData); }
#endif //_WIN32_WCE
