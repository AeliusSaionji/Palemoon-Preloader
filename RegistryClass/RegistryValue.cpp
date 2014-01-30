// RegistryValue.cpp: implementation of the CRegistryValue class.
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

CRegistryValue::CRegistryValue() { this->m_bSet=FALSE; }

CRegistryValue::~CRegistryValue() {
	if (this->m_bSet=TRUE) free(this->m_lpData);
}

int CRegistryValue::SetValue(LPBYTE lpData, DWORD dwDataSize, ULONG nDataType) {
	this->m_dwSize = dwDataSize;
	this->m_lpData = (LPBYTE)malloc(dwDataSize);
	memcpy (this->m_lpData, lpData, dwDataSize);
	this->m_nType = nDataType;
	this->m_bSet = TRUE;
	return 0;
}

LPBYTE CRegistryValue::GetData() {
	ASSERT(this->m_bSet);
	return this->m_lpData;
}

DWORD CRegistryValue::GetLength() {
	ASSERT(this->m_bSet);
	return this->m_dwSize;
}

ULONG CRegistryValue::Type() {
	ASSERT(this->m_bSet);
	return this->m_nType;
}
