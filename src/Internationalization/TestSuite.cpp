// TestSuite.cpp: implementation of the TestSuite class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestSuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestSuite::TestSuite()
{

}

TestSuite::~TestSuite()
{

}

int TestSuite::start()
{
	return 0;

}

int TestSuite::end()
{
	return 0;
}


#include <algorithm>

int TestSuite::run(int argc,char **argv)
{	
	list<TestCase*>::iterator iter;
	for(iter=this->testcases.begin();iter!=this->testcases.end();iter++){
		if(0==(*iter)->run(argc,argv)){
			(*iter)->onSuccess();
		}else{
			(*iter)->onFailed();
			this->failedcases.push_back((*iter));
		}	
	}
	printf("-----------------------failed cases: %u/%u------------------------\n",
		this->failedcases.size(),this->testcases.size());
	this->report();
	printf("\n\n");
	return 0;
}

void TestSuite::add(TestCase *p)
{
	this->testcases.push_back(p);
}

void TestSuite::clear()
{
	list<TestCase*>::iterator iter=this->testcases.begin();
	while(iter!=this->testcases.end())
	{
		this->testcases.remove(*iter);
		delete (*iter);
		iter++;
	}
}

void TestSuite::report()
{
	list<TestCase*>::iterator iter;
	int i=0;
	for(iter=this->failedcases.begin();iter!=this->failedcases.end();iter++){
		(*iter)->report(i);
		i++;
	}
}


/*
template <class T>struct TestExecutor{
	int argc;
	char ** argv;
	TestExecutor(int argc,char **argv){
		this->argc=argc;
		this->argv=argv;
	};
	operator () (T *tcase){
		if(0==tcase->run(argc,argv)){
			tcase->onSuccess();
		}else{
			tcase->onFailed();
		}
	}
};

*/
#ifdef _WIN32
#include <windows.h>
#endif

void TestSuite::delay(int miliseconds)
{
	//::CreateWaitableTimer(
#ifdef _WIN32
	Sleep(miliseconds);
#endif
}
