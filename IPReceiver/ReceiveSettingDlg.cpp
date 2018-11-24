// SysSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ReceiveSettingDlg.h"
#include "ReceiveSetting.h"

//////////////////////////////////////////////////////////////////////////
// CReceiveSettingDlg dialog
CReceiveSettingDlg::CReceiveSettingDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CReceiveSettingDlg::IDD, pParent)
{
}

CReceiveSettingDlg::~CReceiveSettingDlg()
{
}

void CReceiveSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReceiveSettingDlg, CDialogEx)
	ON_COMMAND(IDC_BTN_LOCAL_IP, OnBtnLocalIP)
	ON_COMMAND(IDC_BTN_SRC_IP, OnBtnSrcIP)

END_MESSAGE_MAP()

// CReceiveSettingDlg message handlers

BOOL CReceiveSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  
}


void CReceiveSettingDlg::OnBtnLocalIP()
{
	in_addr addrIP;
	NetGetLocalIp(addrIP);

	CNetIPAddrDlg dlg(addrIP, RP_GetLocalPort());

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		RP_SetLocalPort(dlg.m_uPort);
	}
}

void CReceiveSettingDlg::OnBtnSrcIP()
{
	CNetIPAddrDlg dlg(RP_GetSrcIP(), RP_GetSrcPort());

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		RP_SetSrcIP(dlg.m_dwIP);
		RP_SetSrcPort(dlg.m_uPort);
	}
}
