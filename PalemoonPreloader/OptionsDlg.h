/////////////////////////////////////////////////////////////////////////////
// Options Dialog Header - PalemoonPreloaderDlg.h
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

#if !defined(AFX_FIREFOXPRELOADERDLG_H__0EDF26E3_31C0_4944_8A75_D92014E6EF2D__INCLUDED_)
#define AFX_FIREFOXPRELOADERDLG_H__0EDF26E3_31C0_4944_8A75_D92014E6EF2D__INCLUDED_

#include "PalemoonPreloader.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CDialog {
// Construction
public:
	COptionsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS };
	CString	m_szPath;
	BOOL	m_bAutoFindFF;
	BOOL	m_bWarnOnUnload;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRegistry p_cReg;			// Registry access
	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnBrowse();
	virtual void OnOK();
	afx_msg void OnAuto();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREFOXPRELOADERDLG_H__0EDF26E3_31C0_4944_8A75_D92014E6EF2D__INCLUDED_)
