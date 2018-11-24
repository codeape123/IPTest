
// FFPlayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FFPlay.h"
#include "FFPlayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFPlayDlg dialog
CFFPlayDlg::CFFPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFFPlayDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_codec.SetCallBack(this);
}

void CFFPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFFPlayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay )
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop )
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_BTN_PREV_FRAME, OnBtnPrevFrame)
	ON_BN_CLICKED(IDC_BTN_NEXT_FRAME, OnBtnNextFrame)
	ON_EN_UPDATE(IDC_BRS_FILE,  OnEnUpdateBrsFile)
END_MESSAGE_MAP()

// CFFPlayDlg message handlers
BOOL CFFPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_wndVideo.CreateChildWnd(this, IDC_STA_FRAME);
	m_codec.FFMInit();

	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_PREV_FRAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEXT_FRAME)->EnableWindow(FALSE);
	ReLayout();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFFPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		return;
	}
}

HCURSOR CFFPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFFPlayDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	ReLayout();
}

void CFFPlayDlg::OnClose()
{
	OnBtnStop();
	__super::OnClose();
}

void CFFPlayDlg::OnBtnPlay()
{
	if (!m_codec.IsOpen())
	{
		if (m_codec.OpenClip(m_strFile) < 0)
			return;
	}

	m_codec.Play();
	GetDlgItem(IDC_BTN_PLAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BTN_PREV_FRAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEXT_FRAME)->EnableWindow(FALSE);
}

void CFFPlayDlg::OnBtnStop()
{
	m_codec.CloseClip();
	GetDlgItem(IDC_BTN_PLAY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTN_PREV_FRAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEXT_FRAME)->EnableWindow(FALSE);

}

void CFFPlayDlg::OnBtnPause()
{
	m_codec.Pause();
	GetDlgItem(IDC_BTN_PLAY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTN_PREV_FRAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_NEXT_FRAME)->EnableWindow(TRUE);

}

void CFFPlayDlg::OnBtnPrevFrame()
{
	
}

void CFFPlayDlg::OnBtnNextFrame()
{

}

void CFFPlayDlg::OnEnUpdateBrsFile()
{
	GetDlgItem(IDC_BRS_FILE)->GetWindowText(m_strFile);

	OnBtnStop();
	OnBtnPlay();
}

#define BTN_WIDTH		50
#define BTN_HEIGHT		30
#define CTRL_GAP		2

void CFFPlayDlg::ReLayout()
{
	CWnd* pVideoWnd = GetDlgItem(IDC_STA_FRAME);
	if (pVideoWnd == NULL
		|| !::IsWindow(pVideoWnd->GetSafeHwnd()))
		return;

	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.DeflateRect(CTRL_GAP, CTRL_GAP);

	//PREV
	CRect rectBtn(rectClient.left, rectClient.bottom - BTN_HEIGHT, BTN_WIDTH, rectClient.bottom);
	GetDlgItem(IDC_BTN_PREV_FRAME)->MoveWindow(rectBtn);

	//play/pause
	rectBtn.OffsetRect(BTN_WIDTH + CTRL_GAP, 0);
	GetDlgItem(IDC_BTN_PAUSE)->MoveWindow(rectBtn);
	GetDlgItem(IDC_BTN_PLAY)->MoveWindow(rectBtn);

	//NEXT
	rectBtn.OffsetRect(BTN_WIDTH + CTRL_GAP, 0);
	GetDlgItem(IDC_BTN_NEXT_FRAME)->MoveWindow(rectBtn);

	//stop
	rectBtn.OffsetRect(BTN_WIDTH + CTRL_GAP, 0);
	GetDlgItem(IDC_BTN_STOP)->MoveWindow(rectBtn);

	//TC
	rectBtn.SetRect(rectClient.right - 300, rectClient.bottom - BTN_HEIGHT, rectClient.right, rectClient.bottom);
	GetDlgItem(IDC_STA_TC)->MoveWindow(rectBtn);

	//File
	rectBtn.SetRect(rectClient.left, rectClient.bottom - BTN_HEIGHT * 2 - CTRL_GAP, rectClient.right, rectClient.bottom - BTN_HEIGHT - CTRL_GAP);
	GetDlgItem(IDC_BRS_FILE)->MoveWindow(rectBtn);

	//sld
	rectBtn.OffsetRect(0, -BTN_HEIGHT - CTRL_GAP);
	GetDlgItem(IDC_SLD_PROGRESS)->MoveWindow(rectBtn);

	//video
	ResizeVideoArea();
}

void CFFPlayDlg::ResizeVideoArea()
{
	if (!m_codec.IsOpen())
		return;

	CWnd* pVideoWnd = GetDlgItem(IDC_STA_FRAME);
	if (pVideoWnd == NULL
		|| !::IsWindow(pVideoWnd->GetSafeHwnd()))
		return;

	GetDlgItem(IDC_SLD_PROGRESS)->GetWindowRect(m_rectVideo);
	ScreenToClient(m_rectVideo);
	m_rectVideo.top = 0;
	m_rectVideo.bottom -= BTN_HEIGHT + CTRL_GAP;

	//高不变，改宽，并居中
	float fCenterX = m_rectVideo.Width() / 2.0f;
	float fWidthScaled = m_rectVideo.Height() * float(m_codec.Get_video_width()) / float(m_codec.Get_video_height());
	m_rectVideo.left = int(fCenterX - fWidthScaled / 2 + .5f );
	m_rectVideo.right = int(fCenterX + fWidthScaled / 2 + .5f);
	pVideoWnd->MoveWindow(m_rectVideo);
}

BOOL CFFPlayDlg::OnTaskNotify(WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{	
	if(lParam == 0)//lparam: 0:  Get video info
	{
		m_wndVideo.SetVideoInfo(m_codec.Get_video_width(), m_codec.Get_video_height(), 24);
		ResizeVideoArea();	
		ShowTC();
	}
	else if (lParam == 1)//lparam: 1:  Get video data buffer
	{
		m_wndVideo.ShowVideoFrame( (void*)wParam );
	}
	return TRUE;
}

void CFFPlayDlg::ShowTC()
{
	int64_t i64Duration = m_codec.Get_video_duration();
	CString strDuration;
	
	//帧率
	int iFR = m_codec.Get_video_FrameRate();

	//duration是以微秒为单位
	//转换成hh:mm:ss形式
	int tns, thh, tmm, tss;
	tns = (i64Duration) / 1000000;
	thh = tns / 3600;
	tmm = (tns % 3600) / 60;
	tss = (tns % 60);
	strDuration.Format(_T("W:%02d, H:%02d\tFR：%02dfps\tDur:%02d:%02d:%02d"), m_codec.Get_video_width(), m_codec.Get_video_height(), iFR, thh, tmm, tss);

	GetDlgItem(IDC_STA_TC)->SetWindowText(strDuration);
}