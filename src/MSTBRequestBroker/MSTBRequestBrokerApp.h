// MSTBRequestBrokerApp.h: interface for the MSTBRequestBrokerApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTBREQUESTBROKERAPP_H__0CF7B821_68CE_4B61_BADF_5389D72C2DE6__INCLUDED_)
#define AFX_MSTBREQUESTBROKERAPP_H__0CF7B821_68CE_4B61_BADF_5389D72C2DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\common\\URLParameters.h"
#include "MSTBFunctionSwitcher.h"


class CMSTBRequestBrokerApp  
{
private:
	CMSTBFunctionSwitcher *switcher;

	char command[256];
	char returnValue[256];
	int  externalCommandSequenceNumber;

	CURLParameters parameters;

public:
	int QueryFunctionStartup(char *functionName);
	int Execute();
	char * GetReturnValue();
	bool ParseMessage(char *message,int messageLength);

	int QueryFunctionAvailable(char *funcitonName);
	bool SetLanguageID(int LanguageID);
	bool SwitchOutputToPC();
	int SendKey(int key);
	int SetReturnValue(const char *returnDescription);
	bool SwitchToDVB();
	bool SwitchToHotelPortal();
	bool SwitchToDesktop();
	bool SwitchToNetworkedTV();
	bool ReceiveMessage(char *message,int messageLength);
	bool RestartPC();
	bool SleepPC();
	bool UpdateAd(char *adInfo);
	bool UpdateMenu(char *menuInfo);
	bool UpdateAdImage(char *adId, char *imageURL);
	bool UpdateMenuItemImage(char *menuId,char *imageURL);
	bool UpdateBackgroundImage(char *url);
	bool SwitchOutputToDVB();
	bool SubmitDVBStateInfo(char *name,char *value);
	bool StartFunctionOnPC(char *functionName);
	bool IsFunctionAvailable(char *functionName);
	int QueryPCState();
	bool SynchronizeTime(int absoluteSecondsFrom1970);
	bool SynchronizeVolume(int percent);
	CMSTBRequestBrokerApp();
	virtual ~CMSTBRequestBrokerApp();

};

#endif // !defined(AFX_MSTBREQUESTBROKERAPP_H__0CF7B821_68CE_4B61_BADF_5389D72C2DE6__INCLUDED_)
