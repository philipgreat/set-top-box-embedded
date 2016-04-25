// SystemTaskExecutor.h: interface for the SystemTaskExecutor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMTASKEXECUTOR_H__895B3E29_45CE_4DED_92CE_B166AB3386F1__INCLUDED_)
#define AFX_SYSTEMTASKEXECUTOR_H__895B3E29_45CE_4DED_92CE_B166AB3386F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _WIN32_WINNT 0x0500
#include <windows.h>
class CSystemTaskExecutor
{
public:
	static bool EnableTaskManager();
	static bool DisableTaskManager();
	static int EnableSystemHotKeys();
	static int DisableSystemHotKeys();
	static int ForceShowAllWindows();
	static int HideAllWindows();
	static int ShowAllWindows();
	static int ShowDesktop();
	static int HideDesktop();
	static int SendKeyUpToWindow(unsigned long windowHandle,DWORD message);
	static int SendKeyCodeToWindow(DWORD windowHandle,DWORD wparam);
	//returns pid of the created process
	static int ExecuteTask(char *filePath,char *param);
	static BOOL SendKeyCodeToWindow(const char *windowName, DWORD wparam);
	static BOOL SendWindowMessage(const char *windowName,DWORD messageId,DWORD lparam,DWORD wparam);
	static int KillProcess(int pid);
	static int SetSystemVolume(int percent);
	static int RestartPC();
	static int SleepPC();
	static int SetSystemTime(int absoluteSecondsFrom1970);
	CSystemTaskExecutor();
	virtual ~CSystemTaskExecutor();

};

#endif // !defined(AFX_SYSTEMTASKEXECUTOR_H__895B3E29_45CE_4DED_92CE_B166AB3386F1__INCLUDED_)
