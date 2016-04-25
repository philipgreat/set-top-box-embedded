// STBBrowserCommandInfo.h: interface for the CSTBBrowserCommandInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STBBROWSERCOMMANDINFO_H__9C42BAB6_4871_4F41_89DC_E50F36369119__INCLUDED_)
#define AFX_STBBROWSERCOMMANDINFO_H__9C42BAB6_4871_4F41_89DC_E50F36369119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
class CSTBBrowserCommandInfo : public CCommandLineInfo  
{
private:
	int mode;
public:
	int GetMode()const;
	void ParseParam(const TCHAR* pszParam,BOOL bFlag, BOOL bLast);

	CSTBBrowserCommandInfo();
	virtual ~CSTBBrowserCommandInfo();

};

#endif // !defined(AFX_STBBROWSERCOMMANDINFO_H__9C42BAB6_4871_4F41_89DC_E50F36369119__INCLUDED_)
