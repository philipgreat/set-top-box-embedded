// LanguageSwitcher.cpp: implementation of the LanguageSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LanguageSwitcher.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <string.h>
LanguageSwitcher::LanguageSwitcher()
{

}

LanguageSwitcher::~LanguageSwitcher()
{

}

bool LanguageSwitcher::switcherToLanguage(const char *languageCode)
{
	strncpy(this->currentLanguage,languageCode,31);
	this->currentLanguage[31]=0;

	return true;
}
