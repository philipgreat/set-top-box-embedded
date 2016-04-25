// DesktopLanguageSwitcer.cpp: implementation of the DesktopLanguageSwitcer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DesktopLanguageSwitcer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DesktopLanguageSwitcher::DesktopLanguageSwitcher()
{

}

DesktopLanguageSwitcher::~DesktopLanguageSwitcher()
{

}
static char *langmap[]={
	"zh",
	"zh",
	"en",
	"ru",
	"fr",
	"de",
	"it",
	"ar",
	"pu",
	"es",
	NULL
};
/*

语言	值	说明
中文	1	zh
英文	2	en
俄文	3	ru
法文	4	暂不可用fr
德文	5	暂不可用de
意文	6	暂不可用it
阿拉伯文	7	暂不可用ar

*/
bool DesktopLanguageSwitcher::switcherToLanguage(const char *languageCode)
{
	LanguageSwitcher::switcherToLanguage(languageCode);
	//


	return true;
}
