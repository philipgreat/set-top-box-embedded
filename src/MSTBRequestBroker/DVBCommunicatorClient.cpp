// DVBCommunicatorClient.cpp: implementation of the CDVBCommunicatorClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DVBCommunicatorClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CDVBCommunicatorClient::~CDVBCommunicatorClient()
{

}

int CDVBCommunicatorClient::SendCommand(int seqnum, char *command, char *params)
{
	char buffer[1024*8];
	sprintf(buffer,"%u@%s %s",seqnum,command,params);
	return this->Send((BYTE*)buffer,strlen(buffer)+1);
}

int CDVBCommunicatorClient::ReceiveResult()
{
	char buffer[1024*8];
	int ret = 0;
	ret = this->Recv((BYTE*)buffer,1024*8);
	
	if(ret>0){
		//parse them into structers
		return ret;
	}else{
		return 0;
	}
	
}
