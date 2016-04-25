// StreamProcessBar.cpp: implementation of the CStreamProcessBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StreamProcessBar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStreamProcessBar::CStreamProcessBar() : procBar(NULL)
{

}

CStreamProcessBar::~CStreamProcessBar()
{
	if(NULL!=procBar) CloseHandle(procBar);
}

int CStreamProcessBar::CreateProcessBar(HINSTANCE instance,HWND parent)
{
    RECT            _rcProgress;

	_rcProgress.left = 5;
	_rcProgress.right = _rcProgress.left +400;
	_rcProgress.top = 5;
	_rcProgress.bottom = _rcProgress.top  + 35;

	procBar=CreateWindowEx(
		WS_EX_DLGMODALFRAME|WS_EX_CLIENTEDGE, PROGRESS_CLASS, NULL,
		WS_CHILD|PBS_SMOOTH|WS_BORDER|WS_OVERLAPPED,
		_rcProgress.left, _rcProgress.top, _rcProgress.right-_rcProgress.left, _rcProgress.bottom-_rcProgress.top,
		parent, 
		NULL, NULL, NULL);

	RECT rect;
	int scy=GetSystemMetrics (SM_CYSCREEN);
	int scx=GetSystemMetrics (SM_CXSCREEN);
	::GetWindowRect(procBar,&rect);
	int posx=scx/2-(rect.right-rect.left)/2;
	int posy=scy/2-(rect.bottom-rect.top)/2;
	showX  = posx;
	showY  = posy;

	return 0;
}

int CStreamProcessBar::Show()
{
	SetWindowPos(this->procBar, 
			HWND_TOP, 
			showX,
			showY,
			0,0,
			SWP_NOSIZE|SWP_NOACTIVATE|SWP_SHOWWINDOW);

	//::SetForegroundWindow(this->procBar);
	return 0;
}

int CStreamProcessBar::Hide()
{
	SetWindowPos(this->procBar,NULL, 
				showX,showY,0,0,
				SWP_NOSIZE|SWP_NOACTIVATE|SWP_HIDEWINDOW);
	return 0;
}

void CStreamProcessBar::SetPosition(int pos)
{
	int lProg=pos;
	UINT nPos = (lProg == -1) ? 99 : ((lProg-1)%100);
/*
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(procBar, &ps);
	RECT rt;
	GetClientRect(procBar, &rt);
	//processBar.SetPosition(buffercounter++%100);
	const char *text="Loading.........";
	//DrawText(hdc, text, strlen(text), &rt, DT_CENTER);
		


	EndPaint(procBar, &ps);
*/
	//logger.Log(__FILE__,__LINE__,nPos);
    SendMessage(this->procBar, PBM_SETPOS, nPos, 0);
}
