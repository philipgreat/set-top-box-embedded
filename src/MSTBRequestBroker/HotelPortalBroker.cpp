// CHotelPortalBroker.cpp: implementation of the CHotelPortalBroker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HotelPortalBroker.h"
#include "MSTBConfiguration.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "SystemTaskExecutor.h"
CHotelPortalBroker::CHotelPortalBroker()
{
	appProcessId=0;
}

CHotelPortalBroker::~CHotelPortalBroker()
{
	this->End();
}
static int OpenHotelPortal()
{

	CMSTBConfiguration config;
	char* path = config.GetBrowserPath();
	char* param = config.GetHotelPortalURL();
	if(path!=NULL&param!=NULL){
		return CSystemTaskExecutor::ExecuteTask(path,param);
	}else{
		return 0;
	}

}
int CHotelPortalBroker::Start()
{
	CMSTBSubBroker::Start();
	appProcessId = OpenHotelPortal();
	return appProcessId!=0;
}
int CHotelPortalBroker::End()
{
	//CSystemTaskExecutor::SendWindowMessage("browser",WM_CLOSE,0,0);
	CSystemTaskExecutor::KillProcess(appProcessId);
	return 0;
}
int CHotelPortalBroker::Reenter()
{
	appProcessId = OpenHotelPortal();
	return appProcessId!=0;
}
int CHotelPortalBroker::OnKey(int keyCode)
{
	//we simplely ignore this message
	return 0;
}

int CHotelPortalBroker::Leave()
{
	CSystemTaskExecutor::KillProcess(appProcessId);	
	return 0;
}

int CHotelPortalBroker::SetLanguageID(const char *langId)
{
	CMSTBSubBroker::SetLanguageID(langId);
	return 0;
}
