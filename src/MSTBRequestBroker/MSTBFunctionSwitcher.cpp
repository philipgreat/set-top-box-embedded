// MSTBFunctionSwitcher.cpp: implementation of the MSTBFunctionSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSTBFunctionSwitcher.h"
#include "DesktopBroker.h"
#include "NetworkedTVBroker.h"
#include "HotelPortalBroker.h"
#include "DVBBroker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSTBFunctionSwitcher::CMSTBFunctionSwitcher()
{
	functionState = 0;
	this->broker = NULL;
	this->dvbBroker		= new CDVBBroker();
	this->desktopBroker	= new CDesktopBroker();
	this->networkedTVBroker=new CNetworkedTVBroker();
	this->hotelPortalBroker=new CHotelPortalBroker();
	this->broker		= dvbBroker;
	this->previousPCBroker = this->desktopBroker;
	this->broker->Start();

}

CMSTBFunctionSwitcher::~CMSTBFunctionSwitcher()
{
	delete this->dvbBroker;
	delete this->desktopBroker;
	delete this->networkedTVBroker;
	delete this->hotelPortalBroker;
}

bool CMSTBFunctionSwitcher::SwitchToDVB()
{
	functionState = 0;
	return this->SwitchToBroker(&dvbBroker);	
}

bool CMSTBFunctionSwitcher::SwitchToHotelPortal()
{
	
	return this->SwitchToBroker(&hotelPortalBroker);
}

bool CMSTBFunctionSwitcher::SwitchToNetworkedTV()
{
	return this->SwitchToBroker(&networkedTVBroker);
	//return true;
}

bool CMSTBFunctionSwitcher::SwitchToDesktop()
{
	
	return this->SwitchToBroker(&desktopBroker);
}

int CMSTBFunctionSwitcher::SendKey(int keyCode)
{
	return this->broker->OnKey(keyCode);
	
}

int CMSTBFunctionSwitcher::GetState()
{
	return this->functionState;
}

bool CMSTBFunctionSwitcher::SwitchToBroker(CMSTBSubBroker **destbroker)
{
	if((*destbroker)==NULL||(this->broker)==NULL){	
		return false;
	}
	if((this->broker)==(*destbroker))
	{
		return true;
	}else{

		//从DVB切换到PC，如果上次是PC功能是网络电视，但是本次不切换到网络电视
		//则必须先调用网络电视的终结(end)功能,终止播放器
		if(this->previousPCBroker == this->networkedTVBroker
			&&(*destbroker) != this->dvbBroker)
		{
			this->previousPCBroker->End();	
		}

		if((this->broker)->IsStarted()){
			this->broker->Leave();
		}
		
		if((*destbroker)->IsStarted()){
			this->broker = (*destbroker);
			this->broker->Reenter();			
			
		}else{
			this->broker = (*destbroker);
			this->broker->Start();			
		}
		//TODO: add another check
		if((this->broker)!=this->dvbBroker){
			this->previousPCBroker=(*destbroker);		
		}
	}
	
	return true;
}

bool CMSTBFunctionSwitcher::SwitchToPC()
{
	if(this->previousPCBroker==NULL){
		return false;
	}
	this->broker=this->previousPCBroker;
	if(this->broker == this->networkedTVBroker){		
		this->networkedTVBroker->OnKey((int)'P');
	}
	return true;
}

int CMSTBFunctionSwitcher::SetLanguageId(const char *langId)
{
	return this->broker->SetLanguageID(langId);
}

char * CMSTBFunctionSwitcher::GetCurrentFunctionName()
{
	char *p = NULL;
	if(this->broker==this->desktopBroker){
		return "pcservice";
	}
	if(this->broker==this->hotelPortalBroker){
		return "hotelportal";
	}
	if(this->broker==this->networkedTVBroker){
		return "networkedtv";
	}
	if(this->broker==this->dvbBroker){
		return "dvb";
	}
	return NULL;

}
