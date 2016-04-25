// ChannelPlayerOSD.h: interface for the CChannelPlayerOSD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANNELPLAYEROSD_H__20B80B29_EF3E_42F2_AD7F_15E0F6254F87__INCLUDED_)
#define AFX_CHANNELPLAYEROSD_H__20B80B29_EF3E_42F2_AD7F_15E0F6254F87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Overlay.h"

class CChannelPlayerOSD : public COverlay  
{
private:
	char	*message;
	int		volume;
	int		currentStreamPercent;
	int		timerCount;

public:
	BOOL ShowMenu();
	int UpdatePercent(int percent);
	bool ToggleShow();
	BOOL ShowMenu(char *message, int percent);
	int OnTimer();
	BOOL DrawVolume(int position);
	BOOL ShowVolume(int position);
	BOOL DrawMenu(char *message,int percent);
	CChannelPlayerOSD();
	virtual ~CChannelPlayerOSD();

};

#endif // !defined(AFX_CHANNELPLAYEROSD_H__20B80B29_EF3E_42F2_AD7F_15E0F6254F87__INCLUDED_)
