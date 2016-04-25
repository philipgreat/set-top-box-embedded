// MSTBShellApp.h: interface for the MSTBShellApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTBSHELLAPP_H__CC6240D0_2DB9_4095_B820_E9A4F6BB5C8A__INCLUDED_)
#define AFX_MSTBSHELLAPP_H__CC6240D0_2DB9_4095_B820_E9A4F6BB5C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MSTBShellApp  
{
private:
	char *baseHome;
	char *updatedHome;
	char *currentHome;	
	char *upgradeURL;
public:
	int monitorProcessors();
	void end();
	int upgradeSoftware();
	static bool isProcessAlive(int pid);
	int executeTask(char *fileName,char *parameter);
	int run();
	bool config(const char *upgradeURL,
		const char* baseHome,
		const char* updatedHome);
	MSTBShellApp();
	virtual ~MSTBShellApp();

};

#endif // !defined(AFX_MSTBSHELLAPP_H__CC6240D0_2DB9_4095_B820_E9A4F6BB5C8A__INCLUDED_)
