/////////////////////////////////////////////////////////////////////////
// FileName: ReceiveSetting.cpp
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReceiveSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////

struct StReceivePara
{
	CString m_strSendFile;
	//
	DWORD   m_dwSrcIP;
	UINT    m_nSrcPort;

	UINT    m_nLocalPort;

	StReceivePara()
	{
		m_dwSrcIP    = 0x7F000001;
		m_nSrcPort   = 80;
		m_nLocalPort = 90;
	}
};

static StReceivePara g_StReceivePara;

BOOL RP_ReadProfile()
{
	RP_SetSrcIP((BOOL)GetPrivateProfileInt(NET_SETTING_SEC_NAME, NET_SRC_IP, g_StReceivePara.m_dwSrcIP, APP_INI_FILE_NAME));
	RP_SetSrcPort((BOOL)GetPrivateProfileInt(NET_SETTING_SEC_NAME, NET_SRC_PORT, g_StReceivePara.m_nSrcPort, APP_INI_FILE_NAME));
	RP_SetLocalPort((BOOL)GetPrivateProfileInt(NET_SETTING_SEC_NAME, NET_LOCAL_PORT, g_StReceivePara.m_nLocalPort, APP_INI_FILE_NAME));
	return TRUE;
}

BOOL RP_WriteProfile()
{
	CString strValue;

	strValue.Format(_T("%d"), RP_GetSrcIP());
	WritePrivateProfileString(NET_SETTING_SEC_NAME, NET_SRC_IP, strValue, APP_INI_FILE_NAME);
	strValue.Format(_T("%d"), RP_GetSrcPort());
	WritePrivateProfileString(NET_SETTING_SEC_NAME, NET_SRC_PORT, strValue, APP_INI_FILE_NAME);
	strValue.Format(_T("%d"), RP_GetLocalPort());
	WritePrivateProfileString(NET_SETTING_SEC_NAME, NET_LOCAL_PORT, strValue, APP_INI_FILE_NAME);
	
	return TRUE;
}

DWORD RP_GetSrcIP()
{
	return g_StReceivePara.m_dwSrcIP;
}

void	RP_SetSrcIP(DWORD dwIP)
{
	g_StReceivePara.m_dwSrcIP = dwIP;
}

UINT	RP_GetSrcPort()
{
	return g_StReceivePara.m_nSrcPort;
}

void	RP_SetSrcPort(UINT nPort)
{
	g_StReceivePara.m_nSrcPort = nPort;
}

UINT	RP_GetLocalPort()
{
	return g_StReceivePara.m_nLocalPort;
}

void	RP_SetLocalPort(UINT nPort)
{
	g_StReceivePara.m_nLocalPort = nPort;
}
