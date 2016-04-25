// MSTBSubBroker.h: interface for the MSTBSubBroker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTBSUBBROKER_H__743428F9_23B9_48B9_9DD6_B513E758332C__INCLUDED_)
#define AFX_MSTBSUBBROKER_H__743428F9_23B9_48B9_9DD6_B513E758332C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMSTBSubBroker 
{ 
private:
	bool isStarted;
	char currentLangId[3];
public:
	virtual int SetLanguageID(const char *langId){
		currentLangId[0]=*(langId+0);
		currentLangId[1]=*(langId+1);
		currentLangId[2]=0;
		return 0;
	};
	CMSTBSubBroker()
	{		
		currentLangId[0]='z';
		currentLangId[1]='h';
		isStarted = false;
	};
	virtual int OnKey(int keyCode)=0;
	virtual int Start(){isStarted = true; return 0;};
	virtual int End()=0;
	virtual bool IsStarted(){return this->isStarted;}
	virtual int Reenter()=0;
	virtual int Leave()=0;

	virtual ~CMSTBSubBroker(){};
};

#endif // !defined(AFX_MSTBSUBBROKER_H__743428F9_23B9_48B9_9DD6_B513E758332C__INCLUDED_)
