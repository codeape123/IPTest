#pragma once

// CNetIPAddrDlg dialog

class IP_PUBLIC_EXP CNetIPAddrDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetIPAddrDlg)

public:
	CNetIPAddrDlg(DWORD dwIP, UINT uPort);   // standard constructor
	CNetIPAddrDlg(in_addr& addrIP, UINT uPort);   // standard constructor
	virtual ~CNetIPAddrDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	UINT	m_uPort;
	DWORD	m_dwIP;
};
