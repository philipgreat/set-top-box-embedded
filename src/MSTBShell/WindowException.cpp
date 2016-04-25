// WindowException.cpp: implementation of the WindowException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindowException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <windows.h>

WindowsException::~WindowsException()
{

}

void WindowsException::report()
{
	DWORD err = ::GetLastError();
	LPVOID lpMsgBuf;
    FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
    ); 
	printf("%s: (dec=%u,hex=%08X) %s",this->message,err,err,lpMsgBuf);

}
