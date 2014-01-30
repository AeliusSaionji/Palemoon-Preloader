// Registry Access Classes
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
#if !defined(_REGISTRYCLASS_H_)
#define _REGISTRYCLASS_H_

// Make sure that we have the MFC Collection Classes included
#include <afxtempl.h>

// Both UNICODE and ANSI Versions use the same headers
#include <Registry.h>

// Make sure the right lib file for RegistryClass
#ifndef _WIN32_WCE
// Our regular desktop version of Windows
#if !defined(_UNICODE)
#pragma comment(lib, "regclass.lib")	// ANSI version
#else // !defined(_UNICODE)
#pragma comment(lib, "regclassu.lib")	// UNICODE version
#endif // !defined(_UNICODE)

#else //_WIN32_WCE
// Our Windows CE/PocketPC
#pragma comment(lib, "regclass.lib")	// UNICODE version only

#endif //_WIN32_WCE

#endif // !defined(_REGISTRYCLASS_H_)
