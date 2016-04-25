// TestCase.h: interface for the TestCase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCASE_H__E8404956_3046_48C7_BB1C_67205212B1F3__INCLUDED_)
#define AFX_TESTCASE_H__E8404956_3046_48C7_BB1C_67205212B1F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TestCase  
{
private:
	int ret;
	char*name;
	double span;
	int (*test_function) (int argc, char* argv[]);
public:
	void report(int pos);
	int run(int argc, char* argv[]);
	int onSuccess();
	int onFailed();
	TestCase(const char*name, int (*test_function) (int argc, char* argv[]));
	virtual ~TestCase();

};

#endif // !defined(AFX_TESTCASE_H__E8404956_3046_48C7_BB1C_67205212B1F3__INCLUDED_)
