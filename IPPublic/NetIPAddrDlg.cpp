// NetIPAddrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "NetIPAddrDlg.h"
#include "PublicDefine.h"

// CNetIPAddrDlg dialog

IMPLEMENT_DYNAMIC(CNetIPAddrDlg, CDialog)
CNetIPAddrDlg::CNetIPAddrDlg(DWORD dwIP, UINT uPort)
: CDialog(IDD_IP_ADDRESS, NULL)
, m_uPort(uPort)
, m_dwIP(dwIP)
{
}

CNetIPAddrDlg::CNetIPAddrDlg(in_addr& addrIP, UINT uPort)
: CDialog(IDD_IP_ADDRESS, NULL)
, m_uPort(uPort)
{
	m_dwIP = htonl(addrIP.S_un.S_addr);
}


CNetIPAddrDlg::~CNetIPAddrDlg()
{
}

void CNetIPAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT, m_uPort);
	DDV_MinMaxUInt(pDX, m_uPort, 10, 20000);
	DDX_IPAddress(pDX, IDC_IP, m_dwIP);
}

BEGIN_MESSAGE_MAP(CNetIPAddrDlg, CDialog)
END_MESSAGE_MAP()


// CNetIPAddrDlg message handlers
BOOL CNetIPAddrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;
}

void CNetIPAddrDlg::OnOK()
{
	UpdateData(TRUE);

	CDialog::OnOK();
}