#include "stdafx.h"
#include "NetUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "ws2_32.lib")


void NetSockStart()
{
	WSADATA dat;
	WSAStartup(MAKEWORD(2, 2), &dat);
}

void NetSockEnd()
{
	WSACleanup();
}

BOOL NetGetLocalIp(in_addr& addrIP, int iIdx /*= 0*/)
{
	char szText[256];
	//获取本机主机名称
	int iRet;
	iRet = gethostname(szText, 256);
	if (iRet != 0)
	{
		int a = WSAGetLastError();
		TRACE(_T("gethostname()  Failed! err = %d\n"), a);
		return FALSE;
	}
	//通过主机名获取到地址信息
	HOSTENT *host = gethostbyname(szText);
	if (NULL == host)
	{
		int a = WSAGetLastError();
		TRACE(_T("gethostbyname()  Failed! err = %d\n"), a);
		return FALSE;
	}

	for (int i = 0;; i++)
	{
		char *p = host->h_addr_list[i];
		if (NULL == p)
		{
			return FALSE;
		}

		if (i == iIdx)
		{
			memcpy(&(addrIP.S_un.S_addr), p, host->h_length);
			TRACE(_T("本机第%d块卡的ip地址是：%d.%d.%d.%d\n"), iIdx, addrIP.S_un.S_un_b.s_b1, addrIP.S_un.S_un_b.s_b2, addrIP.S_un.S_un_b.s_b3, addrIP.S_un.S_un_b.s_b4);

			return TRUE;
		}
	}

	return FALSE;
}