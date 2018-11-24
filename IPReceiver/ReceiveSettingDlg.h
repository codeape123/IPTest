#pragma once

//  dialog

class CReceiveSettingDlg : public CDialogEx
{
public:
	CReceiveSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReceiveSettingDlg();

// Dialog Data
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBtnLocalIP();
	afx_msg void OnBtnSrcIP();

	DECLARE_MESSAGE_MAP()

protected:
};
