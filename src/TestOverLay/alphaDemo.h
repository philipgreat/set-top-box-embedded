// alphaDemo.h : main header file for the ALPHADEMO application
//

#if !defined(AFX_ALPHADEMO_H__E1969C0C_A78A_4730_8EC5_DBA324E5BF03__INCLUDED_)
#define AFX_ALPHADEMO_H__E1969C0C_A78A_4730_8EC5_DBA324E5BF03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlphaDemoApp:
// See alphaDemo.cpp for the implementation of this class
//

class CAlphaDemoApp : public CWinApp
{
public:
    CAlphaDemoApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAlphaDemoApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CAlphaDemoApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALPHADEMO_H__E1969C0C_A78A_4730_8EC5_DBA324E5BF03__INCLUDED_)
