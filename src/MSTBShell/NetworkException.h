// NetworkException.h: interface for the NetworkException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKEXCEPTION_H__896FD747_C31D_426D_B3BC_0BE61FF7D309__INCLUDED_)
#define AFX_NETWORKEXCEPTION_H__896FD747_C31D_426D_B3BC_0BE61FF7D309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Exception.h"

class NetworkException : public Exception  
{
public:
	NetworkException(char *message):Exception(message){};
	virtual ~NetworkException();
};

#endif // !defined(AFX_NETWORKEXCEPTION_H__896FD747_C31D_426D_B3BC_0BE61FF7D309__INCLUDED_)
