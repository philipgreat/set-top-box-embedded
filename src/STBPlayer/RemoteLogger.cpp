// RemoteLogger.cpp: implementation of the CRemoteLogger class.
//
//////////////////////////////////////////////////////////////////////

#include "RemoteLogger.h"

#include <stdlib.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRemoteLogger::CRemoteLogger()
{
	client.Init();
	client.Connect ("10.130.36.24",16800);

	//	client.Send("Window CE from STB started\r\n");
	this->Log(__DATE__,"THE SYSTEM STARTED");


}
CRemoteLogger::CRemoteLogger(char *hostName)
{
	client.Init();
	client.Connect (hostName,16800);

	//	client.Send("Window CE from STB started\r\n");
	this->Log(__DATE__,"THE SYSTEM STARTED");


}


CRemoteLogger::~CRemoteLogger()
{
	client.Close();

}

int CRemoteLogger::Log(int i)
{

	return this->Log("",i);;
}

int CRemoteLogger::Log(const char *message)
{
	char charMessage[1024+1024];
	this->UpdateCurrentTime();
	sprintf(charMessage,"%s %s\r\n",this->timeString,message);
	this->client.Send(charMessage);
	return 0;

}

int CRemoteLogger::Log(WCHAR *message)
{
	char charMessage[1024];
	wcstombs(charMessage, message, sizeof(charMessage));
	this->Log(charMessage);
	return 0;
}

int CRemoteLogger::UpdateCurrentTime()
{
	GetSystemTime(&m_SystemTime);
	sprintf(timeString,"%02d/%02d %02d:%02d:%02d.%03d",
		m_SystemTime.wMonth,
		m_SystemTime.wDay,
		(m_SystemTime.wHour+8)%24,
		m_SystemTime.wMinute,
		m_SystemTime.wSecond,
		m_SystemTime.wMilliseconds);

	return 0;

}

int CRemoteLogger::Log(const char *postion, const char *message)
{
	char charMessage[1024]; 
	sprintf(charMessage, 
		("%s %s"), 
		postion,
		message);

	this->Log(charMessage);
	return 0;

}

int CRemoteLogger::Log(const char *postion, int j)
{
	char charMessage[100]; 
	sprintf(charMessage, 
		("%s\t[int]%06d"), 
		postion,
		j);
	this->Log(charMessage);
	return 0;
}
//output like 07/10 15:52:08.000 F:\SUDDY\WINCE\IESimple\mainwnd.cpp:0610	[int]   149

int CRemoteLogger::Log(const char *postion, int line, int value)
{
	char charMessage[100]; 
	sprintf(charMessage, 
		("%s:%04d\t[int]%6d"), 
		postion,
		line,
		value);
	this->Log(charMessage);
	return 0;
}

int CRemoteLogger::Log(const char *file, int line, const char *message)
{
	char charMessage[1024]; 
	sprintf(charMessage, 
		("%s:%04d\t%s"), 
		file,
		line,
		message);
	this->Log(charMessage);
	return 0;
}

int CRemoteLogger::Log(const char *fileName, int line, WCHAR *message)
{
	char charMessage[1024];
	char tempMessage[1024];

	wcstombs(tempMessage, message, sizeof(tempMessage));
	sprintf(charMessage, 
		("%s:%04d\t%s"), 
		fileName,
		line,
		tempMessage);
	this->Log(charMessage);
	return 0;
}

int CRemoteLogger::Log(char ch)

{
	char charMessage[1024];
	sprintf(charMessage, 	("%c"),		ch);
	this->Log(charMessage);
	return 0;
}
