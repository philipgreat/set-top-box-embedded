// URLParameters.h: interface for the CURLParameters class.
//
//////////////////////////////////////////////////////////////////////

/*===========================================================*\
  文件: URLParameters.h
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 把URL数据解析成name-value的对的类
  参考: CParameters  
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/

#if !defined(AFX_URLPARAMETERS_H__27DC2BB2_9451_4ED7_BE68_64C4B0BEFEAD__INCLUDED_)
#define AFX_URLPARAMETERS_H__27DC2BB2_9451_4ED7_BE68_64C4B0BEFEAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Parameters.h"

class CURLParameters : public CParameters  
{
public:
	BOOL AddParameter(const char *name, const char *value);

	int Parse(const char *data);
	CURLParameters();
	virtual ~CURLParameters();

};

#endif // !defined(AFX_URLPARAMETERS_H__27DC2BB2_9451_4ED7_BE68_64C4B0BEFEAD__INCLUDED_)
