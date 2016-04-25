// NetworkedTVBroker.h: interface for the NetworkedTVBroker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKEDTVBROKER_H__183C54C7_228D_418B_A189_0489764C24E1__INCLUDED_)
#define AFX_NETWORKEDTVBROKER_H__183C54C7_228D_418B_A189_0489764C24E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mstbsubbroker.h"
class CNetworkedTVBroker:public CMSTBSubBroker  
{
private:
	int browserProcessId ;

public:
	int SetLanguageID(const char *langId);
	int Leave();
	CNetworkedTVBroker();
	virtual ~CNetworkedTVBroker();
	int OnKey(int keyCode);
	int Start();
	int End();
	int Reenter();
};

#endif // !defined(AFX_NETWORKEDTVBROKER_H__183C54C7_228D_418B_A189_0489764C24E1__INCLUDED_)
