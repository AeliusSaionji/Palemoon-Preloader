/////////////////////////////////////////////////////////////////////////////
// Default Dialog (primary message handler) - DefaultDlg.cpp
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
#include "PalemoonPreloader.h"
#include "OptionsDlg.h"
#include "DefaultDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg dialog

CDefaultDlg::CDefaultDlg(CWnd* pParent /*=NULL*/) : CDialog(CDefaultDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CDefaultDlg)
	//}}AFX_DATA_INIT
	
	// Load the icons for the system tray
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon_Off = AfxGetApp()->LoadIcon(IDR_MAINFRAME_OFF);
	m_hIcon4bit = AfxGetApp()->LoadIcon(IDR_PREXPTRAY);
	m_hIcon4bit_Off = AfxGetApp()->LoadIcon(IDR_PREXPTRAY_OFF);
	
	// Initialize the settings variables
	this->p_nTimerInt = 0;
	this->p_bAutoFindFF = TRUE;
	this->p_bWarnOnUnloads = TRUE;
	this->p_bUserLock = FALSE;
	this->p_szPalemoonPath.Empty();
	this->p_szProfilePath.Empty();
}


void CDefaultDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefaultDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefaultDlg, CDialog)
	//{{AFX_MSG_MAP(CDefaultDlg)
	ON_COMMAND(ID_CONTEXTMENU_OPENMYHOMEPAGE, OnContextmenuOpenmyhomepage)
	ON_COMMAND(ID_CONTEXTMENU_PRELOADEROPTIONS, OnContextmenuPreloaderoptions)
	ON_COMMAND(ID_CONTEXTMENU_UNLOADFIREFOXPRELOADER, OnContextmenuUnloadpalemoonpreloader)
	ON_COMMAND(ID_CONTEXTMENU_INTERNETOPTIONS, OnContextmenuInternetoptions)
	ON_COMMAND(ID_CONTEXTMENU_ABOUTFIREFOXPRELOADER, OnContextmenuAboutpalemoonpreloader)
	ON_COMMAND(ID_CONTEXTMENU_UNLOADFIREFOX, OnContextmenuUnloadpalemoon)
	ON_COMMAND(ID_CONTEXTMENU_RELOADFIREFOX, OnContextmenuReloadpalemoon)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg message handlers

// Load Palemoon if it is not loaded
void CDefaultDlg::OnTimer(UINT nIDEvent) { if (nIDEvent == 1) this->PreloadFF(); CDialog::OnTimer(nIDEvent); }

// Prevents the dialog from closing other than with EndDialog
void CDefaultDlg::OnClose() { this->ShowWindow(SW_HIDE); }
void CDefaultDlg::OnOK() { this->ShowWindow(SW_HIDE); }
void CDefaultDlg::OnCancel() { this->ShowWindow(SW_HIDE); }

BOOL CDefaultDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	CString				// Strings
		szMessage,		// MessageBox message resources
		szTitle,		// MessageBox title resources
		szLPath;		// This is where autofind will save the path it finds

	// Initialize Registry Access
	CRegistryKey *softKey = this->p_cReg.KeyCurrentUser()->CreateKey(_T("SOFTWARE\\6XGate Incorporated\\PalemoonPreload"));
	::OutputDebugString(_T("\r\nLoading Settings...\r\n"));
	
	// Load the timer configuration, save and use the default if not set
	softKey->GetIntegerValue(_T("PollInterval"), (ULONG*)&(this->p_nTimerInt));
	if (this->p_nTimerInt == 0) {
		::OutputDebugString(_T("Default timer Interval\r\n"));
		this->p_nTimerInt = 5000;
		softKey->SetIntegerValue(_T("PollInterval"), this->p_nTimerInt);
	}
	
	// Load the Warning configuration, save and use the default it not set
	if (softKey->GetIntegerValue(_T("WarnOnUnloads"), (ULONG*)&(this->p_bWarnOnUnloads)) != ERROR_SUCCESS)
		softKey->SetIntegerValue(_T("WarnOnUnloads"), this->p_bWarnOnUnloads);

	// Load the AutoFind configuration, then get Palemoon's path if AutoFind is enabled
	softKey->GetIntegerValue(_T("AutoFind"), (ULONG*)&(this->p_bAutoFindFF));
	if (this->p_bAutoFindFF && ::GetLatestPalemoonInstallDir(&szLPath)) {
		::OutputDebugString(_T("Using AutoFind\r\n"));

		// Remove the saved path since AutoFind found Palemoon's path
		softKey->DeleteValue(_T("Path"));
		this->p_szPalemoonPath = szLPath;		
		softKey->SetIntegerValue(_T("AutoFind"), TRUE);

	// If AutoFind is not enabled, or the path couldn't be found, use the manually entered path
	} else {
		::OutputDebugString(_T("Unable to use AutoFind, trying manually\r\n"));

		this->p_bAutoFindFF = FALSE;
		softKey->SetIntegerValue(_T("AutoFind"), FALSE);
		softKey->GetStringValue(_T("Path"), &(this->p_szPalemoonPath));
	}

	// If the path was not found by the manual setting or automatically, ask the user for it
	if (this->p_szPalemoonPath.IsEmpty()) {
		::OutputDebugString(_T("We didn't get the path, lets ask the user for on\r\n"));
		
		this->p_bTimer = FALSE;
		szMessage.LoadString(IDS_ENTERPATH); szTitle.LoadString(IDS_TRAYTIP);
		this->MessageBox (szMessage, szTitle, MB_OK);
		
		// Display the Options dialog box to ask the user for the path, or let the user enable AutoFind
		if (this->ShowPreloaderOptionsDlg() != IDOK) {
			::OutputDebugString(_T("The user cancelled\r\n"));
			szTitle.LoadString(IDS_ERROR_TITLE);
			szMessage.LoadString(IDS_NEEDPATH);

			// The user didn't enter the path, display a warning and end the program
			this->MessageBox (szMessage, szTitle, MB_OK);
			delete softKey;					// Free the key
			this->EndDialog(IDCANCEL);		// End the dialog
			return TRUE;					// And end the funcion
		}
	}

	// If the current profile directory can be found, then enable to parent.lock watcher code
	this->p_bUserLock = ::GetCurrentPalemoonProfile(&(this->p_szProfilePath));

	// Show the tray icon, free the key, and load Palemoon
	this->ShowTrayIcon();
	delete softKey;
	this->PreloadFF();

	// Set the timer
	this->SetTimer(1, this->p_nTimerInt, NULL);
	this->p_bTimer = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDefaultDlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) {
    // Makes the window inivisible on startup (since this window is never shown)
    lpwndpos->flags &= ~SWP_SHOWWINDOW;

	CDialog::OnWindowPosChanging(lpwndpos);
}

LRESULT CDefaultDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
	// Handle tray notifications
	if(message == AM_TRAYNOTIFY) {
		if (wParam == 5000) {
			switch (lParam){
			// Show the tray icon's context menu when right-clicked
			case WM_RBUTTONUP:
				HMENU hm; POINT p;
				hm = this->GetMenu()->GetSubMenu(0)->m_hMenu;
				::GetCursorPos (&p);
				this->SetForegroundWindow();
				::SetMenuDefaultItem(hm, 0, TRUE);
				::TrackPopupMenuEx (hm, TPM_LEFTALIGN|TPM_RIGHTBUTTON, p.x, p.y, this->m_hWnd, NULL);
				this->PostMessage(WM_NULL, 0, 0);
				break;
			// Open a new Palemoon window with the users homepage when double-clicked
			case WM_LBUTTONDBLCLK:
				this->OnContextmenuOpenmyhomepage();
				break;
			}
		}
	}
	// Let MFC handle the rest
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDefaultDlg::OnDestroy()  {
	// Remove the tray icon and destroy the dialog
	this->ShowTrayIcon(FALSE);	
	CDialog::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg tray menu handlers

// Show the Preloader dialogs
void CDefaultDlg::OnContextmenuPreloaderoptions() { this->ShowPreloaderOptionsDlg(); }				// Options
void CDefaultDlg::OnContextmenuAboutpalemoonpreloader() { CAboutDlg dlgAbout; dlgAbout.DoModal(); }	// About...

void CDefaultDlg::OnContextmenuOpenmyhomepage() {
	CString szFF;								// Palemoon.exe path and command-line
	STARTUPINFO si; PROCESS_INFORMATION pi;		// Create process structures

	// Set the path to palemoon.exe so that it will open a new window with the user's homepage
	szFF = this->p_szPalemoonPath;
	szFF += _T("\\palemoon.exe");
	
	// Initialize the structures
	::ZeroMemory(&si, sizeof(STARTUPINFO));
	::ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = 0;

	// Load a new Palemoon with the user's homepage
	::CreateProcess(NULL, szFF.GetBuffer(szFF.GetLength()), NULL, NULL, FALSE, 0, NULL, this->p_szPalemoonPath, &si, &pi);
}

void CDefaultDlg::OnContextmenuInternetoptions() {
	CString szFF;								// Palemoon.exe path and command-line
	STARTUPINFO si; PROCESS_INFORMATION pi;		// CreateProcess structures

	// Set the path to palemoon.exe so that it will open the Palemoon Options dialog
	szFF = this->p_szPalemoonPath;
	szFF += _T("\\palemoon.exe -chrome \"chrome://browser/content/pref/pref.xul\"");
	
	// Initialize the structures
	::ZeroMemory(&si, sizeof(STARTUPINFO));
	::ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = 0;

	// Load the Palemoon Options dialog
	::CreateProcess(NULL, szFF.GetBuffer(szFF.GetLength()), NULL, NULL, FALSE, 0, NULL, this->p_szPalemoonPath, &si, &pi);
}

void CDefaultDlg::OnContextmenuReloadpalemoon() {
	CString			// String Variables
		szMessage,	// MessageBox message resources
		szTitle;	// MessageBox title resources

	// Only unload Palemoon if the Preloader is active
	if (this->p_bTimer) {
		if (this->p_bWarnOnUnloads) {
			// Warn the user
			::OutputDebugString(_T("Warning the user that we will unload Palemoon\r\n"));
			szTitle.LoadString(IDS_WARN_TITLE);
			szMessage.LoadString(IDS_WARN_RELOAD);
			if (this->MessageBox(szMessage, szTitle, MB_YESNO | MB_ICONQUESTION) == IDNO) return;
		}
		
		// Kill the timer so it doesn't keep trying to start Palemoon, restart it when Palemoon is loaded
		if (this->p_bTimer) this->KillTimer(1);
		this->UnloadFF();
	}
	this->PreloadFF();
	this->SetTimer(1, this->p_nTimerInt, NULL);
	this->p_bTimer = TRUE;
	this->GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_CONTEXTMENU_UNLOADFIREFOX, MF_BYCOMMAND | MF_ENABLED);
	this->ChangeTrayIconState(TRUE);
}

void CDefaultDlg::OnContextmenuUnloadpalemoon() {
	CString			// String Variables
		szMessage,	// MessageBox message resources
		szTitle;	// MessageBox title resources

	if (this->p_bWarnOnUnloads) {
		// Warn the user
		::OutputDebugString(_T("Warning the user that we will unload Palemoon\r\n"));
		szTitle.LoadString(IDS_WARN_TITLE);
		szMessage.LoadString(IDS_WARN_UNLOAD);
		if (this->MessageBox(szMessage, szTitle, MB_YESNO | MB_ICONQUESTION) == IDNO) return;
	}
	// Kill the time and unload Palemoon
	if (this->p_bTimer) {
		this->KillTimer(1);
		this->p_bTimer = FALSE;
	}
	this->UnloadFF();
	this->GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_CONTEXTMENU_UNLOADFIREFOX, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	this->ChangeTrayIconState(FALSE);
}

void CDefaultDlg::OnContextmenuUnloadpalemoonpreloader() {
	CString			// String Variables
		szMessage,	// MessageBox message resources
		szTitle;	// MessageBox title resources

	// Only unload Palemoon if the Preloader was active
	if (this->p_bTimer) {
		if (this->p_bWarnOnUnloads) {
			// Warn the user
			::OutputDebugString(_T("Warning the user that we will unload Palemoon\r\n"));
			szTitle.LoadString(IDS_WARN_TITLE);
			szMessage.LoadString(IDS_WARN_UNLOADPRELOADER);
			if (this->MessageBox(szMessage, szTitle, MB_YESNO | MB_ICONQUESTION) == IDNO) return;
		}

		// Unload the hidden Palemoon and end the program
		this->UnloadFF();
	}
	this->EndDialog(IDCANCEL);
}

/////////////////////////////////////////////////////////////////////////////
// CDefaultDlg helper member functions

int CDefaultDlg::ShowPreloaderOptionsDlg() {
	COptionsDlg dlg(this);	// Set the options dialog's parent
	CString szLPath;		// This is where autofind will save the path it finds
	CRegistryKey *softKey = this->p_cReg.KeyCurrentUser()->CreateKey(_T("SOFTWARE\\6XGate Incorporated\\PalemoonPreload"));

	// Initialize the dialog
	dlg.m_szPath = this->p_szPalemoonPath;			// Current Palemoon Path
	dlg.m_bAutoFindFF = this->p_bAutoFindFF;		// Do we AutoFind Palemoon?
	dlg.m_bWarnOnUnload = this->p_bWarnOnUnloads;	// Do we warn the user about unloading Palemoon?
	
	// Show the dialog
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		// If the user enables AutoFind, try to find Palemoon automaticly
		if (dlg.m_bAutoFindFF && ::GetLatestPalemoonInstallDir(&szLPath)) {

			// Remove the saved path since AutoFind found Palemoon's path
			softKey->DeleteValue(_T("Path"));
			this->p_bAutoFindFF = TRUE;
			this->p_szPalemoonPath = szLPath;
			softKey->SetIntegerValue(_T("AutoFind"), TRUE);
			::OutputDebugString(_T("Using AutoFind Path\r\n"));

		// If the user manually entered the path that was validated, use it
		} else {

			// Disable AutoFind and get the manually entered path
			this->p_bAutoFindFF = FALSE;
			this->p_szPalemoonPath = dlg.m_szPath;

			// Trim the \ off the path if it is present save the settings
			if (this->p_szPalemoonPath[this->p_szPalemoonPath.GetLength() - 1] == _T('\\')) this->p_szPalemoonPath.TrimRight(_T('\\'));
			softKey->SetStringValue(_T("Path"), this->p_szPalemoonPath);
			softKey->SetIntegerValue(_T("AutoFind"), FALSE);
			::OutputDebugString(_T("Using Manually Entered Path\r\n"));
		
		}

		// Get and save the warning settings
		this->p_bWarnOnUnloads = dlg.m_bWarnOnUnload;
		softKey->SetIntegerValue(_T("WarnOnUnloads"), this->p_bWarnOnUnloads);
		
		// Free the registry key
		delete softKey;
	}

	return nResponse;
}

BOOL CDefaultDlg::ShowTrayIcon(BOOL bShow /* = TRUE */) {
	CString szRes; NOTIFYICONDATA nd; OSVERSIONINFO vi;

	// Initialize the version and tray icon structures
	::ZeroMemory(&vi, sizeof(vi));
	::ZeroMemory(&nd, sizeof(nd));
	vi.dwOSVersionInfoSize = sizeof(vi);
	nd.cbSize = sizeof(nd);

	// Get the OS version
	// ::GetVersionEx(&vi); // depreciated so I'm just throwing it out until I can figure out what the new way to do this is
	
	// Use a the 16x16 4-bit icon on pre-XP systems, otherwise use the normal application icon
	nd.hIcon = this->m_hIcon;
	// if ((vi.dwMajorVersion < 5) || (vi.dwMinorVersion < 1)) nd.hIcon = this->m_hIcon4bit; //this is part of the getversionex
	
	// Set the rest of the tray icon structure
	nd.hWnd = this->m_hWnd;
	nd.uID = 5000;
	szRes.LoadString(IDS_TRAYTIP); ::StringCchCopy(nd.szTip, 64, szRes);
	nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.uCallbackMessage = AM_TRAYNOTIFY;

	// Add or remove the icon to the tray
	if (bShow) ::Shell_NotifyIcon (NIM_ADD, &nd); else Shell_NotifyIcon (NIM_DELETE, &nd);
	return TRUE;
}

// Triple-redundant method to see if Palemoon is running
BOOL CDefaultDlg::IsPalemoonRunning() {
	CString szLockFile;		// The path to the lock file
	
	// First, check for the PalemoonMessageWindow
	if (::FindWindow(_T("PalemoonMessageWindow"), NULL) != NULL) return TRUE;
	::OutputDebugString(_T("Didn't find PalemoonMessageWindow\r\n"));	

	// Next, check for the lock file
	if (this->p_bUserLock) {
		szLockFile = _T("\\parent.lock"); // For some reason, out of all the times I used CString, this time += failed to work...
		szLockFile.Insert(0, this->p_szProfilePath);
		if (::IsFileExists(szLockFile)) return TRUE;
		::OutputDebugString(_T("Didn't find parent.lock\r\n"));
	}

	// Finally, check to see if palemoon.exe is present in the currently running processes
	if (::IsProcessActive(_T("palemoon.exe"))) return TRUE;
	::OutputDebugString(_T("Didn't palemoon.exe process\r\n"));
	return FALSE;

	// If all three atemps to find Palemoon failled, it must not be loaded
	return FALSE;
}

BOOL CDefaultDlg::PreloadFF() {

	// Make sure that Palemoon is not running
	if (this->IsPalemoonRunning()) return TRUE;

	// Executing pre-loading thread
	AfxBeginThread(LoadAndWaitForPalemoon, (LPVOID)this, 0, 0, 0, NULL);
	return FALSE;
}

BOOL CDefaultDlg::UnloadFF() {
	HWND hFWnd = NULL;		// Found windows

	// Find and close Windows with the PalemoonMessageWindow class, this ensures proper termination of Palemoon with all of its
	// settings saved
	hFWnd = ::FindWindow(_T("PalemoonMessageWindow"), NULL);
	while (hFWnd != NULL) {
		::PostMessage(hFWnd, WM_QUIT, 0, 0);
		hFWnd = ::FindWindow(_T("PalemoonMessageWindow"), NULL);
	}

	return TRUE;
}

BOOL CDefaultDlg::ChangeTrayIconState(BOOL bEnabled /* = TRUE */)
{
	CString szRes; NOTIFYICONDATA nd; OSVERSIONINFO vi;

	// Initialize the version and tray icon structures
	::ZeroMemory(&vi, sizeof(vi));
	::ZeroMemory(&nd, sizeof(nd));
	vi.dwOSVersionInfoSize = sizeof(vi);
	nd.cbSize = sizeof(nd);

	// Get the OS version
	// ::GetVersionEx(&vi); //depreciated, what do?
	
	// Choose the on or off icon
	if (bEnabled) {
		// Use a the 16x16 4-bit icon on pre-XP systems, otherwise use the normal application icon
		nd.hIcon = this->m_hIcon;
		// if ((vi.dwMajorVersion < 5) || (vi.dwMinorVersion < 1)) nd.hIcon = this->m_hIcon4bit;
	} else {
		// Use a the 16x16 4-bit icon on pre-XP systems, otherwise use the normal application icon
		nd.hIcon = this->m_hIcon_Off;
		// if ((vi.dwMajorVersion < 5) || (vi.dwMinorVersion < 1)) nd.hIcon = this->m_hIcon4bit_Off;
	}

	// Set the rest of the tray icon structure
	nd.hWnd = this->m_hWnd;
	nd.uID = 5000;
	szRes.LoadString(IDS_TRAYTIP); ::StringCchCopy(nd.szTip, 64, szRes);
	nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.uCallbackMessage = AM_TRAYNOTIFY;

	// Add or remove the icon to the tray
	::Shell_NotifyIcon (NIM_MODIFY, &nd);
	return TRUE;
}
