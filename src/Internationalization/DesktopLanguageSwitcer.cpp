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

����	ֵ	˵��
����	1	zh
Ӣ��	2	en
����	3	ru
����	4	�ݲ�����fr
����	5	�ݲ�����de
����	6	�ݲ�����it
��������	7	�ݲ�����ar

*/
bool DesktopLanguageSwitcher::switcherToLanguage(const char *languageCode)
{
	LanguageSwitcher::switcherToLanguage(languageCode);
	//


	return true;
}
