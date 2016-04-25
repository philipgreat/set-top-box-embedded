// MenuLanguageSwitcher.h: interface for the MenuLanguageSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENULANGUAGESWITCHER_H__A4D2369F_6A6E_4F29_B16F_FAEA1DF3992E__INCLUDED_)
#define AFX_MENULANGUAGESWITCHER_H__A4D2369F_6A6E_4F29_B16F_FAEA1DF3992E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LanguageSwitcher.h"

class MenuLanguageSwitcher : public LanguageSwitcher  
{
public:
	bool switcherToLanguage(const char *languageCode);
	MenuLanguageSwitcher();
	virtual ~MenuLanguageSwitcher();

};

#endif // !defined(AFX_MENULANGUAGESWITCHER_H__A4D2369F_6A6E_4F29_B16F_FAEA1DF3992E__INCLUDED_)
