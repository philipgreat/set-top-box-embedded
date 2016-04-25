// MSTBShellApp.cpp: implementation of the MSTBShellApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSTBShellApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "windowexception.h"
#include <stdlib.h>
#include "UpgradeManager.h"
#include <psapi.h>
#pragma comment(lib,"psapi")


typedef struct{
	int processId;
	char *processName;
}process_t;
static process_t processList[]={
	{0,"MSTBRequestBroker.exe"},
		//	{0,"MSTBBooter.exe"},
	{0,"DVBComm.exe"},
	{0,NULL},
};

static bool continueToRun = true;
static char *baseHomePath =NULL;

static BOOL SetPrivilege(
						 HANDLE hToken,          // token handle
						 LPCTSTR Privilege,      // Privilege to enable/disable
						 BOOL bEnablePrivilege   // TRUE to enable.  FALSE to disable
						 )
{
    TOKEN_PRIVILEGES tp;
    LUID luid;
    TOKEN_PRIVILEGES tpPrevious;
    DWORD cbPrevious=sizeof(TOKEN_PRIVILEGES);
	
    if(!LookupPrivilegeValue( NULL, Privilege, &luid )) return FALSE;
	
    // 
    // first pass.  get current privilege setting
    // 
    tp.PrivilegeCount           = 1;
    tp.Privileges[0].Luid       = luid;
    tp.Privileges[0].Attributes = 0;
	
    AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		&tpPrevious,
		&cbPrevious
		);
	
    if (GetLastError() != ERROR_SUCCESS) return FALSE;
	
    // 
    // second pass.  set privilege based on previous setting
    // 
    tpPrevious.PrivilegeCount       = 1;
    tpPrevious.Privileges[0].Luid   = luid;
	
    if(bEnablePrivilege) {
        tpPrevious.Privileges[0].Attributes |= (SE_PRIVILEGE_ENABLED);
    }
    else {
        tpPrevious.Privileges[0].Attributes ^= (SE_PRIVILEGE_ENABLED &
            tpPrevious.Privileges[0].Attributes);
    }
	
    AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tpPrevious,
		cbPrevious,
		NULL,
		NULL
		);
	
    if (GetLastError() != ERROR_SUCCESS) return FALSE;
	
    return TRUE;
}



static int KillProcess(int processId)
{
	HANDLE hProcess;
	// Get the actual priority class.
	hProcess = OpenProcess (PROCESS_ALL_ACCESS,
		FALSE,
		processId);
	if(hProcess){
		::TerminateProcess(hProcess,0);
		CloseHandle(hProcess);
		return 0;
	}else{
		return 1;
	}
}

static DWORD ExecuteFileEx(LPCTSTR startDirectory,LPCTSTR fileName,LPTSTR cmdLine)
{
	STARTUPINFO si;
	DWORD pid = 0;
    PROCESS_INFORMATION pi;
    char commandLine[2048];
	*commandLine=' ';
	strncpy(commandLine+1,cmdLine,2040);
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
	BOOL ret = CreateProcess(
		fileName, 
		commandLine, 
		NULL, 
		NULL, 
		FALSE, 
		0, 
		NULL, 
		startDirectory, 
		&si, 
		&pi);
	//WaitForSingleObject( pi.hProcess, INFINITE );
	return pi.dwProcessId;
}
LONG __stdcall FirstFilter( EXCEPTION_POINTERS* pep )
{
	printf( "居然崩溃了!\n" );
	//
	process_t *p=processList;
	while((p->processName)!=NULL)
	{
		KillProcess(p->processId);
		p++;
	}
	::Sleep(2000);
	
	char filePath[MAX_PATH];	
	if(baseHomePath)
	{
		sprintf(filePath,"%s\\%s",baseHomePath,"MSTBShell.exe");
		ExecuteFileEx(".\\",filePath," ");
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL WINAPI HandlerRoutine(DWORD event   )
{
	continueToRun = false;
    switch(event)
    {
    case CTRL_C_EVENT:
        break;
		
    case CTRL_BREAK_EVENT:
        break;
		
    case CTRL_CLOSE_EVENT:
        break;
		
    case CTRL_LOGOFF_EVENT:
        break;
		
    case CTRL_SHUTDOWN_EVENT:
        break;
    }
	
    return TRUE;
}

MSTBShellApp::MSTBShellApp()
{
	baseHome	= new char[MAX_PATH];
	updatedHome = new char[MAX_PATH];	
	upgradeURL	= new char[MAX_PATH];
	currentHome = baseHome;
	baseHomePath= baseHome;
	::SetUnhandledExceptionFilter(FirstFilter);
	::SetConsoleCtrlHandler(HandlerRoutine,1);
}

MSTBShellApp::~MSTBShellApp()
{
	delete baseHome;
	delete updatedHome;
	delete upgradeURL;
}

bool MSTBShellApp::config(const char *upgradeURL,
						  const char* baseHome,
						  const char* updatedHome)
{
	strncpy(this->baseHome,baseHome,MAX_PATH);
	strncpy(this->updatedHome,updatedHome,MAX_PATH);
	strncpy(this->upgradeURL,upgradeURL,MAX_PATH);
	return 0;
}
/********************************************************************\
程序在部署的时候有一个基本目录,MSTBShell就是从该目录启动的,程序启动以
后,将检查是否有新的文件,如果更新过程完全成功,则系统把目录切换到新的目录
运行,否则使用最初部署的程序继续使用.
\********************************************************************/
int MSTBShellApp::run()
{
	//更新软件

#if 1 	
	if(this->upgradeSoftware())
	{
		//运行目录切换到新的目录
		this->currentHome = this->updatedHome;
	}
#endif
	//启动监控线程
	this->monitorProcessors();
	return 0;//程序不会到这儿.
	
}
int MSTBShellApp::executeTask(char *fileName, char *parameter)
{
	char filePath[MAX_PATH];	
	sprintf(filePath,"%s\\%s",this->currentHome,fileName);
	return  ExecuteFileEx(this->currentHome,filePath,parameter);
	
}
#ifdef _WIN2000
bool MSTBShellApp::isProcessAlive(int processId)
{
	
	HANDLE hProcess;
	HANDLE hToken;
	
    if(!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &hToken))
    {
        if (GetLastError() == ERROR_NO_TOKEN)
        {
            if (!ImpersonateSelf(SecurityImpersonation))
				return false;
			
            if(!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &hToken))
			{
                printf("OpenThreadToken\n");
				return false;
            }
		}else{
            return false;
		}
	}
	
    // enable SeDebugPrivilege
    if(!SetPrivilege(hToken, SE_DEBUG_NAME, TRUE))
    {
        printf("SetPrivilege\n");
        CloseHandle(hToken);
        return false;
    }
	
	hProcess = OpenProcess (
		PROCESS_ALL_ACCESS,
		FALSE,
		processId);
	if(hProcess>0){
		printf("found the process h = %u id = %u ok!\n",hProcess,processId);
		
		CloseHandle(hProcess);
		return true;	
	}else{
		//throw WindowsException("isProcessAlive");
		return false;
	}
}

#else

bool MSTBShellApp::isProcessAlive(int processId)
{
	bool ret = false;
	DWORD processes[1024], neededSize, processesCount;
    if ( !EnumProcesses( processes, sizeof(processes), &neededSize ) )
        return 1; 
    processesCount = neededSize / sizeof(DWORD);	
	
    for (DWORD i = 0; i < processesCount; i++ )
	{	
		if(processes[i] ==(DWORD) processId){
			ret = true;
			break;
		}				
	}
	return ret;

}

#endif

/***************************************************************\
成功更新后把currentHome设置为upgradeHome
首先获得更新列表，然后按照规则进行更新
规则包括：'最新'，'强制'
如果是最新，则，程序执行版本号检查，如果有更新然后更新本地程序
如果是强制，则，程序不检查版本号，直接从远程服务器更新
注意：强制更新发生在发现新的版本并非最好的时候，要想回到以前的版本，则启用
强制更新选项
\***************************************************************/
int MSTBShellApp::upgradeSoftware()
{
	bool result;
	UpgradeManager manager;
	manager.config(this->upgradeURL,this->updatedHome);
	result = manager.runUpgrade();
	return result;
}

void MSTBShellApp::end()
{
	process_t *p=processList;
	while((p->processName)!=NULL)
	{
		if(!KillProcess(p->processId)){
			//throw Exception("kill process failed");
		}
		p++;
	}
	
}

int MSTBShellApp::monitorProcessors()
{
	process_t *p=processList;
	int runCounter = 0;
	while((p->processName)!=NULL)
	{
		p->processId = executeTask(p->processName,"");
		Sleep(1000);
		p++;
	}
	
	while(continueToRun)
	{
		p=processList;
		while((p->processName)!=NULL)
		{
			if(!isProcessAlive(p->processId)){				
				p->processId = executeTask(p->processName,"");				
			}
			p++;
		}
		runCounter++;
		Sleep(1000);
		//if(runCounter>5) throw Exception("Unhandled!");
		//用于崩溃测试
	}
	this->end();
	return 0;
}
