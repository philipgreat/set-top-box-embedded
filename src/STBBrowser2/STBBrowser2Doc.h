// STBBrowser2Doc.h : interface of the CSTBBrowser2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STBBROWSER2DOC_H__35287FDC_4318_4B06_9EBD_7A2C7DFDEE5A__INCLUDED_)
#define AFX_STBBROWSER2DOC_H__35287FDC_4318_4B06_9EBD_7A2C7DFDEE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSTBBrowser2Doc : public CDocument
{
private:


protected: // create from serialization only
	CSTBBrowser2Doc();
	DECLARE_DYNCREATE(CSTBBrowser2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTBBrowser2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CSTBBrowser2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSTBBrowser2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STBBROWSER2DOC_H__35287FDC_4318_4B06_9EBD_7A2C7DFDEE5A__INCLUDED_)
