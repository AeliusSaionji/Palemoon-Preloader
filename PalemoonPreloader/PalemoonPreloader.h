/////////////////////////////////////////////////////////////////////////////
// Application Header - PalemoonPreloader.h
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

#if !defined(AFX_FIREFOXPRELOADER_H__CE030BEA_28E5_488F_9A5D_987F0C37704B__INCLUDED_)
#define AFX_FIREFOXPRELOADER_H__CE030BEA_28E5_488F_9A5D_987F0C37704B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPalemoonPreloaderApp:

class CPalemoonPreloaderApp : public CWinApp {
public:
	CPalemoonPreloaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPalemoonPreloaderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPalemoonPreloaderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREFOXPRELOADER_H__CE030BEA_28E5_488F_9A5D_987F0C37704B__INCLUDED_)
