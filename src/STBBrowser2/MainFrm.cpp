// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "STBBrowser2.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_WM_CREATE()
ON_WM_GETMINMAXINFO()
	ON_WM_SHOWWINDOW()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	// TODO: add member initialization code here
	HDC hDC = ::GetDC(NULL);
	int XSpan = GetDeviceCaps(hDC, HORZRES);
	int YSpan = GetDeviceCaps(hDC, VERTRES);
	::ReleaseDC(NULL, hDC);
	
	// Calculates size of window elements
	int XBorder = GetSystemMetrics(SM_CXFRAME);
	int YCaption = GetSystemMetrics(SM_CYCAPTION);
	int YMenu = GetSystemMetrics(SM_CYMENU);
	int YBorder = GetSystemMetrics(SM_CYFRAME);
	
	// Calculates window origin and span for full screen mode
	CPoint Origin = CPoint(-XBorder, -YBorder - YCaption - YMenu);
	XSpan += 2 * XBorder, YSpan += 2 * YBorder + YMenu + YCaption;
	// Calculates full screen window rectangle
	m_rectFull = CRect(Origin, CSize(XSpan, YSpan));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//|WS_EX_TOPMOST
	lpCreateStruct->dwExStyle |=WS_EX_TOPMOST;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

		/*	
		if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
		{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
		}
		
		  if (!m_wndStatusBar.Create(this) ||
		  !m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
		  {
		  TRACE0("Failed to create status bar\n");
		  return -1;      // fail to create
		  }
		  
			// TODO: Delete these three lines if you don't want the toolbar to
			//  be dockable
			m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
			EnableDocking(CBRS_ALIGN_ANY);
			DockControlBar(&m_wndToolBar);
	*/
	//this->MoveWindow(0,0,1044,788,TRUE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style &= ~(LONG) FWS_ADDTOTITLE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMaxPosition = m_rectFull.TopLeft();
	lpMMI->ptMaxTrackSize = lpMMI->ptMaxSize = CPoint(m_rectFull.Size());
//	CMDIFrameWnd::OnGetMinMaxInfo(lpMMI);
//	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

bool CMainFrame::ToggleFullScreen()
{

  // Previous window status parameters
  static CRect rectNormal;
  static boolFull = FALSE, boolStatus, boolTool;

  // Checks SDI / MDI application
  if (IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
  {
    // MDI Application
    static nCmdShow;  // Previous child-window status
    CMDIChildWnd* pChild = ((CMDIFrameWnd*) this)->MDIGetActive();
    if (boolFull)
    {
      // Resets child window show status
      pChild->ShowWindow(nCmdShow);
    }
    else
    {
      // Gets child window show status
      WINDOWPLACEMENT WP;
      pChild->GetWindowPlacement(&WP);
      nCmdShow = WP.showCmd;
      
      // Maximizes child window
      pChild->ShowWindow(SW_SHOWMAXIMIZED);
    }
  }
  
  if (boolFull)
  {
    // Toggles from full screen to normal mode
    // Shows status bar and tool bar if they were visible
    if (boolStatus)
      m_wndStatusBar.ShowWindow(SW_SHOW);
  
    if (boolTool)
      m_wndToolBar.ShowWindow(SW_SHOW);

    RecalcLayout();
  }
  else
  {
    // Toggles from normal to full screen mode
    // Saves status bar and toolbar status and hides them
	  /*
    if (boolStatus = m_wndStatusBar.IsWindowVisible())
      m_wndStatusBar.ShowWindow(SW_HIDE);

    if (boolTool = m_wndToolBar.IsWindowVisible())
      m_wndToolBar.ShowWindow(SW_HIDE);
	*/

    RecalcLayout();
  
    // Saves current window position and size
    GetWindowRect(rectNormal);
  }

  // Shows window in full screen / normal mode
  MoveWindow(boolFull ? rectNormal : m_rectFull);
  
  // Toggles window status
  boolFull = !boolFull;
  return boolFull==TRUE;

}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	this->ToggleFullScreen();
	// TODO: Add your message handler code here
	
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	this->SendKeyToActiveView(WM_KEYUP,nChar);
	//CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//this->MessageBox("on key down");

	this->SendKeyToActiveView(WM_KEYDOWN,nChar);
	//CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMainFrame::SendKeyToActiveView(DWORD message,UINT key)
{
	CWnd *window = this->GetActiveView();
	if(NULL != window){
		window->PostMessage(message,key,0);
		return TRUE;
	}else{
		this->MessageBox("fail to get the active view!");
		return FALSE;
	}
	
}
void CMainFrame::OnUpdateFrameTitle(BOOL NaDa)
{
	//CString csAppName;
	//csAppName.Format(AFX_IDS_APP_TITLE);
	SetWindowText("browser");
}