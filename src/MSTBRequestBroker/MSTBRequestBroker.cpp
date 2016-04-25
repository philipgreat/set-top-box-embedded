// MSTBRequestBroker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SystemTaskExecutor.h"
#include "MSTBFunctionSwitcher.h"
#include "MSTBRequestBrokerApp.h"
#ifndef  _WIN32_WCE
#pragma comment(lib,"ws2_32")
#include <Winsock2.h>
#else
#pragma comment(lib,"ws2")
#include <Winsock.h>
#endif
#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "..\\ServiceFramework\\UDPServer.h"
#include "BrokerServiceObject.h"
void errexit(const char *format, ...)
{
	va_list	args;	
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();
	exit(1);
}



//	CSystemTaskExecutor::RestartPC();
//  CSystemTaskExecutor::SetSystemTime( 1040000000);
//	CSystemTaskExecutor::SetSystemVolume(50);
//	CSystemTaskExecutor::ExecuteTask("f:\\suddy\\mytool\\log.exe","null");
//	CSystemTaskExecutor::SendKeyCodeToWindow("browser",65);
int test_switcher(int argc, char* argv[])
{
	CMSTBFunctionSwitcher *switcher=new  CMSTBFunctionSwitcher;
	switcher->SwitchToDVB();
	switcher->SwitchToDesktop();
	switcher->SwitchToHotelPortal();
	switcher->SwitchToDesktop();
	switcher->SwitchToNetworkedTV();
	switcher->SwitchToDVB();
	switcher->SwitchToNetworkedTV();
	switcher->SwitchToDesktop();	
	switcher->SwitchToDesktop();
	delete switcher;
	
	return 0;
	
}
static char *test_cases[]={
		"12@SwitchToDVB  ",
		"14@SwitchToHotelPortal  ",
		"15@SwitchToDesktop  ",
		"16@SwitchToNetworkedTV  ",
		"17@RestartPC  ",
		"18@SleepPC  ",
		"19@UpdateAd adInfo=adinfo ",
		"22@UpdateMenu menuInfo=menuInfo ",
		"32@UpdateAdImage adId=100&imageURL=http:// ",
		"42@UpdateMenuItemImage menuId=100&imageURL=http ",
		"52@UpdateBackgroundImage url=http ",
		"62@SwitchOutputToDVB  ",
		"72@SubmitDVBStateInfo name=name&value=value ",
		"82@StartFunctionOnPC functionName=x ",
		"92@IsFunctionAvailable functionName=x ",
		"112@QueryPCState  ",
		"212@SynchronizeTime seconds=1232142",
		"312@SynchronizeVolume   percent=50",
		"exit",		
		NULL,
		
};
int test_execute_command(int argc, char* argv[])
{
	//CSystemTaskExecutor::SendKeyCodeToWindow("player",'Q');
	char message[1024];
	CMSTBRequestBrokerApp *app=new CMSTBRequestBrokerApp();
	char **p=test_cases;
	while(*p!=NULL){
		//printf("tester#brokershell: ");
		//scanf("%s",message);
		//RestartPC style=10&method=goanother
		strcpy(message,*p);
		if(strncmp(message,"exit",5)==0){
			break;
		}
		
		app->ParseMessage(message,1024);
		app->Execute();
		p++;
		
		
	}
	delete app;
	//CSystemTaskExecutor::SendKeyCodeToWindow("browser",65);
	return 0;

}
int start_server()
{

	WSADATA wsadata;
	
	printf("UDPSERVER Pid = %u@%s, %s\n",
		::GetCurrentProcessId(),
		__TIME__,
		__DATE__
		);
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
		errexit("WSAStartup failed\n");
	
	CUDPServer server(1800);
	server.SetServiceHandler(new CBrokerServiceObject());
	server.Run();
	WSACleanup();
	return 0;

}
int main(int argc, char* argv[])
{
	return start_server();
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int CmdShow)
{
	return start_server();
}

/*
ut 10.130.36.51 1800 12@SwitchToDVB
ut 10.130.36.51 1800 14@SwitchToHotelPortal
ut 10.130.36.51 1800 15@SwitchToDesktop
ut 10.130.36.51 1800 16@SwitchToNetworkedTV
ut 10.130.36.51 1800 18@SleepPC
ut 10.130.36.51 1800 62@SwitchOutputToDVB
ut 10.130.36.51 1800 112@QueryPCState
*/