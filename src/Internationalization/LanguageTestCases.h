// LanguageTestCases.h: interface for the LanguageTestCases class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGETESTCASES_H__23FD6465_A108_498E_A808_2E7065147ADD__INCLUDED_)
#define AFX_LANGUAGETESTCASES_H__23FD6465_A108_498E_A808_2E7065147ADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestSuite.h"
class LanguageTestCases : public TestSuite  
{
private:
	static int switchToRussia(int argc,char**argv);
	static int switchToEnglish(int argc,char**argv);
	static int switchToChinese(int argc,char**argv);
public:
	
	int run(int argc,char **argv);
	LanguageTestCases();
	virtual ~LanguageTestCases();

};

#endif // !defined(AFX_LANGUAGETESTCASES_H__23FD6465_A108_498E_A808_2E7065147ADD__INCLUDED_)
