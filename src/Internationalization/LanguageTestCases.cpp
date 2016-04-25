// LanguageTestCases.cpp: implementation of the LanguageTestCases class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LanguageTestCases.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "DesktopLanguageSwitcer.h"
LanguageTestCases::LanguageTestCases()
{

}

LanguageTestCases::~LanguageTestCases()
{
		
}

int LanguageTestCases::run(int argc, char **argv)
{
	int ret = 0;
	printf("--------------------------------------------------------------\n");
	printf("%s@%s,%s\n",__FILE__,__TIME__,__DATE__);
	printf("--------------------------------------------------------------\n");	
	T(LanguageTestCases::switchToChinese);
	T(LanguageTestCases::switchToEnglish);
	T(LanguageTestCases::switchToRussia);
	ret = TestSuite::run(argc,argv);
	return ret;
}

int LanguageTestCases::switchToChinese(int argc, char **argv)
{
	bool success = false;
	DesktopLanguageSwitcher switcer;
	success = switcer.switcherToLanguage("zh");
	return success-true;
}

int LanguageTestCases::switchToEnglish(int argc, char **argv)
{
	bool success = false;
	DesktopLanguageSwitcher switcer;
	success = switcer.switcherToLanguage("en");
	return success-true;

}

int LanguageTestCases::switchToRussia(int argc, char **argv)
{
	bool success = false;
	DesktopLanguageSwitcher switcer;
	success = switcer.switcherToLanguage("ru");
	return success-true;
}
