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

#ifdef _WIN32
	#include <windows.h>
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <sys/types.h>

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
	bool toStandardTime(time_t  *time);

#ifdef  _WIN32
	bool fromSystemTime(SYSTEMTIME *systime);
	bool toSystemTime(SYSTEMTIME *systime);
#endif
	bool before(CWebDateTime *p);
	bool equals(CWebDateTime *other);
	void report();
	void addHour(int hour);
	bool parse(const char *data, int len);
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
