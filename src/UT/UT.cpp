// UT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UDPClient.h"

char *test_cases[]={
		"SwitchToDVB  ",
		"SwitchToHotelPortal  ",
		"SwitchToDesktop  ",
		"SwitchToNetworkedTV  ",
		"RestartPC  ",
		"SleepPC  ",
		"UpdateAd adInfo=adinfo ",
		"UpdateMenu menuInfo=menuInfo ",
		"UpdateAdImage adId=100&imageURL=http:// ",
		"UpdateMenuItemImage menuId=100&imageURL=http ",
		"UpdateBackgroundImage url=http ",
		"SwitchOutputToDVB  ",
		"SubmitDVBStateInfo name=name&value=value ",
		"StartFunctionOnPC functionName=x ",
		"IsFunctionAvailable functionName=x ",
		"QueryPCState  ",
		"SynchronizeTime seconds=1232142",
		"SynchronizeVolume   percent=50",		
		
		NULL,
		
};

int test_all_command(int argc, char *argv[])
{

	char **p=test_cases;
	char message[1024];
	CUDPClient::InitEnv();
	CUDPClient *client;
	short port=atoi(argv[2]);
	client=new CUDPClient(argv[1],port);
	client->Connect();

	while(*p!=NULL){
		//printf("tester#brokershell: ");
		//scanf("%s",message);
		//RestartPC style=10&method=goanother
		strcpy(message,*p);
		if(strncmp(message,"exit",5)==0){
			break;
		}	

		client->Send((unsigned char *)*p,strlen(*p)+1);	
		client->Recv((unsigned char *)message,1024);
		printf("return message:%s", message);

		
		p++;
		
		
	}
	delete client;
	return 0;

}
int test_single_command(int argc, char *argv[])
{
	if(argc < 4){
		printf("usage: ut <server> <port> <message>\n");
		exit(0);
	}
	char message[1024]={0};
	CUDPClient::InitEnv();
	CUDPClient *client;
	short port=atoi(argv[2]);
	client=new CUDPClient(argv[1],port);
	client->Connect();
	strcat(message,argv[3]);

	for(int i=4;i<argc;i++){
		strcat(message," ");
		strcat(message,argv[i]);
	}
	client->Send((unsigned char *)message,strlen(message)+1);

	if(client->Recv((unsigned char *)message,1024)>0){
		printf("return message:%s\n", message);
	}else{
		printf("no respond\n");	
	}
	delete client;
	return 0;
}
int main(int argc, char* argv[])
{

	return 	test_single_command(argc,argv);
}

