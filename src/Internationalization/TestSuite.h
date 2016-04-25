// TestSuite.h: interface for the TestSuite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSUITE_H__8F576777_B298_4DF3_9D1F_6062515141EF__INCLUDED_)
#define AFX_TESTSUITE_H__8F576777_B298_4DF3_9D1F_6062515141EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TestCase.h"

#include <list>
using namespace std;

#define WRAP_FUNCTION(x)  #x,(x)
#define CASE(x)  new TestCase(WRAP_FUNCTION(x))
#define T(x)  add(CASE(x));

class TestSuite  
{
private:
	list<TestCase*>testcases;
	list<TestCase*>failedcases;
public:
	static void delay(int miliseconds);
	void report();
	void clear();
	void add(TestCase *p);
	int run(int argc,char **argv);
	int end();
	int start();
	TestSuite();
	virtual ~TestSuite();

};

#endif // !defined(AFX_TESTSUITE_H__8F576777_B298_4DF3_9D1F_6062515141EF__INCLUDED_)
