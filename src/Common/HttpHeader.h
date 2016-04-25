// HttpHeader.h: interface for the CHttpHeader class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: HttpHeader.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ����HTTPͷ�Ĺ��ߵ���, ���ڽ�һ������HTTPӦ��
  �ο�: CGenericSaxParser, CCertificateParserHelper
  ����: zhangxl@channel.com
  �޶���¼:	

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
