// HotelPortalBroker.h: interface for the HotelPortalBroker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOTELPORTALBROKER_H__24F106D9_699A_4070_B29B_B770B0D5426E__INCLUDED_)
#define AFX_HOTELPORTALBROKER_H__24F106D9_699A_4070_B29B_B770B0D5426E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mstbsubbroker.h"
class CHotelPortalBroker:public CMSTBSubBroker
{
private:
	int appProcessId ;
public:
	int SetLanguageID(const char *langId);
	int Leave();
	CHotelPortalBroker();
	virtual ~CHotelPortalBroker();
	int OnKey(int keyCode);
	int Start();
	int End();
	int Reenter();

};

#endif // !defined(AFX_HOTELPORTALBROKER_H__24F106D9_699A_4070_B29B_B770B0D5426E__INCLUDED_)
