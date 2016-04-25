// MSTBShellAppTestCases.cpp: implementation of the MSTBShellAppTestCases class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSTBLiveKeepingTestCases.h"
#include "MSTBShellApp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MSTBShellAppTestCases::MSTBShellAppTestCases()
{

}

MSTBShellAppTestCases::~MSTBShellAppTestCases()
{

}
int MSTBShellAppTestCases::run(int argc, char ** argv)
{
	int ret = 0;
	printf("--------------------------------------------------------------\n");
	printf("%s@%s,%s\n",__FILE__,__TIME__,__DATE__);
	printf("--------------------------------------------------------------\n");	
	ret = TestSuite::run(argc,argv);
	return ret;
}
#include <windows.h>

int MSTBShellAppTestCases::process_alive_live(int argc, char* argv[])
{
	return !(MSTBShellApp::isProcessAlive(0));
}

int MSTBShellAppTestCases::process_alive_dead(int argc, char* argv[])
{
	return (MSTBShellApp::isProcessAlive(13161));

}


#include <windows.h>
int MSTBShellAppTestCases::testRun(int argc, char **argv)
{
	MSTBShellApp app;
	//app.config("c:\\settopbox","d:\\settopbox");
	app.config("http://suddy.channel.com/download/","d:\\settopbox","c:\\settopbox");
	app.run();
	return 0;
	//	MSTBLiveKeepingProcessList	
}

void MSTBShellAppTestCases::registerTestCases()
{
	T(MSTBShellAppTestCases::process_alive_live);
	//T(MSTBShellAppTestCases::process_alive_dead);
	//T(MSTBShellAppTestCases::testRun);
}
