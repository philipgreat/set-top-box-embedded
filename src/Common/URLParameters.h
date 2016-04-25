// URLParameters.h: interface for the CURLParameters class.
//
//////////////////////////////////////////////////////////////////////

/*===========================================================*\
  �ļ�: URLParameters.h
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ��URL���ݽ�����name-value�ĶԵ���
  �ο�: CParameters  
  ����: zhangxl@channel.com
  �޶���¼:	

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
