/////////////////////////////////////////////////////////////////////////
// FileName: GlobalSetting.cpp
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlobalSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
/*
struct StIPGlobalPara
{
	CString m_strSendFile;
	//
	DWORD   m_dwNetIP;
	UINT    m_nNetPort;

	//socket send
	UINT	m_nSendBufSizeKB; //KB
	UINT	m_nSendLenKB;    //KB
	UINT	m_nSendPeriodMs;   //ms

	StIPGlobalPara()
	{
		m_strSendFile = _T("c:\\NetData.ndt");
		//strNetIP = _T("127.0.0.1");
		m_dwNetIP = 0x7F000001;
		m_nNetPort = 8080;

		m_nSendBufSizeKB = 1000;
		m_nSendLenKB     = 10;
		m_nSendPeriodMs  = 10;
	}
};

static StIPGlobalPara g_StIPGlobalPara;

BOOL GP_ReadProfile()
{
	TCHAR szResult[MAX_PATH];

	GetPrivateProfileString(WORK_SETUP_SEC_NAME, SEND_FILE, g_StIPGlobalPara.m_strSendFile, szResult, MAX_PATH, APP_INI_FILE_NAME);
	GP_SetSendFile(szResult);

	GP_SetNetIP((BOOL)GetPrivateProfileInt(NET_SETTING_SEC_NAME, NET_IP, g_StIPGlobalPara.m_dwNetIP, APP_INI_FILE_NAME));
	GP_SetNetPort((BOOL)GetPrivateProfileInt(NET_SETTING_SEC_NAME, NET_PORT, g_StIPGlobalPara.m_nNetPort, APP_INI_FILE_NAME));

	GP_SetSocketBufSize((BOOL)GetPrivateProfileInt(SOCKET_SETTING_SEC_NAME, SOCKET_BUFFER, g_StIPGlobalPara.m_nSendBufSizeKB, APP_INI_FILE_NAME));
	GP_SetSocketSendLength((BOOL)GetPrivateProfileInt(SOCKET_SETTING_SEC_NAME, SOCKET_SEND_LENGTH, g_StIPGlobalPara.m_nSendLenKB, APP_INI_FILE_NAME));
	GP_SetSocketSendPeriod((BOOL)GetPrivateProfileInt(SOCKET_SETTING_SEC_NAME, SOCKET_SEND_PERIOD, g_StIPGlobalPara.m_nSendPeriodMs, APP_INI_FILE_NAME));
	return TRUE;
}

BOOL GP_WriteProfile()
{
	CString strValue;

	WritePrivateProfileString(WORK_SETUP_SEC_NAME, SEND_FILE, GP_GetSendFile(), APP_INI_FILE_NAME);
	strValue.Format(_T("%d"), GP_GetNetIP() );
	WritePrivateProfileString(NET_SETTING_SEC_NAME, NET_IP, strValue, APP_INI_FILE_NAME);
	strValue.Format(_T("%d"), GP_GetNetPort() );
	WritePrivateProfileString(NET_SETTING_SEC_NAME, NET_PORT, strValue, APP_INI_FILE_NAME);
	
	strValue.Format(_T("%d"), GP_GetSocketBufSize() );
	WritePrivateProfileString(SOCKET_SETTING_SEC_NAME, SOCKET_BUFFER, strValue, APP_INI_FILE_NAME);
	strValue.Format(_T("%d"), GP_GetSocketSendLength() );
	WritePrivateProfileString(SOCKET_SETTING_SEC_NAME, SOCKET_SEND_LENGTH, strValue, APP_INI_FILE_NAME);
	strValue.Format(_T("%d"), GP_GetSocketSendPeriod() );
	WritePrivateProfileString(SOCKET_SETTING_SEC_NAME, SOCKET_SEND_PERIOD, strValue, APP_INI_FILE_NAME);
	return TRUE;
}

void GP_SetSendFile( CString strSendFile )
{
	g_StIPGlobalPara.m_strSendFile = strSendFile;
}

CString GP_GetSendFile()
{
	return g_StIPGlobalPara.m_strSendFile;
}

DWORD GP_GetNetIP()
{
	return g_StIPGlobalPara.m_dwNetIP;
}

void	GP_SetNetIP( DWORD dwIP )
{
	g_StIPGlobalPara.m_dwNetIP = dwIP;
}

UINT	GP_GetNetPort()
{
	return g_StIPGlobalPara.m_nNetPort;
}

void	GP_SetNetPort( UINT nPort )
{
	g_StIPGlobalPara.m_nNetPort = nPort;
}

UINT	GP_GetSocketBufSize()
{
	return g_StIPGlobalPara.m_nSendBufSizeKB;
}

void	GP_SetSocketBufSize( UINT nSendBufSizeKB )
{
	g_StIPGlobalPara.m_nSendBufSizeKB = nSendBufSizeKB;
}

UINT 	GP_GetSocketSendLength()
{
	return g_StIPGlobalPara.m_nSendLenKB;
}

void	GP_SetSocketSendLength( UINT nSendLenKB )
{
	g_StIPGlobalPara.m_nSendLenKB = nSendLenKB;
}

UINT 	GP_GetSocketSendPeriod()
{
	return g_StIPGlobalPara.m_nSendPeriodMs;
}

void	GP_SetSocketSendPeriod( UINT nSendPeriodMs )
{
	g_StIPGlobalPara.m_nSendPeriodMs = nSendPeriodMs;
}

*/