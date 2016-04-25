// STBPlayer.cpp : Defines the entry point for the application.
//

#include	"stdafx.h"
#include	"resource.h"
#include	"ChannelMediaPlayer.h"
#include	"RemoteLogger.h"
#include	"ChannelPlayerOSD.h"
#include	"StreamProcessBar.h"
#include	"Overlay.h"
#include    "SystemTaskExecutor.h"
#define UNIQE_APP	"{A719E980-D193-11d5-B71A-0000B4C258C7}"
#define MAX_LOADSTRING 100
//static CRemoteLogger logger;
static CChannelPlayerOSD *playerOSD;
static CChannelMediaPlayer *player;

static int buffercounter=0;
static HWND ghWnd = 0;
static int state  = 0;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
static WCHAR    szFileName[2048];
// Foward declarations of functions included in this code module:
ATOM				STBPlayerRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_STBPLAYER, szWindowClass, MAX_LOADSTRING);
	STBPlayerRegisterClass(hInstance);
	//logger.Log("system started");
	
	// Perform application initialization:

	//::MessageBox(NULL,"goes here","sdf",MB_OK);	
	HANDLE  playerInstance;
	playerInstance = ::CreateMutex (NULL,FALSE,UNIQE_APP);
	if(GetLastError()==ERROR_ALREADY_EXISTS){
		
		HWND hWnd=FindWindow (NULL,"player");
		::ShowWindow(hWnd ,	SW_SHOWMAXIMIZED);
		::SetActiveWindow (hWnd);
		::SetForegroundWindow(hWnd);
		
		return FALSE;
	}
	
	A2W(szFileName,lpCmdLine);
	player = new CChannelMediaPlayer();
	playerOSD = new CChannelPlayerOSD();

	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}		
	CSystemTaskExecutor::DisableSystemHotKeys();
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_STBPLAYER);
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return msg.wParam;
}

DWORD __stdcall ThreadWork(void *pTask)
{	
	
	//player.WaitForCompletion();
	//::CoUninitialize();
	return 0;
}

void StartPlay()
{
	
	::CoInitialize(NULL);
	HRESULT hr = 0;
	
	//and wait for another active
	hr=player->RenderFile(szFileName,ghWnd);
	//printf("/before render file\n");
	if(FAILED(hr)){
		//wprintf(L"render file %s\n", szFileName);
		TCHAR msg[1024]={0}; 
		AMGetErrorText(hr,msg,1024);
		::MessageBox(ghWnd,msg,
			"发生播放错误!(Error when Playing the file!)",
			MB_OK|MB_ICONERROR);				
		exit(0);			
	}
}

//
//  FUNCTION: STBPlayerRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM STBPlayerRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX); 
	
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_STBPLAYER);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
	
	wcex.lpszMenuName	= (LPCSTR)IDC_STBPLAYER;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	
	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
int counter=0;
void HandleKeyDown(WPARAM wParam)
{
	WCHAR *msg=new WCHAR[1024];
	switch(wParam)
	{
	case 'H':		
		wsprintfW(msg,
		L"STBPlayer for Windows XPE Edtion\r\n\r\n\
		Build @ %s %s\r\n(C)2000-2006 Channel Soft(Beijing) ltd.",
		TEXT(__TIME__),TEXT(__DATE__));
		//PauseClip();		
		::MessageBoxW(NULL,msg, L"播放器信息",MB_OK|MB_ICONINFORMATION);
		
		break;
	case 'P':
		player->Pause();
		//PauseClip()r
		break;
		
	case 'S':
		//StopClip();
		break;		
	case 'M':
		playerOSD->ToggleShow();
		//playerOSD.Show();
		break;
		
		//ToggleMute();
		break;		
	case 'F':
		playerOSD->UpdatePercent(player->GetPosition()+10);
		playerOSD->ShowMenu();
		player->ForwardPercent(10);
		break;		
	case 'B':
		playerOSD->UpdatePercent(player->GetPosition()-10);
		playerOSD->ShowMenu();
		player->BackwardPercent(10);
		break;		
	case VK_UP:
		player->IncreaseVolume(5);
		playerOSD->ShowVolume(player->GetVolume());
		break;
	case VK_DOWN:
		player->DecreaseVolume(5);
		playerOSD->ShowVolume(player->GetVolume());
		break;
	case VK_LEFT:
		playerOSD->UpdatePercent(player->GetPosition()-1);
		playerOSD->ShowMenu();
		player->BackwardPercent(1);
		break;
	case VK_RIGHT:
		playerOSD->UpdatePercent(player->GetPosition()+1);
		playerOSD->ShowMenu();
		player->ForwardPercent(1);
		
		break;
		
	case VK_ESCAPE:
	case VK_F12:
	case 'Q':
	case 'X':
		//CloseClip();
		//player.Release();
		PostQuitMessage(0);
		::ShowCursor(TRUE);
		
		break;
	}
	delete[] msg;
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable
	HDC hDC = ::GetDC(NULL);
	int XSpan = GetDeviceCaps(hDC, HORZRES);
	int YSpan = GetDeviceCaps(hDC, VERTRES);
	
	::ReleaseDC(NULL, hDC);
	
   	hWnd =::CreateWindowEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,
		szWindowClass,"",WS_POPUP | WS_BORDER,
		0, 0, XSpan, YSpan,
		NULL,NULL,hInstance,NULL);
	
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	ShowWindow(hWnd, nCmdShow);
	
	//SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_ASYNCWINDOWPOS | SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow(hWnd);
	::SetTimer(hWnd,100,100,NULL);
	//::UpdateWindow(hWnd);
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	HRESULT hr = 0;
	ghWnd=hWnd;
	int percent = 0;
	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		case WM_SHOWWINDOW:
			break;
		case WM_TIMER:
			percent = player->GetPosition();
			playerOSD->UpdatePercent(percent);
			playerOSD->OnTimer();
			break;
		case WM_CREATE:
			playerOSD->ShowMenu("",0);
			::SetWindowText(hWnd,"player");
			StartPlay();
			break;
		case WM_ACTIVATE:
			break;			
		case WM_KEYDOWN:			
			HandleKeyDown(wParam);
			break;
		case WM_PAINT:
			RECT rt;
			hdc = BeginPaint(hWnd, &ps);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
			
		case WM_GRAPHNOTIFY:
			long evCode;
			player->PreProcGraphEvent(&evCode);
			if(evCode==14){
				playerOSD->Hide();
				//processBar.Hide();
				state=1;
			}		
			break;
		case WM_DESTROY:
			//player->Release();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
    player->NotifyOwnerMessage( hWnd, message, wParam, lParam);
	return 0;
}

