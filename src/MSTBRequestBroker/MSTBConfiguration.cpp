// MSTBConfiguration.cpp: implementation of the CMSTBConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSTBConfiguration.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSTBConfiguration::CMSTBConfiguration()
{

}

CMSTBConfiguration::~CMSTBConfiguration()
{

}

char* CMSTBConfiguration::GetPlayerPath()
{
	return this->GetValue("Application.PlayerPath");
}

char * CMSTBConfiguration::GetBrowserPath()
{
	return this->GetValue("Application.BrowserPath");
}



char* CMSTBConfiguration::GetHotelPortalURL()
{
	return this->GetValue("MSTB.HotelPortalURL");
}

char* CMSTBConfiguration::GetNetworkedTVURL()
{
	return this->GetValue("MSTB.NetworkedTVURL");

}
/*
use this ini file like a sample to apply

MSTB.HotelPortalURL=http://10.130.36.45:8080/hotel/index.htm
MSTB.NetworkedTVURL=http://10.130.36.45:8080/vod/index.htm
Application.BrowserPath=d:\settopbox\STBBrowser.exe
Application.PlayerPath=d:\settopbox\STBPlayer.exe

*/