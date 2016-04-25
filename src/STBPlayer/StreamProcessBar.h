// StreamProcessBar.h: interface for the CStreamProcessBar class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: ChannelMediaPlayer.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ��ʱʹ�õĽ�����
  �ο�: 
  ����: zhangxl@channel.com
  �޶���¼:	

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
