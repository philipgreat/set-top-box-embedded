// MSTBRequestBrokerApp.cpp: implementation of the MSTBRequestBrokerApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSTBRequestBrokerApp.h"
#include "SystemTaskExecutor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "DVBCommunicatorClient.h"

#define ISFUNCTION(x)	strncmp((x),this->command,strlen((x))+1)==0
#define EQUALS(x,y)		strncmp((x),y,strlen((x))+1)==0


static  int counter = 0;


static  int SendCommandToDVBComm(char *cmd, char* param)
{
	CDVBCommunicatorClient client("127.0.0.1",5212);
	client.Connect();
	client.SendCommand(counter,cmd,param);
	client.ReceiveResult();
	return 0;
}

CMSTBRequestBrokerApp::CMSTBRequestBrokerApp()
{
	switcher=new  CMSTBFunctionSwitcher;
	externalCommandSequenceNumber = 0;
	char *p=::getenv("SETTOPBOX_HOME");
	if(p!=NULL){
		::SetCurrentDirectory(p);	
	}

}

CMSTBRequestBrokerApp::~CMSTBRequestBrokerApp()
{
	delete switcher;
}

bool CMSTBRequestBrokerApp::SynchronizeVolume(int percent)
{
	CSystemTaskExecutor::SetSystemVolume(percent);
	return true;
}

bool CMSTBRequestBrokerApp::SynchronizeTime(int absoluteSecondsFrom1970)
{
	return CSystemTaskExecutor::SetSystemTime(absoluteSecondsFrom1970)>0;
}

int CMSTBRequestBrokerApp::QueryPCState()
{
	//TODO: delete this after released
	return 0;
}
/*

注[1]：PC状态为如下几个值之一
状态	值	说明
不可用	0	
可用	1	

*/
bool CMSTBRequestBrokerApp::IsFunctionAvailable(char *functionName)
{
	bool ret = false;
	printf("!%s\n",functionName);
	if(EQUALS("\"networkedtv\"",functionName)){
		ret = 0;
		goto end;
	}
	if(EQUALS("\"hotelportal\"",functionName)){		
		ret = 0;
		goto end;
	}

	if(EQUALS("\"pcservice\"",functionName)){		
		ret = 0;
		goto end;
	}
end:
	return ret;
}

bool CMSTBRequestBrokerApp::StartFunctionOnPC(char *functionName)
{
	bool ret = false;
	printf("!%s\n",functionName);
	if(EQUALS("\"networkedtv\"",functionName)){
		ret = this->SwitchToNetworkedTV();
		goto end;
	}
	if(EQUALS("\"hotelportal\"",functionName)){		
		ret = this->SwitchToHotelPortal();
		goto end;
	}

	if(EQUALS("\"pcservice\"",functionName)){		
		ret = this->SwitchToDesktop();
		goto end;
	}
end:
	return ret;
}

bool CMSTBRequestBrokerApp::SubmitDVBStateInfo(char *name, char *value)
{
	//TODO
	return true;
}

bool CMSTBRequestBrokerApp::SwitchOutputToDVB()
{
	return switcher->SwitchToDVB();
}

bool CMSTBRequestBrokerApp::UpdateBackgroundImage(char *url)
{
	return true;
}

bool CMSTBRequestBrokerApp::UpdateMenuItemImage(char *menuId, char *imageURL)
{
	return true;
}

bool CMSTBRequestBrokerApp::UpdateAdImage(char *adId, char *imageURL)
{
	return true;
}

bool CMSTBRequestBrokerApp::UpdateMenu(char *menuInfo)
{
	return true;
}

bool CMSTBRequestBrokerApp::UpdateAd(char *adInfo)
{
	//send ad info
	return true;
}

bool CMSTBRequestBrokerApp::SleepPC()
{
	CSystemTaskExecutor::SleepPC();
	return true;
}

bool CMSTBRequestBrokerApp::RestartPC()
{
	CSystemTaskExecutor::RestartPC();
	return true;
}

bool CMSTBRequestBrokerApp::ReceiveMessage(char *message, int messageLength)
{
	return true;
}
/*
	parse a message like this form:
    'RestartPC style=10&method=goanother'

*/
bool CMSTBRequestBrokerApp::ParseMessage(char *message, int messageLength)
{
	
	int len=strlen(message)+1;
	char *p = NULL;	

	char *head = new char[len];
	int  commandLength = 0;
	int  seqnumberLength = 0;

	this->externalCommandSequenceNumber = 0;
	memset(this->command,0,sizeof(this->command));

	p = head ;
	strncpy(head, message, len);
	while(*p!='@'&&p-head<len)
	{
		seqnumberLength++;
		p++;	
	}
	
	if(p-head + 1>len){
		strncpy(this->command,head,len);
		strncpy(this->returnValue,head,len);

		goto end;
	}

	*p=0;

	this->externalCommandSequenceNumber = atol(head);
	commandLength = 0;
	while(*p!=' '&&p-head<len)
	{
		commandLength++;
		p++;
	}
	if(p-head<len){
		*p=0;
	}
	if(commandLength>0){
		
		strncpy(this->command,head+seqnumberLength+1,commandLength);
	}
	if(p-head<len){

		*p=0;
		//printf("%s\n",p+1);
		this->parameters.Parse(p+1);
		//this->parameters.Report();
	}
end:
	delete head;
	return true;
}
#if 0
#endif
bool CMSTBRequestBrokerApp::SwitchToNetworkedTV()
{
	switcher->SwitchToNetworkedTV();
	return true;
}

bool CMSTBRequestBrokerApp::SwitchToDesktop()
{
	switcher->SwitchToDesktop();
	return true;
}

bool CMSTBRequestBrokerApp::SwitchToHotelPortal()
{
	switcher->SwitchToHotelPortal();
	return true; 
}

bool CMSTBRequestBrokerApp::SwitchToDVB()
{
	//printf("in %s %s \n",__FILE__,"SwitchToDVB");
	switcher->SwitchToDVB();

	return true;
}
/*
	int Execute();
	bool SwitchToDVB();
	bool SwitchToHotelPortal();
	bool SwitchToDesktop();
	bool SwitchToNetworkedTV();
	bool ParseMessage();
	bool ReceiveMessage(char *message,int messageLength);
	bool ParseMessage(char *message,int messageLength);
	bool RestartPC();
	bool SleepPC();
	bool UpdateAd(char *adInfo);
	bool UpdateMenu(char *menuInfo);
	bool UpdateAdImage(char *adId, char *imageURL);
	bool UpdateMenuItemImage(char *menuId,char *imageURL);
	bool UpdateBackgroundImage(char *url);
	bool SwitchOutputToDVB();
	bool SubmitDVBStateInfo(char *name,char *value);
	bool StartFunctionOnPC(char *functionName);
	bool IsFunctionAvailable(char *functionName);
	int QueryPCState();
	bool SynchronizeTime(int absoluteSecondsFrom1970);
	bool SynchronizeVolume(int percent);
*/

int CMSTBRequestBrokerApp::Execute()
{

	bool ret = false;
	int  state = 0;
	bool isIntegerReturned = false;


	printf("command = %30s\t",this->command);
	if(this->externalCommandSequenceNumber==0){
		goto exit;
	}
	if(ISFUNCTION("SwitchToDVB")){		
		ret = this->SwitchToDVB();
		goto end;
	}
	if(ISFUNCTION("SwitchToHotelPortal")){		
		ret = this->SwitchToHotelPortal();
		goto end;
	}
	if(ISFUNCTION("SwitchToDesktop")){		
		ret = this->SwitchToDesktop();
		goto end;
	}
	if(ISFUNCTION("SwitchToNetworkedTV")){		
		ret = this->SwitchToNetworkedTV();
		goto end;
	}
	if(ISFUNCTION("SetLanguageID")){	
		char *langIdStr=parameters.GetValue("LanguageID");
		if(langIdStr!=NULL){
			long langId = atol(langIdStr);
			ret = this->SetLanguageID(langId);
		}		
		goto end;
	}
	/*
	if(ISFUNCTION("ReceiveMessage")){		
		this->SwitchToDVB();
		goto end;
	}
	*/
	if(ISFUNCTION("RestartPC")){		
		ret = this->RestartPC();
		goto end;
	}
	if(ISFUNCTION("SleepPC")){		
		ret = this->SleepPC();
		goto end;
	}
	if(ISFUNCTION("UpdateAd")){		
		char *adInfo=parameters.GetValue("adInfo");
		ret = this->UpdateAd(adInfo);
		goto end;
	}
	if(ISFUNCTION("UpdateMenu")){	
		char *menuInfo=parameters.GetValue("menuInfo");
		ret = this->UpdateMenu(menuInfo);
		goto end;
	}
	if(ISFUNCTION("UpdateAdImage")){		
		char *adId=parameters.GetValue("adId");
		char *imageURL=parameters.GetValue("imageURL");
		ret = this->UpdateAdImage(adId,imageURL);
		goto end;
	}
	if(ISFUNCTION("UpdateMenuItemImage")){		
		char *menuId=parameters.GetValue("menuId");
		char *imageURL=parameters.GetValue("imageURL");

		ret = this->UpdateMenuItemImage(menuId,imageURL);
		goto end;
	}
	if(ISFUNCTION("UpdateBackgroundImage")){	
		char *url=parameters.GetValue("url");
		ret = this->UpdateBackgroundImage(url);
		goto end;
	}
	if(ISFUNCTION("SwitchOutputToDVB")){		
		ret = this->SwitchOutputToDVB();
		goto end;
	}
	if(ISFUNCTION("SwitchOutputToPC")){		
		ret = this->SwitchOutputToPC();
		goto end;
	}
	if(ISFUNCTION("SubmitDVBStateInfo")){	
		char *name=parameters.GetValue("name");
		char *value=parameters.GetValue("value");
		ret = this->SubmitDVBStateInfo(name,value);
		goto end;
	}
	if(ISFUNCTION("StartFunctionOnPC")){	
		char *functioName=parameters.GetValue("functionName");
		//TODO: delete this after released
		ret = this->StartFunctionOnPC(functioName);
		goto end;
	}
	if(ISFUNCTION("IsFunctionAvailable")){	
		char *functioName=parameters.GetValue("functionName");
		ret = this->IsFunctionAvailable(functioName);
		goto end;
	}
	if(ISFUNCTION("QueryFunctionAvailable")){	
		char *functioName=parameters.GetValue("functionName");
		//todo 
		state = this->QueryFunctionAvailable(functioName);
		isIntegerReturned=true;
		goto end;
	}	
	if(ISFUNCTION("QueryFunctionStartup")){	
		char *functioName=parameters.GetValue("functionName");
		//todo 
		state = this->QueryFunctionStartup(functioName);
		isIntegerReturned=true;
		goto end;
	}
	if(ISFUNCTION("QueryPCState")){		
		state = this->QueryPCState();
		isIntegerReturned=true;
		goto end;
	}
	if(ISFUNCTION("SynchronizeTime")){	
		char *secondsString=parameters.GetValue("seconds");
		if(secondsString!=NULL){
			long seconds = atol(secondsString);
			ret = this->SynchronizeTime(seconds);
		}
		goto end;
	}	
	if(ISFUNCTION("SendKey")){	
		char *keyCodeString=parameters.GetValue("keyCode");
		if(keyCodeString!=NULL){
			long keyCode = atol(keyCodeString);
			ret = (this->SendKey(keyCode)>0);
		}
		goto end;
	}
	if(ISFUNCTION("SynchronizeVolume")){		
		char *volumePercentString=parameters.GetValue("percent");
		long percent = atol(volumePercentString);		
		ret = this->SynchronizeVolume(percent);
		goto end;
	}
	//if it is int value returned;
	//todo

end:
	if(isIntegerReturned){
		sprintf(this->returnValue,"%d@%s=%d",
			this->externalCommandSequenceNumber,
			this->command,
			state);
		
	}else{
		sprintf(this->returnValue,"%d@%s=%s",
			this->externalCommandSequenceNumber,
			this->command,
			ret?"true":"false");
	}

	printf("%s\n",this->returnValue);
	counter++;
exit:
	return ret;
}


int CMSTBRequestBrokerApp::SetReturnValue(const char *returnDescription)
{
	memcpy(this->returnValue,returnDescription,256);
	return 0;
}

char * CMSTBRequestBrokerApp::GetReturnValue()
{
	return this->returnValue;
}

int CMSTBRequestBrokerApp::SendKey(int key)
{
	return this->switcher->SendKey(key);
}

bool CMSTBRequestBrokerApp::SwitchOutputToPC()
{
	
	return this->switcher->SwitchToPC();;
}
static char *langmap[]={
	"zh",
	"zh",
	"en",
	"ru",
	"fr",
	"de",
	"it",
	"ar",
	"pu",
	"es",
	NULL
};
/*

语言	值	说明
中文	1	
英文	2	
俄文	3	
法文	4	暂不可用
德文	5	暂不可用
意文	6	暂不可用
阿拉伯文	7	暂不可用

*/
bool CMSTBRequestBrokerApp::SetLanguageID(int LanguageID)
{
	if(LanguageID<10){
		this->switcher->SetLanguageId(*(langmap+LanguageID));
	}
	return true;	
}

int CMSTBRequestBrokerApp::QueryFunctionAvailable(char *funcitonName)
{

	int ret = 0;
	if(ISFUNCTION("networkedtv")){		
		ret = 0;//TODO: add this
		goto end;
	}
	if(ISFUNCTION("hotelportal")){		
		ret = 0;//TODO: add this
		goto end;
	}
	if(ISFUNCTION("pcservice")){		
		ret = true;
		goto end;
	}
end:
	return ret;

}

int CMSTBRequestBrokerApp::QueryFunctionStartup(char *functionName)
{
	int ret = 0;
	if(EQUALS("\"networkedtv\"",functionName)){		
		ret = 0;//TODO: add this
		goto end;
	}
	if(EQUALS("\"hotelportal\"",functionName)){		
		ret = 0;//TODO: add this
		goto end;
	}
	if(EQUALS("\"pcservice\"",functionName)){		
		ret = 0;
		goto end;
	}
end:
	return ret;

}
