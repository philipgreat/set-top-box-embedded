// MediaFileProcessor.h: interface for the MediaFileProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAFILEPROCESSOR_H__30B94EC4_C76B_4B15_AF82_F1A01F394120__INCLUDED_)
#define AFX_MEDIAFILEPROCESSOR_H__30B94EC4_C76B_4B15_AF82_F1A01F394120__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OfficeDocumentProcessor.h"

class MediaFileProcessor : public OfficeDocumentProcessor  
{
public:
	MediaFileProcessor();
	virtual ~MediaFileProcessor();

};

#endif // !defined(AFX_MEDIAFILEPROCESSOR_H__30B94EC4_C76B_4B15_AF82_F1A01F394120__INCLUDED_)
