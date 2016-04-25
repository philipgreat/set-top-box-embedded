// DVBCommunicatorClient.h: interface for the CDVBCommunicatorClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DVBCOMMUNICATORCLIENT_H__79E91BF3_826C_4025_821F_FAC2DB47558C__INCLUDED_)
#define AFX_DVBCOMMUNICATORCLIENT_H__79E91BF3_826C_4025_821F_FAC2DB47558C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\Common\\UDPClient.h"
class CDVBCommunicatorClient : public CUDPClient  
{
private:
	int currentSequenceNumber;
	char result[256];
public:
	int ReceiveResult();
	int SendCommand(int seqnum, char *command, char* params);
	CDVBCommunicatorClient(const char* serverName,unsigned short serverPort):
		CUDPClient(serverName,serverPort){currentSequenceNumber=0;};
	virtual ~CDVBCommunicatorClient();

};

#endif // !defined(AFX_DVBCOMMUNICATORCLIENT_H__79E91BF3_826C_4025_821F_FAC2DB47558C__INCLUDED_)
