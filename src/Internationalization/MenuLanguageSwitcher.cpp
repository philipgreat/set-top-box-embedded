// MenuLanguageSwitcher.cpp: implementation of the MenuLanguageSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MenuLanguageSwitcher.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MenuLanguageSwitcher::MenuLanguageSwitcher()
{

}

MenuLanguageSwitcher::~MenuLanguageSwitcher()
{

}

bool MenuLanguageSwitcher::switcherToLanguage(const char *languageCode)
{
	LanguageSwitcher::switcherToLanguage(languageCode);
	return true;
}
