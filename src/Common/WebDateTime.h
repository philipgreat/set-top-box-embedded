// WebDateTime.h: interface for the CWebDateTime class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: WebDateTime.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ���ڽ�����׼��ʱ���ʽ����
  �ο�: 
  ����: zhangxl@channel.com
  �޶���¼:	

\*===========================================================*/

#if !defined(AFX_WEBDATETIME_H__A363D697_7A76_44E0_AF6E_CAD7D1B02223__INCLUDED_)
#define AFX_WEBDATETIME_H__A363D697_7A76_44E0_AF6E_CAD7D1B02223__INCLUDED_

#include "PortHeader.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWebDateTime  
{
private:
	short year;
	short month;
	short day;
	short dayOfWeek;
	short hour;
	short minute;
	short second;
	short msecond;


public:
	BOOL equals(CWebDateTime *other);
	void AddSeconds(int sec);
	void ShowInConsole();
	void AddHour(int hour);
	BOOL Parse(const char *data, int len);
	CWebDateTime();
	CWebDateTime(
		short year,
		short month,
		short day);
	CWebDateTime(
		short year,
		short month,
		short day,
		short hour,
		short minute,
		short second);
	CWebDateTime(
		short year,
		short month,
		short day,
		short dayOfWeek,
		short hour,
		short minute,
		short second,
		short msecond);
	virtual ~CWebDateTime();

};

#endif // !defined(AFX_WEBDATETIME_H__A363D697_7A76_44E0_AF6E_CAD7D1B02223__INCLUDED_)
