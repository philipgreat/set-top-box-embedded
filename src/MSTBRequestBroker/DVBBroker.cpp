// CDVBBroker.cpp: implementation of the CDVBBroker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DVBBroker.h"
#include "SystemTaskExecutor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDVBBroker::CDVBBroker()
{

}

CDVBBroker::~CDVBBroker()
{
	this->End();

}
int CDVBBroker::Start()
{
	CMSTBSubBroker::Start();
	return 0;
}
int CDVBBroker::End()
{
	return 0;
}
int CDVBBroker::Reenter()
{
	return 0;
}
int CDVBBroker::OnKey(int keyCode)
{
	//donothing
	return 0;
}

int CDVBBroker::Leave()
{
	return 0;
}

int CDVBBroker::SetLanguageID(const char *langId)
{
	CMSTBSubBroker::SetLanguageID(langId);
	return 0;
}
