// DesktopLanguageSwitcer.h: interface for the DesktopLanguageSwitcer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESKTOPLANGUAGESWITCER_H__B9D175E9_2C88_4D67_9CCE_6ACA43CB0B24__INCLUDED_)
#define AFX_DESKTOPLANGUAGESWITCER_H__B9D175E9_2C88_4D67_9CCE_6ACA43CB0B24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "LanguageSwitcher.h"
class DesktopLanguageSwitcher : public  LanguageSwitcher
{
public:
	bool switcherToLanguage(const char *languageCode);
	DesktopLanguageSwitcher();
	virtual ~DesktopLanguageSwitcher();

};

#endif // !defined(AFX_DESKTOPLANGUAGESWITCER_H__B9D175E9_2C88_4D67_9CCE_6ACA43CB0B24__INCLUDED_)
