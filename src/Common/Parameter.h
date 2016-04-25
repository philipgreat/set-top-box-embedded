// Parameter.h: interface for the CParameter class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: Parameter.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 定义了参数的实体类，用于存储参数
  参考: 
  作者: zhangxl@channel.com
  修订记录:	

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
