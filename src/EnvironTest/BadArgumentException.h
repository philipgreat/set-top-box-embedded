// BadArgumentException.h: interface for the BadArgumentException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BADARGUMENTEXCEPTION_H__AEA604E3_9FAC_4AA3_8AFA_85DA339E0B2F__INCLUDED_)
#define AFX_BADARGUMENTEXCEPTION_H__AEA604E3_9FAC_4AA3_8AFA_85DA339E0B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
#include "Exception.h"

class BadArgumentException : public Exception  
{
public:
	BadArgumentException(char *message):Exception(message){};
	virtual ~BadArgumentException();
};

#endif // !defined(AFX_BADARGUMENTEXCEPTION_H__AEA604E3_9FAC_4AA3_8AFA_85DA339E0B2F__INCLUDED_)
