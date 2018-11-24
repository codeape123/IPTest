
// FFPlayDlg.h : header file
//

#pragma once

#include "FFMPEGUtil.h"
#include "VideoWnd.h"

// CFFPlayDlg dialog
class CFFPlayDlg : public CDialogEx
				 , public ITaskCB
{
// Construction
public:
	CFFPlayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FFPLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnUpdateBrsFile();
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnPrevFrame();
	afx_msg void OnBtnNextFrame();
	DECLARE_MESSAGE_MAP()

protected:
	void	ReLayout();
	void	ResizeVideoArea();
	void	ShowVideoFrame(void* pDataBuf, int iVideoWidth, int iVideoHeight, int bpp);
	void	ShowTC();

public:
	//lparam: 1: clip info

	BOOL	OnTaskNotify(WPARAM wParam = NULL, LPARAM lParam = NULL);

protected:
	CFFMPCodec	m_codec;
	CString		m_strFile;

	CVideoWnd	m_wndVideo;
	CRect		m_rectVideo;
};
