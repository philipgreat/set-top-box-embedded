// WebDateTime.h: interface for the CWebDateTime class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: WebDateTime.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 用于解析标准的时间格式的类
  参考: 
  作者: zhangxl@channel.com
  修订记录:	

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
