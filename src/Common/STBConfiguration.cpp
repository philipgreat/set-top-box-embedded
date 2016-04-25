// STBConfiguration.cpp: implementation of the CSTBConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#include "STBConfiguration.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef _WINDOWS_
	#ifdef _WIN32_WCE
		#define INI_FILE	("\\hard disk\\settopbox\\stbapplication.ini")
	#else
		#define INI_FILE	("d:\\settopbox\\stbapplication.ini")
	#endif
#else
	#define INI_FILE	("/home/suddy/stbapplication.ini")
#endif
//#define INI_FILE	(L"\\storage card\\stbapplication.ini")
//stbapplication.ini

CSTBConfiguration::CSTBConfiguration()
{
	templistCount=0;
	this->Load();	
}

CSTBConfiguration::~CSTBConfiguration()
{
	this->Save();
}

int CSTBConfiguration::Load()
{
	//params.Clear();
	params.Load(INI_FILE);	
	return 0;
}

int CSTBConfiguration::Save()
{
	params.Save(INI_FILE);
	return 0;
}

char* CSTBConfiguration::GetValue(const char *key)
{
	
	return params.GetValue(key);
}

char* CSTBConfiguration::GetCWProviderURL()
{
	return this->GetValue("CWService.ProviderURL");
}

void CSTBConfiguration::Report()
{
	params.Report();
}


int CSTBConfiguration::Parse(const char *data)
{	
	return params.Parse(data);
}

int CSTBConfiguration::SetValue(const char *key, const char *value)
{
	return params.AddParameter(key,value);
}

char* CSTBConfiguration::GetUsername()
{
	return this->GetValue("User.Name");
}

char* CSTBConfiguration::GetPassword()
{
	return this->GetValue("User.Pass");
}

void CSTBConfiguration::SaveLastViewed(const char *url)
{
	this->SetValue("User.LastView",url);
}

char* CSTBConfiguration::GetLastViewURL()
{
	return this->GetValue("User.LastView");
}

char* CSTBConfiguration::GetHomePage() 
{
	return this->GetValue("User.HomePage");
}

char* CSTBConfiguration::GetCWServiceProviderURL() 
{
	return this->GetValue("CWService.ProviderURL");
}


