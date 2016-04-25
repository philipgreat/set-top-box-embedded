// ServiceFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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
#include "UDPServer.h"
#include "TestServiceObject.h"
void errexit(const char *format, ...)
{
	va_list	args;	
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();
	exit(1);
}
void HideDeskTop()
{
	int ret  = 0;
	HWND desktopwindow = ::FindWindowEx(0, 0, "Progman",NULL);
	ret = ::ShowWindow(desktopwindow,SW_HIDE);
	HWND traywindow = ::FindWindowEx(0, 0, "Shell_TrayWnd",NULL);
	ret = ::ShowWindow(traywindow, SW_HIDE);
	::CloseHandle(traywindow);

	getchar();
	ret = ::ShowWindow(desktopwindow, SW_SHOW);
	ret = ::ShowWindow(traywindow, SW_SHOW);
	::CloseHandle(desktopwindow);

}
int main(int argc, char* argv[])
{
	WSADATA wsadata;
	HideDeskTop();
	printf("UDPSERVER Pid = %u Build at %s, %s\n",
		::GetCurrentProcessId(),
		__TIME__,
		__DATE__
		);

	
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
		errexit("WSAStartup failed\n");
	
	CUDPServer server(1800);
	server.SetServiceHandler(new CTestServiceObject());
	server.Run();

	WSACleanup();
	return 0;

}

