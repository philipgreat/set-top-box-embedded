// StreamProcessBar.h: interface for the CStreamProcessBar class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: ChannelMediaPlayer.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 临时使用的进度条
  参考: 
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/
#if !defined(AFX_STREAMPROCESSBAR_H__2A993F9A_88B8_4600_83AF_EBFA1A4EE2F6__INCLUDED_)
#define AFX_STREAMPROCESSBAR_H__2A993F9A_88B8_4600_83AF_EBFA1A4EE2F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
#include <commctrl.h>
class CStreamProcessBar  
{
private:
	HWND   procBar;
	int    showX;
	int	   showY;
public:
	void SetPosition(int pos);
	int Hide();
	int Show();
	int CreateProcessBar(HINSTANCE instance,HWND parent);
	CStreamProcessBar();
	virtual ~CStreamProcessBar();

};

#endif // !defined(AFX_STREAMPROCESSBAR_H__2A993F9A_88B8_4600_83AF_EBFA1A4EE2F6__INCLUDED_)
