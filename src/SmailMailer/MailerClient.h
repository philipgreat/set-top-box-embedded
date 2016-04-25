// MailerClient.h : Declaration of the CMailerClient

#ifndef __MAILERCLIENT_H_
#define __MAILERCLIENT_H_

#include "resource.h"       // main symbols
#include "UDPClient.h"
/////////////////////////////////////////////////////////////////////////////
// CMailerClient
class ATL_NO_VTABLE CMailerClient : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMailerClient, &CLSID_MailerClient>,
	public IDispatchImpl<IMailerClient, &IID_IMailerClient, &LIBID_SMAILMAILERLib>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CMailerClient()
	{
	}
	TCHAR	m_szFile[MAX_PATH];
DECLARE_REGISTRY_RESOURCEID(IDR_MAILERCLIENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMailerClient)
	COM_INTERFACE_ENTRY(IMailerClient)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)		//IShellExtInit接口
	COM_INTERFACE_ENTRY(IContextMenu)		//IContextMenu接口

END_COM_MAP()

	STDMETHOD(GetCommandString)(UINT idCmd, UINT uFlags, UINT *pwReserved, 
								LPSTR pszName, UINT cchMax);
	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO pici);
	STDMETHOD(QueryContextMenu)(HMENU hmenu, UINT indexMenu, 
								UINT idCmdFirst, UINT idCmdLast, 
								UINT uFlags);

	// IShellExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, 
							HKEY hkeyProgID);



// IMailerClient
public:
};

#endif //__MAILERCLIENT_H_
