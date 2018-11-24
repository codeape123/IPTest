/////////////////////////////////////////////////////////////////////////
// FileName: ReceiveSetting.h
/////////////////////////////////////////////////////////////////////////

#pragma once

#define APP_INI_FILE_NAME					_T("IPReceive.ini")

#define NET_SETTING_SEC_NAME				_T("NET_SETTING")
#define NET_LOCAL_PORT						_T("NetLocalPort")
#define NET_SRC_IP							_T("NetSrcIP")
#define NET_SRC_PORT						_T("NetSrcPort")


BOOL	RP_ReadProfile();
BOOL	RP_WriteProfile();

DWORD	RP_GetSrcIP();
void	RP_SetSrcIP( DWORD dwIP );

UINT	RP_GetSrcPort();
void	RP_SetSrcPort( UINT nPort );

UINT	RP_GetLocalPort();
void	RP_SetLocalPort(UINT nPort);