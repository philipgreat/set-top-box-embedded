// CDesktopBroker.cpp: implementation of the CDesktopBroker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DesktopBroker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "SystemTaskExecutor.h"
CDesktopBroker::CDesktopBroker()
{

}

CDesktopBroker::~CDesktopBroker()
{
	this->End();
}
int CDesktopBroker::Start()
{
	//
	//CSystemTaskExecutor::ShowAllWindows();
	CMSTBSubBroker::Start();
	//start a process explorer.exe
	return 0;
}
int CDesktopBroker::End()
{
	
	//CSystemTaskExecutor::HideAllWindows();
	//clean the context used by the broker
	return 0;
}
int CDesktopBroker::Reenter()
{
	//show hidden windows
	//CSystemTaskExecutor::ShowAllWindows();
	return 0;
}
int CDesktopBroker::OnKey(int keyCode)
{
	//dispatch the key
	//post message to process
	return 0;
}

int CDesktopBroker::Leave()
{
	//CSystemTaskExecutor::HideAllWindows();
	//hide the window
	return 0;
}



int CDesktopBroker::SetLanguageID(const char *langId)
{
	CMSTBSubBroker::SetLanguageID(langId);
	return 0;
}
