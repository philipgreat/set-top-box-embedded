// Exception.cpp: implementation of the Exception class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
Exception::Exception(const char *message)
{
	this->message =(char*) message;
}

Exception::~Exception()
{

}

void Exception::report()
{
	printf("%s\n",this->message);

}
