// regclass.cpp : Defines the initialization routines for the DLL.
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
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE RegclassDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("RegistryClass DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(RegclassDLL, (HINSTANCE)hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(RegclassDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("RegistryClass DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(RegclassDLL);
	}
	return 1;   // ok
}
