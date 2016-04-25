// HTTPClientTest.cpp : Defines the entry point for the console application.
//


// PureCUDPClient.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <windows.h>
#include "UpdateTestCases.h"
#include "MSTBLiveKeepingTestCases.h"
#include "TCPClient.h"
#include "MSTBShellApp.h"
//#include "MSTBShellApp.h"
int main(int argc, char* argv[])
{
#ifdef _WIN32
	init_environment();
#endif	
	//UpdateTestCases().run(argc,argv);
	//MSTBShellAppTestCases().run(0,NULL);
	printf("MSTBShell pid = %u@%s, %s\n",
		::GetCurrentProcessId(),
		__TIME__,
		__DATE__
		);


	MSTBShellApp app;
	//app.config("c:\\settopbox","d:\\settopbox");
	app.config(
		"http://suddy.channel.com/download/",
		"d:\\settopbox",
		"c:\\settopbox");
	app.run();
	//UpdateTestCases().run(argc,argv);
	return 0;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int CmdShow)
{
#ifdef _WIN32
	init_environment();
#endif
	UpdateTestCases().run(0,NULL);
	MSTBShellAppTestCases().run(0,NULL);
	return 0;
}
