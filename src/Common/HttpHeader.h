// HttpHeader.h: interface for the CHttpHeader class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: HttpHeader.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 解析HTTP头的工具的类, 用于进一步处理HTTP应答
  参考: CGenericSaxParser, CCertificateParserHelper
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/

#if !defined(AFX_HTTPHEADER_H__18843FAC_A8DB_4AB9_953C_5418420275C7__INCLUDED_)
#define AFX_HTTPHEADER_H__18843FAC_A8DB_4AB9_953C_5418420275C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Parameters.h"

class CHttpHeader : public CParameters  
{
public:
	int GetInt(const char* name);
	int Test();
	int Parse(const char *data);
	CHttpHeader();
	virtual ~CHttpHeader();

};

#endif // !defined(AFX_HTTPHEADER_H__18843FAC_A8DB_4AB9_953C_5418420275C7__INCLUDED_)
