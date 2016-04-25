// DVBBroker.h: interface for the DVBBroker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DVBBROKER_H__5DBC764C_46B8_4704_B6E0_6E1AEB2FF2FA__INCLUDED_)
#define AFX_DVBBROKER_H__5DBC764C_46B8_4704_B6E0_6E1AEB2FF2FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mstbsubbroker.h"
class CDVBBroker  :public CMSTBSubBroker
{
public:
	int SetLanguageID(const char *langId);
	int Leave();
	CDVBBroker();
	virtual ~CDVBBroker();
	int OnKey(int keyCode);
	int Start();
	int End();
	int Reenter();
};

#endif // !defined(AFX_DVBBROKER_H__5DBC764C_46B8_4704_B6E0_6E1AEB2FF2FA__INCLUDED_)
