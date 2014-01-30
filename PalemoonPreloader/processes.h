/////////////////////////////////////////////////////////////////////////////
// Process Watching Functions - processes.h
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
// This file contains system specific process watching functions
/////////////////////////////////////////////////////////////////////////////

#if !defined(_PROCESSES_H__F3CC43CD_464D_471e_AE3A_CE9F4AFA3EAD__INCLUDED_)
#define _PROCESSES_H__F3CC43CD_464D_471e_AE3A_CE9F4AFA3EAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// External
extern "C" {
	BOOL WINAPI InitializeProcessWatcher(void);
	BOOL WINAPI DeInitializeProcessWatcher(void);
	BOOL WINAPI IsProcessActive(LPCTSTR lpszModuleName);
}

#endif // !defined(_PROCESSES_H__F3CC43CD_464D_471e_AE3A_CE9F4AFA3EAD__INCLUDED_)
