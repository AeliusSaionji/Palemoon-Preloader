/////////////////////////////////////////////////////////////////////////////
// Options Dialog - PalemoonPreloaderDlg.cpp
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
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/) : CDialog(COptionsDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(COptionsDlg)
	m_szPath = _T("");
	m_bAutoFindFF = FALSE;
	m_bWarnOnUnload = FALSE;
	//}}AFX_DATA_INIT
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Text(pDX, IDC_PATH, m_szPath);
	DDX_Check(pDX, IDC_AUTO, m_bAutoFindFF);
	DDX_Check(pDX, IDC_WARN, m_bWarnOnUnload);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_AUTO, OnAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnBrowse() {

	BROWSEINFO bi; LPITEMIDLIST pidl;	// Browser for Folder structures
	LPTSTR pszPath;						// Retrieved path

	// Initialize the BrowseInfo structure
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = (TCHAR*)malloc(MAX_PATH * sizeof(TCHAR));
	bi.lpszTitle = _T("Palemoon Application Folder");
	bi.ulFlags = BIF_RETURNFSANCESTORS || BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	// Browse for a folder
	pidl = SHBrowseForFolder(&bi);

	// If a folder is selected, let update the Path text box
	if (pidl != NULL) {
		// Initialize the path buffer and get the path
		pszPath = (TCHAR*)malloc(MAX_PATH * sizeof(TCHAR));
		SHGetPathFromIDList(pidl, pszPath);
		
		// Set the path text box
		this->SetDlgItemText(IDC_PATH, pszPath);

		// Free resources
		CoTaskMemFree((void*)pidl);
		free(pszPath);
	}

	// Free resources
	free (bi.pszDisplayName);

}

void COptionsDlg::OnOK() {
	CString			// String Variables
		szFFExe,	// Palemoon.exe path
		szErrMsg;	// Error message resource
	HANDLE hFFExe;	// Palemoon.exe CreateFile handle

	// Check to see if the AutoFind is checked
	if (this->IsDlgButtonChecked(IDC_AUTO)) {
		CDialog::OnOK();
		return;
	}

	// Create a string with the palemoon.exe path
	this->GetDlgItemText(IDC_PATH, szFFExe);
	if (szFFExe[szFFExe.GetLength() - 1] == _T('\\')) szFFExe.TrimRight(_T('\\'));
	szFFExe += _T("\\palemoon.exe");

	// See if palemoon.exe exists in the path by opening it
	hFFExe = ::CreateFile(szFFExe, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFFExe == INVALID_HANDLE_VALUE) {
		// If this fails then the path is not good		
		szErrMsg.LoadString(IDS_OPTIONS_UNABLETOOPEN);
		szErrMsg += szFFExe;
		::ErrorMessage(this->m_hWnd, szErrMsg, ::GetLastError());
		return;
	}
	// We are done
	::CloseHandle(hFFExe);
	
	CDialog::OnOK();
}

void COptionsDlg::OnAuto() {
	CWnd *pControl;
	// Disable the path controls if autofind is checked
	if (this->IsDlgButtonChecked(IDC_AUTO)) {
		pControl = this->GetDlgItem(IDC_PATH);
		pControl->EnableWindow(FALSE);
		pControl = this->GetDlgItem(IDC_BROWSE);
		pControl->EnableWindow(FALSE);
		pControl = this->GetDlgItem(IDC_STATIC_PATH);
		pControl->EnableWindow(FALSE);
	} else {
		pControl = this->GetDlgItem(IDC_PATH);
		pControl->EnableWindow();
		pControl = this->GetDlgItem(IDC_BROWSE);
		pControl->EnableWindow();
		pControl = this->GetDlgItem(IDC_STATIC_PATH);
		pControl->EnableWindow();
	}
}

BOOL COptionsDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	CWnd *pControl;

	// See if we can autofind Palemoon
	if (::GetLatestPalemoonInstallDir(NULL)) {
		pControl = this->GetDlgItem(IDC_AUTO);
		pControl->EnableWindow();
	// Otherwise, disable the option to do so
	} else {
		pControl = this->GetDlgItem(IDC_AUTO);
		pControl->EnableWindow(FALSE);
	}

	// Disable the path controls if autofind is checked
	if (this->IsDlgButtonChecked(IDC_AUTO)) {
		pControl = this->GetDlgItem(IDC_PATH);
		pControl->EnableWindow(FALSE);
		pControl = this->GetDlgItem(IDC_BROWSE);
		pControl->EnableWindow(FALSE);
		pControl = this->GetDlgItem(IDC_STATIC_PATH);
		pControl->EnableWindow(FALSE);
	} else {
		pControl = this->GetDlgItem(IDC_PATH);
		pControl->EnableWindow();
		pControl = this->GetDlgItem(IDC_BROWSE);
		pControl->EnableWindow();
		pControl = this->GetDlgItem(IDC_STATIC_PATH);
		pControl->EnableWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
