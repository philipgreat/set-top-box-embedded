// DesktopBroker.h: interface for the DesktopBroker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESKTOPBROKER_H__DD5BCF1A_A63B_435A_B842_5D6C68BC4F25__INCLUDED_)
#define AFX_DESKTOPBROKER_H__DD5BCF1A_A63B_435A_B842_5D6C68BC4F25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mstbsubbroker.h"

class CDesktopBroker  :public CMSTBSubBroker
{
public:
	int SetLanguageID(const char *langId);
	int Leave();
	CDesktopBroker();
	virtual ~CDesktopBroker();
	int OnKey(int keyCode);
	int Start();
	int End();
	int Reenter();

};

#endif // !defined(AFX_DESKTOPBROKER_H__DD5BCF1A_A63B_435A_B842_5D6C68BC4F25__INCLUDED_)
