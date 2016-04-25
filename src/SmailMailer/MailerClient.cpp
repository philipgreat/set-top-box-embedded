// MailerClient.cpp : Implementation of CMailerClient
#include "stdafx.h"
#include "SmailMailer.h"
#include "MailerClient.h"

/////////////////////////////////////////////////////////////////////////////
// CMailerClient

HRESULT CMailerClient::QueryContextMenu(HMENU hmenu, UINT indexMenu,
								   UINT idCmdFirst, UINT idCmdLast,
								   UINT uFlags)
{
	if (!(CMF_DEFAULTONLY & uFlags))
	{
		int nCmdRegister = idCmdFirst;
		int nCmdUnregister = idCmdFirst;

		InsertMenu(hmenu, indexMenu++, MF_STRING|MF_BYPOSITION,
					nCmdRegister, _T("提取文本并发送到邮件"));

		// A successful return code should be the offset of
		// the largest command identifier assigned, plus one
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, nCmdUnregister - idCmdFirst + 1);
	}
	

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, USHORT(0));
}

HRESULT CMailerClient::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
	TCHAR szParms[MAX_PATH+6];

	// The offset will determine which option was requested:
	// 0 for Register, 1 for Unregister
	UINT idOffset = LOWORD(pici->lpVerb);


	// Embed a '/u' for the Unregister command into the
	// parameters, and always put quotes around the path
	// so spaces in the path won't be a problem
	if (1 == idOffset||0 == idOffset)
	{

#if 1		
		CUDPClient::InitEnv();
		CUDPClient  udpclient("127.0.0.1",8800);
		udpclient.Connect();
		lstrcpy(szParms, _T("10024@processDocument fileName="));
		lstrcat(szParms, m_szFile);
		udpclient.Send((BYTE*)szParms,strlen(szParms));
#endif
	}



	return S_OK;
}

HRESULT CMailerClient::GetCommandString(UINT idCmd, UINT uFlags, UINT* pwReserved,
								   LPSTR pszName, UINT cchMax)
{
	if (uFlags & GCS_HELPTEXT)
	{
		// Windows NT will ask for Unicode strings
		switch(idCmd)
		{
		case 0:
			if (uFlags & GCS_VERBA)
				lstrcpyn(pszName, "Perform COM registration for this module", cchMax);
			else
				lstrcpynW((LPWSTR)pszName, L"Perform COM registration for this module", cchMax);
			break;
		case 1:
			if (uFlags & GCS_VERBA)
				lstrcpyn(pszName, "Perform COM unregistration for this module", cchMax);
			else
				lstrcpynW((LPWSTR)pszName, L"Perform COM unregistration for this module", cchMax);
			break;
		default:
			break;
		}

		return S_OK;
	}

	return E_FAIL;
}

HRESULT CMailerClient::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
{
	if (lpdobj == NULL)
		return E_INVALIDARG;

	// The file can be referenced through the STGMEDIUM structure
	// that is retrievable through the IDataObject pointer, and
	// DragQueryFile can then be used to retrieve the file name.
	STGMEDIUM medium;
	FORMATETC fe = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	HRESULT hr = lpdobj->GetData(&fe, &medium);
	if (FAILED(hr))
		return E_INVALIDARG;

	DragQueryFile(reinterpret_cast<HDROP>(medium.hGlobal), 0,
					m_szFile, MAX_PATH);

	ReleaseStgMedium(&medium);
	return hr;
}
