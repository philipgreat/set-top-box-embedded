// FileSystemException.h: interface for the FileSystemException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESYSTEMEXCEPTION_H__E233970B_693A_4202_B59D_2CC6957CAF08__INCLUDED_)
#define AFX_FILESYSTEMEXCEPTION_H__E233970B_693A_4202_B59D_2CC6957CAF08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Exception.h"

class FileSystemException : public Exception  
{
public:
	FileSystemException(char *message):Exception(message){};
	virtual ~FileSystemException();

};

#endif // !defined(AFX_FILESYSTEMEXCEPTION_H__E233970B_693A_4202_B59D_2CC6957CAF08__INCLUDED_)
