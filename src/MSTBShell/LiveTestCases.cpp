#include "stdafx.h"
#include "LiveTestCases.h"
LiveTestCases::LiveTestCases()
{
}
LiveTestCases::~LiveTestCases()
{
		
}
int LiveTestCases::run(int argc, char **argv)
{
	int ret = 0;
	printf("--------------------------------------------------------------\n");
	printf("%s@%s,%s\n",__FILE__,__TIME__,__DATE__);
	printf("--------------------------------------------------------------\n");	
	T(LiveTestCases::testLove);
	T(LiveTestCases::testHate);
	T(LiveTestCases::testLive);
	T(LiveTestCases::testDead);
	
	ret = TestSuite::run(argc,argv);
	return ret;
}
int LiveTestCases::testLove(int argc, char **argv)
{
	int ret = 1;
	return ret;
}
int LiveTestCases::testHate(int argc, char **argv)
{
	int ret = 1;
	return ret;
}
int LiveTestCases::testLive(int argc, char **argv)
{
	int ret = 1;
	return ret;
}
int LiveTestCases::testDead(int argc, char **argv)
{
	int ret = 1;
	return ret;
}
