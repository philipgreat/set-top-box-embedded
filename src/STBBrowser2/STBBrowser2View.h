// STBBrowser2View.h : interface of the CSTBBrowser2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STBBROWSER2VIEW_H__DE5CA4C8_C45A_4EAD_B74D_9EEFCDB28913__INCLUDED_)
#define AFX_STBBROWSER2VIEW_H__DE5CA4C8_C45A_4EAD_B74D_9EEFCDB28913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSTBBrowser2View : public CHtmlView
{
protected: // create from serialization only
	CSTBBrowser2View();
	DECLARE_DYNCREATE(CSTBBrowser2View)

// Attributes
public:
	CSTBBrowser2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSTBBrowser2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnDownloadComplete();
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetParentTitle();
	void ShowWindowInfo(HWND window);
	virtual ~CSTBBrowser2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSTBBrowser2View)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in STBBrowser2View.cpp
inline CSTBBrowser2Doc* CSTBBrowser2View::GetDocument()
   { return (CSTBBrowser2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STBBROWSER2VIEW_H__DE5CA4C8_C45A_4EAD_B74D_9EEFCDB28913__INCLUDED_)
