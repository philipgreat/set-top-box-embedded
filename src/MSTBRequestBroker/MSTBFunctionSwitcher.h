// MSTBFunctionSwitcher.h: interface for the MSTBFunctionSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTBFUNCTIONSWITCHER_H__57756B82_929F_4E7F_9C6C_0F2C1C0FE8D3__INCLUDED_)
#define AFX_MSTBFUNCTIONSWITCHER_H__57756B82_929F_4E7F_9C6C_0F2C1C0FE8D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MSTBSubBroker.h"

class CMSTBFunctionSwitcher  
{
private:
	int functionState;
	CMSTBSubBroker *broker;
	CMSTBSubBroker *previousPCBroker;
	CMSTBSubBroker *dvbBroker;
	CMSTBSubBroker *hotelPortalBroker;
	CMSTBSubBroker *desktopBroker;
	CMSTBSubBroker *networkedTVBroker;

public:
	char * GetCurrentFunctionName();
	int SetLanguageId(const char*langId);
	bool SwitchToPC();
	bool SwitchToBroker(CMSTBSubBroker **destbroker);
	int GetState();
	int SendKey(int keyCode);
	bool SwitchToDesktop();
	bool SwitchToNetworkedTV();
	bool SwitchToHotelPortal();
	bool SwitchToDVB();
	CMSTBFunctionSwitcher();
	virtual ~CMSTBFunctionSwitcher();

};

#endif // !defined(AFX_MSTBFUNCTIONSWITCHER_H__57756B82_929F_4E7F_9C6C_0F2C1C0FE8D3__INCLUDED_)
