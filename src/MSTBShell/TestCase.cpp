// TestCase.cpp: implementation of the TestCase class.
//
//////////////////////////////////////////////////////////////////////

#include "TestCase.h"
#include "Exception.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
TestCase::TestCase(const char*name, int (*test_function) (int argc, char* argv[]))
{
	char *p=strrchr(name,':');
	this->name=p+1;
	this->test_function=test_function;
}

TestCase::~TestCase()
{
	
}

int TestCase::onFailed()
{
	printf("[FAIL]    %06d[%08X]  %f  %s\n",
		this->ret,this->ret,this->span,this->name);
	return 0;
}

int TestCase::onSuccess()
{
	printf("[OK  ]    %06d[%08X]  %f  %s\n",
		this->ret,this->ret,this->span,this->name);
	return 0;
}
#include "HighPrecisionTimer.h"
int TestCase::run(int argc, char* argv[])
{
	HighPrecisionTimer t;
	t.start();
	try{
		ret=this->test_function(argc,argv);	
	}catch(Exception &e){
		e.report();
		ret = 1;
	}
	t.end();
	this->span=t.getSpanTime();		
	
	return ret;
}

void TestCase::report(int pos)
{
	printf("%s(%d)",this->name,this->ret);
	printf("\n");
}
