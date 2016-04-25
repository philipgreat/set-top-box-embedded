// LanguageSwitcher.h: interface for the LanguageSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGESWITCHER_H__5D2709CE_B430_446D_AB61_FA44C3978D58__INCLUDED_)
#define AFX_LANGUAGESWITCHER_H__5D2709CE_B430_446D_AB61_FA44C3978D58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LanguageSwitcher  
{
private:
	char currentLanguage[32];
public:
	virtual bool switcherToLanguage(const char *languageCode);
	LanguageSwitcher();
	virtual ~LanguageSwitcher();

};

#endif // !defined(AFX_LANGUAGESWITCHER_H__5D2709CE_B430_446D_AB61_FA44C3978D58__INCLUDED_)
