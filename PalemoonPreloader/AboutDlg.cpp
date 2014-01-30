/////////////////////////////////////////////////////////////////////////////
// About Application Dialog - AboutDlg.cpp
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

#include "stdafx.h"
#include "FileVersionInfo.h"
#include "PalemoonPreloader.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/) : CDialog(CAboutDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Initialize version class
	CFileVersionInfo fv; CString szRes;
	fv.Create();
	
	// Set the dialog title
	szRes = "About ";
	szRes += fv.GetProductName ();
	this->SetWindowText(szRes);

	// Get the application version
	szRes = fv.GetProductVersion();
	this->SetDlgItemText (IDC_VERSION, szRes);

	// Create the copyright line
	szRes = fv.GetLegalCopyright();
	szRes += _T(" ");
	szRes += fv.GetCompanyName();
	this->SetDlgItemText (IDC_COPYRIGHT, szRes);

	// Set the remaining controls text with the remaining version information
	this->SetDlgItemText (IDC_APPNAME, fv.GetProductName ());
	this->SetDlgItemText (IDC_DESCR, fv.GetFileDescription());

	return TRUE;  // return TRUE unless you set the focus to a control
}
