// UpgradeManager.h: interface for the UpgradeManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPGRADEMANAGER_H__31BEF2AE_D744_4173_BF8A_19103EDA843D__INCLUDED_)
#define AFX_UPGRADEMANAGER_H__31BEF2AE_D744_4173_BF8A_19103EDA843D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class UpgradeManager  
{
private:
	char upgradeURL[1024];	
	char localHome[1024];
public:
	void downloadFile(char *fileName, char *rule);
	int forceDownloadFile(const char *fileName);
	int downloadNewestFile(const char*fileName);
	bool runUpgrade();
	void config(const char *url,const char*localHome);
	UpgradeManager();
	virtual ~UpgradeManager();

};

#endif // !defined(AFX_UPGRADEMANAGER_H__31BEF2AE_D744_4173_BF8A_19103EDA843D__INCLUDED_)
