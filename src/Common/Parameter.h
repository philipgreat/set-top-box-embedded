// Parameter.h: interface for the CParameter class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: Parameter.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: �����˲�����ʵ���࣬���ڴ洢����
  �ο�: 
  ����: zhangxl@channel.com
  �޶���¼:	

\*===========================================================*/
#if !defined(AFX_PARAMETER_H__3079DF5B_D261_4062_9AD2_6ACBA0D2F602__INCLUDED_)
#define AFX_PARAMETER_H__3079DF5B_D261_4062_9AD2_6ACBA0D2F602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParameter  
{
private: 
	char *name;
	char *value;
public:
	void Report();
	char * GetValue()
	{
		return this->value;
	}
	char * GetName();
	CParameter();

	CParameter(const char *name,const char* value);

	virtual ~CParameter();

};

#endif // !defined(AFX_PARAMETER_H__3079DF5B_D261_4062_9AD2_6ACBA0D2F602__INCLUDED_)
