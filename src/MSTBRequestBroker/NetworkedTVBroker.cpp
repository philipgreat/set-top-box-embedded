// CNetworkedTVBroker.cpp: implementation of the CNetworkedTVBroker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetworkedTVBroker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static char const *browserWindowName="browser";
static char const *playerWindowName="player";
#include "SystemTaskExecutor.h"
#include "MSTBConfiguration.h"
CNetworkedTVBroker::CNetworkedTVBroker()
{
}


CNetworkedTVBroker::~CNetworkedTVBroker()
{
	this->End();

}
static int OpenNetworkedTV()
{

	CMSTBConfiguration config;
	char* path = config.GetBrowserPath();
	char* param = config.GetNetworkedTVURL();
	char realparm[1024*4];
	sprintf(realparm,"-n %s",param);
	if(path!=NULL&&param!=NULL){
		return CSystemTaskExecutor::ExecuteTask(path,realparm);
	}else{
		return 0;
	}
}
static int OpenOldNetworkedTV()
{

	CMSTBConfiguration config;
	char* path = config.GetBrowserPath();
	char* param = config.GetNetworkedTVURL();
	if(path!=NULL&&param!=NULL){
		return CSystemTaskExecutor::ExecuteTask(path,"-n open-old-page");
	}else{
		return 0;
	}

}

int CNetworkedTVBroker::Start()
{
	CMSTBSubBroker::Start();
	browserProcessId = OpenNetworkedTV();
	return browserProcessId!=0;
}
int CNetworkedTVBroker::End()
{
	//CSystemTaskExecutor::SendWindowMessage(browserWindowName,WM_KEYDOWN,27,0);
	CSystemTaskExecutor::SendKeyCodeToWindow(playerWindowName,27);	
	printf("int CNetworkedTVBroker::End()\n");
	CSystemTaskExecutor::KillProcess(browserProcessId);
	return 0;
}
int CNetworkedTVBroker::Reenter()
{
	browserProcessId = OpenNetworkedTV();
	return browserProcessId!=0;
}
int CNetworkedTVBroker::OnKey(int keyCode)
{
	//if we failed to send message to the player, ok
	//we send the message to the browser
	//we have no idea to sent the other window
	if(!CSystemTaskExecutor::SendKeyCodeToWindow(playerWindowName,keyCode))
	{
		CSystemTaskExecutor::SendKeyCodeToWindow(browserWindowName,keyCode);
	}
	//record the state if player is started 
	return 1;
}

int CNetworkedTVBroker::Leave()
{	
	CSystemTaskExecutor::SendKeyCodeToWindow(playerWindowName,(int)'P');
	//CSystemTaskExecutor::KillProcess(browserProcessId);
	return 0;
}


int CNetworkedTVBroker::SetLanguageID(const char *langId)
{
	CMSTBSubBroker::SetLanguageID(langId);
	return 0;
}
