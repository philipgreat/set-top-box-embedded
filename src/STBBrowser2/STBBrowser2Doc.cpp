// STBBrowser2Doc.cpp : implementation of the CSTBBrowser2Doc class
//

#include "stdafx.h"
#include "STBBrowser2.h"

#include "STBBrowser2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2Doc

IMPLEMENT_DYNCREATE(CSTBBrowser2Doc, CDocument)

BEGIN_MESSAGE_MAP(CSTBBrowser2Doc, CDocument)
	//{{AFX_MSG_MAP(CSTBBrowser2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2Doc construction/destruction

CSTBBrowser2Doc::CSTBBrowser2Doc()
{
	// TODO: add one-time construction code here

}

CSTBBrowser2Doc::~CSTBBrowser2Doc()
{
}

BOOL CSTBBrowser2Doc::OnNewDocument()
{
	

	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2Doc serialization

void CSTBBrowser2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2Doc diagnostics

#ifdef _DEBUG
void CSTBBrowser2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSTBBrowser2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2Doc commands

BOOL CSTBBrowser2Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{

	return TRUE;
}



void CSTBBrowser2Doc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument::SetTitle("browser");
}
