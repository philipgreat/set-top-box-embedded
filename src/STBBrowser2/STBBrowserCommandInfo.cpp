// STBBrowserCommandInfo.cpp: implementation of the CSTBBrowserCommandInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "STBBrowser2.h"
#include "STBBrowserCommandInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSTBBrowserCommandInfo::CSTBBrowserCommandInfo()
{
	this->mode = 0;
}

CSTBBrowserCommandInfo::~CSTBBrowserCommandInfo()
{

}

void CSTBBrowserCommandInfo::ParseParam(const TCHAR *pszParam, BOOL bFlag, BOOL bLast)
{

	if(bFlag){
		if(	*pszParam=='n'){
			this->mode = STB_MODE_NETWORKEDTV;
		}
		if(	*pszParam=='h'){
			this->mode = STB_MODE_HOTELPORTAL;
		}
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast ) ;
	
}

int CSTBBrowserCommandInfo::GetMode()const
{
	return this->mode;
}
