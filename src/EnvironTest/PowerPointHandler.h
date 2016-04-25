// PowerPointHandler.h: interface for the PowerPointHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERPOINTHANDLER_H__7FE09DD5_5B3D_4F33_B53B_7C3071BB4314__INCLUDED_)
#define AFX_POWERPOINTHANDLER_H__7FE09DD5_5B3D_4F33_B53B_7C3071BB4314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentHandle.h"

class PowerPointHandler : public DocumentHandle  
{
public:
	int onPage(int index, const char*text);
	PowerPointHandler();
	virtual ~PowerPointHandler();

};

#endif // !defined(AFX_POWERPOINTHANDLER_H__7FE09DD5_5B3D_4F33_B53B_7C3071BB4314__INCLUDED_)
