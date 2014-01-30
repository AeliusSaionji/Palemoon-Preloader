/////////////////////////////////////////////////////////////////////////////
// Standard Header (Precompiled) StdAfx.h
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

#if !defined(AFX_STDAFX_H__A7975398_308E_4C82_A738_99D63A713EE8__INCLUDED_)
#define AFX_STDAFX_H__A7975398_308E_4C82_A738_99D63A713EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _WIN32_IE		0x0000	// We don't want any IE-specific functionality, this is for Palemoon.
#define _WIN32_WINNT	0x0501	// We don't want any 2000 or greater functionality, this is for older machines.

// MFC Headers
#include <afxwin.h>         // MFC core and standard components
#include <afxmt.h>			// MFC mutex objects

// Misc Headers
#include <shlobj.h>			// NT4.0/95 Shell Objects
#include <strsafe.h>		// Safe String Handling Functions
#include <RegistryClass.h>	// 6XGate RegistryClass Windows Registry Access Library

// Local Headers
#include "helpers.h"		// Internal Helper Functions
#include "processes.h"		// Process Watch Functions

#ifdef _DEBUG
// Debugging Mutex
#define APP_MUTEX _T("{37A5E6AA-23C8-46fd-AA50-2B3C314A45DE}")
#else
// Release Mutex
#define APP_MUTEX _T("{D5879DE9-8D55-47a1-B8D3-9D7C099002FD}")
#endif

#define WAIT_MUTEX _T("{E9178615-2CC7-4c1c-841A-646FEB9C7F1E}")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A7975398_308E_4C82_A738_99D63A713EE8__INCLUDED_)
