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
	//��ȡ������������
	int iRet;
	iRet = gethostname(szText, 256);
	if (iRet != 0)
	{
		int a = WSAGetLastError();
		TRACE(_T("gethostname()  Failed! err = %d\n"), a);
		return FALSE;
	}
	//ͨ����������ȡ����ַ��Ϣ
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
			TRACE(_T("������%d�鿨��ip��ַ�ǣ�%d.%d.%d.%d\n"), iIdx, addrIP.S_un.S_un_b.s_b1, addrIP.S_un.S_un_b.s_b2, addrIP.S_un.S_un_b.s_b3, addrIP.S_un.S_un_b.s_b4);

			return TRUE;
		}
	}

	return FALSE;
}