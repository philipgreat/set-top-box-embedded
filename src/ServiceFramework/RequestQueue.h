// RequestQueue.h: interface for the CRequestQueue class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: Parameters.h:	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 请求队列的包装的类，同步多个请求
  参考: 
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/
#if !defined(AFX_REQUESTQUEUE_H__876E559F_6D11_487D_B777_807CDF448B61__INCLUDED_)
#define AFX_REQUESTQUEUE_H__876E559F_6D11_487D_B777_807CDF448B61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;
#include <windows.h>
//这个类的实例必须在同步的情况下进行访问
//TODO: add critical section machanism here to control the access of 
//parallal threads
#include "ServiceRequest.h"
class CRequestQueue
{
private:
	//CServiceRequest *requst;
	queue<CServiceRequest *> requestQueue;
public:
	DWORD GetCount();
	CServiceRequest* Dequeue();
	void AddRequest(CServiceRequest *req);
	CRequestQueue();
	virtual ~CRequestQueue();
};

#endif // !defined(AFX_REQUESTQUEUE_H__876E559F_6D11_487D_B777_807CDF448B61__INCLUDED_)
