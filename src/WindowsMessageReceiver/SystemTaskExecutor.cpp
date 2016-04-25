// CSystemTaskExecutor.cpp: implementation of the CSystemTaskExecutor class.
//
//////////////////////////////////////////////////////////////////////

#include "SystemTaskExecutor.h"
#include <time.h>
#include <Mmsystem.h>
#include <Powrprof.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemTaskExecutor::CSystemTaskExecutor()
{
	
}

CSystemTaskExecutor::~CSystemTaskExecutor()
{

}


int CSystemTaskExecutor::SetSystemTime(int absoluteSecondsFrom1970)
{
	struct tm *t = NULL;
	long time=(const long)absoluteSecondsFrom1970;
	
	t = localtime(&time);
	
	SYSTEMTIME systemtime;
	systemtime.wYear	= 1900 + t->tm_year;
	systemtime.wMonth	= t->tm_mon;
	systemtime.wDay		= t->tm_mday;
	systemtime.wHour	= t->tm_hour;
	systemtime.wMinute	= t->tm_min;
	systemtime.wSecond	= t->tm_sec;
	systemtime.wMilliseconds	= 0;
	
	return ::SetSystemTime(&systemtime);

}

static BOOL SuspendSystem(){
	return SetSuspendState(TRUE, FALSE, FALSE);
}

/*
BOOLEAN SetSuspendState(
  BOOL Hibernate,
  BOOL ForceCritical,
  BOOL DisableWakeEvent
);

*/
int CSystemTaskExecutor::SleepPC()
{

	return printf("SleepPC");

}
static BOOL RestartSystem()
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	// Get a token for this process. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return( FALSE ); 
	
	// Get the LUID for the shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get the shutdown privilege for this process. 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
	
	if (GetLastError() != ERROR_SUCCESS) 
		return FALSE; 
	
	if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)) 
		return FALSE; 
	
	return TRUE;
}

static BOOL ShutdownSystem()
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	// Get a token for this process. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return( FALSE ); 
	
	// Get the LUID for the shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
        &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get the shutdown privilege for this process. 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
	
	if (GetLastError() != ERROR_SUCCESS) 
		return FALSE; 
	
	
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)) 
		return FALSE; 
	
	return TRUE;
}

int CSystemTaskExecutor::RestartPC()
{
	
	//return RestartSystem();
	return printf("RestartSystem");
}
/*
BOOL InitiateSystemShutdownEx(
LPTSTR lpMachineName,
LPTSTR lpMessage,
DWORD dwTimeout,
BOOL bForceAppsClosed,
BOOL bRebootAfterShutdown,
DWORD dwReason
);

*/

//reference http://www.rxiao.com/collection/csdn/C++Builder/536150.xml
static bool SetVolumeValue(HMIXER hmixer ,MIXERCONTROL *mxc, long volume)
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_UNSIGNED vol;vol.dwValue = volume;
	mxcd.hwndOwner = 0;
	mxcd.dwControlID = mxc->dwControlID;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.cbDetails = sizeof(vol);
	mxcd.paDetails = &vol;
	mxcd.cChannels = 1;
	if(mixerSetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER|MIXER_SETCONTROLDETAILSF_VALUE))
		return 0;
	return 1;
}


static bool GetVolumeControl(HMIXER hmixer ,long componentType,long ctrlType,MIXERCONTROL* mxc)
{
	MIXERLINECONTROLS mxlc;
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(mxl);
	mxl.dwComponentType = componentType;
	if(!mixerGetLineInfo((HMIXEROBJ)hmixer, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE))
	{
		mxlc.cbStruct = sizeof(mxlc);
		mxlc.dwLineID = mxl.dwLineID;
		mxlc.dwControlType = ctrlType;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = mxc;
		if(mixerGetLineControls((HMIXEROBJ)hmixer,&mxlc,MIXER_GETLINECONTROLSF_ONEBYTYPE))
			return 0;
		else
			return 1;
	}
	return 0;
}

static unsigned GetVolumeValue(HMIXER hmixer ,MIXERCONTROL *mxc)
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_UNSIGNED vol; vol.dwValue=0;
	mxcd.hwndOwner = 0;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.dwControlID = mxc->dwControlID;
	mxcd.cbDetails = sizeof(vol);
	mxcd.paDetails = &vol;
	mxcd.cChannels = 1;
	if(mixerGetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER|MIXER_GETCONTROLDETAILSF_VALUE))
		return -1;
	return vol.dwValue;
}


//---------------------------------------------------------------------------
static unsigned WINAPI GetVolume(int dev)//得到设备的音量dev=0主音量，1WAVE ,2MIDI ,3 LINE IN
{
	
	long device;unsigned rt=0;
	MIXERCONTROL volCtrl;
	HMIXER hmixer;
	switch (dev)
	{
    case 1:
		device=MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT; break;
    case 2:
		device=MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; break;
    case 3:
		//  device=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;  // cd 音量
		//  device=MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE; break;   //麦克风音量
		//  device=MIXERLINE_COMPONENTTYPE_SRC_LINE; break;         //PC 扬声器音量
		device=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;
		
    default:
		device=MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	}
	
	if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;
	if(!GetVolumeControl(hmixer,device,MIXERCONTROL_CONTROLTYPE_VOLUME,&volCtrl))
		return 0;
	rt=GetVolumeValue(hmixer,&volCtrl)*100/volCtrl.Bounds.lMaximum;
	mixerClose(hmixer);
	return rt;
	
}

static bool WINAPI SetVolume(long dev,long vol)//设置设备的音量
{
	// dev =0,1,2   分别表示主音量,波形,MIDI ,LINE IN
	// vol=0-100     表示音量的大小 , 设置与返回音量的值用的是百分比，即音量从0 - 100，而不是设备的绝对值
	// retrun false 表示设置音量的大小的操作不成功
	// retrun true  表示设置音量的大小的操作成功
	
	long device;
	bool rc=false;
	MIXERCONTROL volCtrl;
	HMIXER hmixer;
	switch (dev)
	{
	case 1:
		device=MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT; break;
	case 2:
		device=MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; break;
	case 3:
		device=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC; break;
		
	default:
		device=MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	}
	
	if(mixerOpen(&hmixer, 0, 0, 0, 0)) return 0;
	
	if(GetVolumeControl(hmixer,device,MIXERCONTROL_CONTROLTYPE_VOLUME,&volCtrl))
	{
		vol=vol*volCtrl.Bounds.lMaximum/100;
		if(SetVolumeValue(hmixer,&volCtrl,vol))
			rc=true;
	}
	mixerClose(hmixer);
	return rc;
}

int CSystemTaskExecutor::SetSystemVolume(int percent)
{
	return SetVolume(0,percent);
	//return 0;
	
}

int CSystemTaskExecutor::KillProcess(int processId)
{
	HANDLE hProcess;
	// Get the actual priority class.
	hProcess = OpenProcess (PROCESS_ALL_ACCESS,
		FALSE,
		processId);
	if(hProcess){
		::TerminateProcess(hProcess,0);
	}

	CloseHandle(hProcess);
	return 0;
}

BOOL CSystemTaskExecutor::SendWindowMessage(const char *windowName, DWORD messageId, DWORD lparam, DWORD wparam)
{
	HWND window=::FindWindow(NULL,windowName);
	
	//window = (struct HWND__ *)0x00F20156;
	//window = (struct HWND__ *)0x00820520;

	printf("windows = %8X\n",window);
	if(window!=NULL){
		return PostMessage(window,messageId,wparam,lparam);
	}
	
	return 0;
}

BOOL CSystemTaskExecutor::SendKeyCodeToWindow(const char *windowName, DWORD wparam)
{
	return  CSystemTaskExecutor::SendWindowMessage(windowName,WM_KEYDOWN,0,wparam);
	//CSystemTaskExecutor::SendWindowMessage(windowName,WM_CHAR,0,wparam);
	//CSystemTaskExecutor::SendWindowMessage(windowName,WM_KEYUP,0,wparam);
	
}

static DWORD ExecuteFileEx(LPCTSTR fileName,LPTSTR cmdLine)
{
	STARTUPINFO si;
	DWORD pid = 0;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	BOOL ret = CreateProcess(
		fileName, 
		cmdLine, 
		NULL, 
		NULL, 
		FALSE, 
		0, 
		NULL, 
		NULL, 
		&si, 
		&pi);
	//WaitForSingleObject( pi.hProcess, INFINITE );
	return pi.dwProcessId;
}

int CSystemTaskExecutor::ExecuteTask(char *ProgramFileName, char *param)
{
	
	return ExecuteFileEx(ProgramFileName,param);
}

int  CSystemTaskExecutor::SendKeyCodeToWindow(DWORD windowHandle, DWORD wparam)
{
	HWND window=(struct HWND__ *)windowHandle;
	if(window!=NULL){
		return PostMessage(window,WM_CHAR,wparam,0);
	}
	return 0;

}

int CSystemTaskExecutor::SendKeyUpToWindow(unsigned long windowHandle, DWORD message)
{
	HWND window=(struct HWND__ *)windowHandle;
	if(window!=NULL){
		PostMessage(window,WM_KEYDOWN,message,0);
		PostMessage(window,WM_KEYUP,message,0);
		//PostMessage(window,WM_KEYUP,message,0);
	}
	return 0;

}

int CSystemTaskExecutor::HideDesktop()
{
	int ret  = 0;
	HWND desktopwindow = ::FindWindowEx(0, 0, "Progman",NULL);
	ret = ::ShowWindow(desktopwindow,SW_HIDE);
	::CloseHandle(desktopwindow);

	HWND traywindow = ::FindWindowEx(0, 0, "Shell_TrayWnd",NULL);
	ret = ::ShowWindow(traywindow,SW_HIDE);
	::CloseHandle(traywindow);
	return ret;
}

int CSystemTaskExecutor::ShowDesktop()
{
	int ret  = 0;
	HWND desktopwindow = ::FindWindowEx(0, 0, "Progman",NULL);
	ret = ::ShowWindow(desktopwindow,SW_SHOW);
	::CloseHandle(desktopwindow);
	HWND traywindow = ::FindWindowEx(0, 0, "Shell_TrayWnd",NULL);
	ret = ::ShowWindow(traywindow,SW_SHOW);
	::CloseHandle(traywindow);

	return ret;
}


//static HWND windowsSet[1000];
//static int windowsCounter = 0 ; 
/*

BOOL CALLBACK WndFunc(HWND hwnd, LPARAM lParam)
{
	::PostMessage(hwnd, WM_CLOSE, 0, 0);
}

*/
static BOOL CALLBACK HideAWindow(HWND hwnd, LPARAM lParam)
{
	if(::IsWindowVisible(hwnd)&&::IsWindowEnabled(hwnd))
	{
		//windowsSet[windowsCounter]=hwnd;
		::ShowWindow(hwnd,SW_HIDE);
		//windowsCounter++;
	}
	return TRUE;
}
static BOOL CALLBACK ShowAWindow(HWND hwnd, LPARAM lParam)
{
	if(IsWindowEnabled(hwnd))
	{
		::ShowWindow(hwnd,SW_SHOW);
	}
	
	return TRUE;
}
int CSystemTaskExecutor::HideAllWindows()
{
	::EnumWindows(HideAWindow,0);
	return 0;
}
int CSystemTaskExecutor::ShowAllWindows()
{
	::EnumWindows(ShowAWindow,0);
	return 0;
}

int CSystemTaskExecutor::ForceShowAllWindows()
{
	::EnumWindows(ShowAWindow,0);
	return 0;
}
//禁止系统热键

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, 									  
									  WPARAM wParam, LPARAM lParam) {
	
	
	BOOL fEatKeystroke = FALSE;
	if(nCode == HC_ACTION) {
		
		switch (wParam) {
			
		case WM_KEYDOWN:  case WM_SYSKEYDOWN:
			
		case WM_KEYUP:    case WM_SYSKEYUP: 
			
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
			
			fEatKeystroke = 
				((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||
				
				((p->vkCode == VK_ESCAPE) && 
				
				((p->flags & LLKHF_ALTDOWN) != 0)) ||
				
				((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0));
			
			break;
			
		}
		
	}
	
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
	
}

static HHOOK hhkLowLevelKybd = NULL;
static BOOL isDisabled = FALSE;
//屏蔽掉系统键
int CSystemTaskExecutor::DisableSystemHotKeys()
{
	if(!isDisabled){
		HHOOK hhkLowLevelKybd  = SetWindowsHookEx(
			WH_KEYBOARD_LL,
			LowLevelKeyboardProc, 
			::GetModuleHandle(NULL), 
			0);
		isDisabled = TRUE;
		printf("diasable hot keys\n");
	}
	return (hhkLowLevelKybd!=NULL);
}

int CSystemTaskExecutor::EnableSystemHotKeys()
{

	if(isDisabled){
		isDisabled = FALSE;
		printf("enable hot keys\n");
		return UnhookWindowsHookEx(hhkLowLevelKybd)==TRUE;
	}else{
		//do nothing
		return 1;
	}
}





bool CSystemTaskExecutor::DisableTaskManager()
{

	return true;

}

bool CSystemTaskExecutor::EnableTaskManager()
{

	return true;

}
/*




// TestDisableHotKeys.cpp : Defines the entry point for the console application.
//

#define _WIN32_WINNT 0x0500

#include <windows.h>

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, 									  
									  WPARAM wParam, LPARAM lParam) {
	
	
	BOOL fEatKeystroke = FALSE;
	if(nCode == HC_ACTION) {
		
		switch (wParam) {
			
		case WM_KEYDOWN:  case WM_SYSKEYDOWN:
			
		case WM_KEYUP:    case WM_SYSKEYUP: 
			
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
			
			fEatKeystroke = 
				((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||
				
				((p->vkCode == VK_ESCAPE) && 
				
				((p->flags & LLKHF_ALTDOWN) != 0)) ||
				
				((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0));
			
			break;
			
		}
		
	}
	
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
	
}
int main(int argc, char* argv[])
{
	HHOOK hhkLowLevelKybd  = SetWindowsHookEx(WH_KEYBOARD_LL, 
		
		LowLevelKeyboardProc, ::GetModuleHandle(NULL), 0);
	//::GetModuleHandle()
	
	MessageBox(NULL, 
		
		TEXT("Alt+Esc, Ctrl+Esc, and Alt+Tab are now disabled.")
		
		TEXT("Click \"Ok\" to terminate this application and re-enable these keys."),
		
		TEXT("Disable Low-Level Keys"), MB_OK);
	
	UnhookWindowsHookEx(hhkLowLevelKybd);
	
	
	
	return(0);
}

/*





// TestDisableHotKeys2.cpp : Defines the entry point for the application.
//
#define _WIN32_WINNT 0x0500
#include "stdafx.h"



LRESULT CALLBACK LowLevelKeyboardProc(int nCode, 									  
									  WPARAM wParam, LPARAM lParam) {
	
	
	BOOL fEatKeystroke = FALSE;
	if(nCode == HC_ACTION) {
		
		switch (wParam) {
			
		case WM_KEYDOWN:  case WM_SYSKEYDOWN:
			
		case WM_KEYUP:    case WM_SYSKEYUP: 
			
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
			
			fEatKeystroke = 
				((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||
				
				((p->vkCode == VK_ESCAPE) && 
				
				((p->flags & LLKHF_ALTDOWN) != 0)) ||
				
				((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0));
			
			break;
			
		}
		
	}
	
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
	
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	HHOOK hhkLowLevelKybd  = SetWindowsHookEx(WH_KEYBOARD_LL, 
		
		LowLevelKeyboardProc, ::GetModuleHandle(NULL), 0);
	//::GetModuleHandle()
	
	MessageBox(NULL, 
		
		TEXT("Alt+Esc, Ctrl+Esc, and Alt+Tab are now disabled.")
		
		TEXT("Click \"Ok\" to terminate this application and re-enable these keys."),
		
		TEXT("Disable Low-Level Keys"), MB_OK);
	
	UnhookWindowsHookEx(hhkLowLevelKybd);
	
	
	
	return(0);

	return 0;
}













*/





