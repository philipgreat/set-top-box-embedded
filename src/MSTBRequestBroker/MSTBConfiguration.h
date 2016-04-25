// MSTBConfiguration.h: interface for the CMSTBConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSTBCONFIGURATION_H__13E9EB09_2D1A_4DEB_8677_358B7F52F2B3__INCLUDED_)
#define AFX_MSTBCONFIGURATION_H__13E9EB09_2D1A_4DEB_8677_358B7F52F2B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\common\\STBConfiguration.h"
class CMSTBConfiguration : public CSTBConfiguration  
{
public:
	char * GetNetworkedTVURL();
	char * GetHotelPortalURL();
	char * GetBrowserPath();
	char * GetPlayerPath();

	CMSTBConfiguration();
	virtual ~CMSTBConfiguration();

};

#endif // !defined(AFX_MSTBCONFIGURATION_H__13E9EB09_2D1A_4DEB_8677_358B7F52F2B3__INCLUDED_)
