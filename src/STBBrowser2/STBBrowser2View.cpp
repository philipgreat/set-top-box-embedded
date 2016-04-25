// STBBrowser2View.cpp : implementation of the CSTBBrowser2View class
//

#include "stdafx.h"
#include "STBBrowser2.h"

#include "STBBrowser2Doc.h"
#include "STBBrowser2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2View

IMPLEMENT_DYNCREATE(CSTBBrowser2View, CHtmlView)

BEGIN_MESSAGE_MAP(CSTBBrowser2View, CHtmlView)
	//{{AFX_MSG_MAP(CSTBBrowser2View)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2View construction/destruction
static char *prevURLFileName="prevURLFile.ini";
static void SaveCurrentURL(const char *urlstring)
{
	FILE *file;

	file=fopen(prevURLFileName,"wb");
	if(file!=NULL){
		fwrite(urlstring,strlen(urlstring)+1,1,file);	
	}
	fclose(file);
	
}
static void ReadPreviousURL(char *history,int max)
{
	FILE *file;
	file=fopen(prevURLFileName,"rb");
	if(file!=NULL){
		fread(history,1,max,file);	
	}
	fclose(file);
	
}
CSTBBrowser2View::CSTBBrowser2View()
{
	// TODO: add construction code here

}

CSTBBrowser2View::~CSTBBrowser2View()
{
}

BOOL CSTBBrowser2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2View drawing

void CSTBBrowser2View::OnDraw(CDC* pDC)
{
	CSTBBrowser2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CSTBBrowser2View::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	CSTBBrowser2Doc* pDoc = GetDocument();
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	CSTBBrowser2App *p=(CSTBBrowser2App *)::AfxGetApp();
	char *command = p->GetCommandLine();
	if(strncmp(command,"open-old-page",strlen("open-old-page"))==0
		&&p->IsNetworkedTVMode()){
		//open old page;
		char history[1024];
		ReadPreviousURL(history,1024);
		if(strncmp("http://",history,strlen("http://"))==0){
			Navigate2(history,NULL,NULL);
		}else{
			Navigate2(command,NULL,NULL);
		}
		
	}else{
		Navigate2(command,NULL,NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2View printing


/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2View diagnostics

#ifdef _DEBUG
void CSTBBrowser2View::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CSTBBrowser2View::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CSTBBrowser2Doc* CSTBBrowser2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSTBBrowser2Doc)));
	return (CSTBBrowser2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSTBBrowser2View message handlers

void CSTBBrowser2View::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel) 
{
	// TODO: Add your specialized code here and/or call the base class

	*Cancel=TRUE;
	/*		WCHAR* url = ((*pdparams).rgvarg)[5].pvarVal->bstrVal;*/
	CHtmlView::OnNewWindow2(ppDisp, Cancel);
}
static DWORD ExecuteFileEx(LPCTSTR startDirectory,LPCTSTR fileName,LPTSTR cmdLine)
{
	STARTUPINFO si;
	DWORD pid = 0;
    PROCESS_INFORMATION pi;
    char commandLine[2048];
	*commandLine=' ';
	strncpy(commandLine+1,cmdLine,2040);
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
	BOOL ret = CreateProcess(
		fileName, 
		commandLine, 
		NULL, 
		NULL, 
		FALSE, 
		0, 
		NULL, 
		startDirectory, 
		&si, 
		&pi);
	//WaitForSingleObject( pi.hProcess, INFINITE );
	return pi.dwProcessId;
}

void CSTBBrowser2View::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	// TODO: Add your specialized code here and/or call the base class
	const char *header="mms://";
	int len=strlen(header);
	//MessageBox(lpszURL,lpszURL,MB_OK);
	char fileURL[2048];
	*fileURL=' ';
	strncpy(fileURL+1,lpszURL,2046);
	if(0==strncmp(header,lpszURL,len)){
		ExecuteFileEx(".\\","stbplayer.exe",fileURL);
		*pbCancel  = TRUE;	
	}
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags,	lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}
static HWND GetLastChild(HWND hwndParent)
{
   HWND hwnd = hwndParent;
   while (TRUE) {
      HWND hwndChild = ::GetWindow(hwnd, GW_CHILD);
      if (hwndChild==NULL)
         return hwnd;
      hwnd = hwndChild;
   }
   return NULL;
}

void CSTBBrowser2View::OnDownloadComplete() 
{
	CHtmlView::OnDownloadComplete();
}

void CSTBBrowser2View::ShowWindowInfo(HWND window)
{
	WINDOWINFO windowinfo;
	char message[1024];
	::GetWindowInfo(window,&windowinfo);
	sprintf(message,"view handle = %8X",window);

	this->MessageBox(message);


}




static HWND window = NULL;
static bool isFirstRun=true;
void CSTBBrowser2View::OnNavigateComplete2(LPCTSTR strURL) 
{
	// TODO: Add your specialized code here and/or call the base class
	this->MoveWindow(0,0,1044,788);
	window=GetLastChild(this->m_hWnd);
	if(window){
		if(isFirstRun){
			::PostMessage(window,WM_KEYDOWN,39,0);
			isFirstRun = false;
			VK_DOWN;

		}
	}else{
		this->MessageBox("fail to get window=GetLastChild(this->m_hWnd);");
	}
	CSTBBrowser2App *p=(CSTBBrowser2App *)::AfxGetApp();
	if(p->IsNetworkedTVMode()){
		//this->MessageBox("save SaveCurrentURL(strURL);");
		SaveCurrentURL(strURL);	
	}
	CHtmlView::OnNavigateComplete2(strURL);
}

void CSTBBrowser2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//this->MessageBox("on key down");
	window=GetLastChild(this->m_hWnd);
	if(window){
		::SendMessage(window,WM_KEYDOWN,nChar,0);
	}else{
		this->MessageBox("fail to get window=GetLastChild(this->m_hWnd);");
	}

	CHtmlView::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CSTBBrowser2View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//this->MessageBox("keyup");
	
	CHtmlView::OnKeyUp(nChar, nRepCnt, nFlags);
}
