#if !defined(LIVETESTCASES_H)
#define LIVETESTCASES_H
#include "TestSuite.h"
class LiveTestCases : public TestSuite  
{
private:
	static int testLove(int argc,char**argv);
	static int testHate(int argc,char**argv);
	static int testLive(int argc,char**argv);
	static int testDead(int argc,char**argv);
public:	
	int run(int argc,char **argv);
	LiveTestCases();
	virtual ~LiveTestCases();
};
#endif // !defined(LIVETESTCASES_H)
