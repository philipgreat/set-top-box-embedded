// PowerPointProcessor.h: interface for the PowerPointProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERPOINTPROCESSOR_H__EB4C2A32_AD09_4964_819E_2BA02BB09CFC__INCLUDED_)
#define AFX_POWERPOINTPROCESSOR_H__EB4C2A32_AD09_4964_819E_2BA02BB09CFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OfficeDocumentProcessor.h"


#import "MSPPT.OLB" 
using namespace PowerPoint;

class PowerPointProcessor : public OfficeDocumentProcessor
{
private:
	_ApplicationPtr app;

public:
	int processDocument(const char *fullDocumentPath);
	PowerPointProcessor();
	virtual ~PowerPointProcessor();

};

#endif // !defined(AFX_POWERPOINTPROCESSOR_H__EB4C2A32_AD09_4964_819E_2BA02BB09CFC__INCLUDED_)
