// MSTBLiveKeepingTestCases.h: interface for the MSTBLiveKeepingTestCases class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTBLIVEKEEPINGTESTCASES_H__00632A7C_7BFF_4A85_80FA_BF9E4DB9362C__INCLUDED_)
#define AFX_MSTBLIVEKEEPINGTESTCASES_H__00632A7C_7BFF_4A85_80FA_BF9E4DB9362C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestSuite.h"

class MSTBShellAppTestCases : public TestSuite  
{
public:
	int run(int agrc, char ** argv);

private:
	static int testRun(int argc,char**argv);
	static int process_alive_live(int argc, char* argv[]);
	static int process_alive_dead(int argc, char* argv[]);
public:
	void registerTestCases();
	MSTBShellAppTestCases();
	virtual ~MSTBShellAppTestCases();

};

#endif // !defined(AFX_MSTBLIVEKEEPINGTESTCASES_H__00632A7C_7BFF_4A85_80FA_BF9E4DB9362C__INCLUDED_)
