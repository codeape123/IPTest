// IPReceiverDlg.h : ͷ�ļ�
//
#pragma once

// CIPReceiverDlg �Ի���
class CIPReceiverDlg : public CDialogEx
{
// ����
public:
	CIPReceiverDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPRECEIVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnBtnReceive();
	afx_msg void OnBtnStop();

	afx_msg void OnBtnSetting();

	DECLARE_MESSAGE_MAP()

protected:
	CRtpReceive	m_pRtpReceive;
};
