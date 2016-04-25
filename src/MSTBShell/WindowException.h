// WindowException.h: interface for the WindowException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWEXCEPTION_H__FCAFE683_C69C_47AF_8261_E8FB9DA740B4__INCLUDED_)
#define AFX_WINDOWEXCEPTION_H__FCAFE683_C69C_47AF_8261_E8FB9DA740B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Exception.h"
class WindowsException : public Exception 
{
public:
	void report();
	WindowsException(const char *message):Exception(message){};
	virtual ~WindowsException();

};

#endif // !defined(AFX_WINDOWEXCEPTION_H__FCAFE683_C69C_47AF_8261_E8FB9DA740B4__INCLUDED_)
