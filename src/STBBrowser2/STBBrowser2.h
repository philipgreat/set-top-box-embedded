// STBBrowser2.h : main header file for the STBBROWSER2 application
//

#if !defined(AFX_STBBROWSER2_H__6F3D371C_2597_4143_BB95_B486387AA180__INCLUDED_)
#define AFX_STBBROWSER2_H__6F3D371C_2597_4143_BB95_B486387AA180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2App:
// See STBBrowser2.cpp for the implementation of this class
//

class CSTBBrowser2App : public CWinApp
{

private:
	int mode ;
	//char commandLine[1024];
	char commandLine[1024];
public:
	BOOL IsNetworkedTVMode();
	int GetApplicationMode()const;
	//char * GetCommandLine() const;
	char * GetCommandLine()const;
	CSTBBrowser2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTBBrowser2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSTBBrowser2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STBBROWSER2_H__6F3D371C_2597_4143_BB95_B486387AA180__INCLUDED_)
