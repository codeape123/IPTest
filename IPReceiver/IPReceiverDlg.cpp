
// IPReceiverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPReceiver.h"
#include "IPReceiverDlg.h"
#include "afxdialogex.h"
#include "ReceiveSettingDlg.h"
#include "ReceiveSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CIPReceiverDlg �Ի���
CIPReceiverDlg::CIPReceiverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPReceiverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPReceiverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIPReceiverDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BTN_RECEIVE, OnBtnReceive)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)	
	ON_BN_CLICKED(IDC_BTN_SETTING, OnBtnSetting)
END_MESSAGE_MAP()


// CIPReceiverDlg ��Ϣ�������

BOOL CIPReceiverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIPReceiverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIPReceiverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIPReceiverDlg::OnBtnSetting()
{
	CReceiveSettingDlg dlg;
	dlg.DoModal();
}

void CIPReceiverDlg::OnBtnStop()
{
	m_pRtpReceive.StopReceive();
}

void CIPReceiverDlg::OnBtnReceive()
{
	m_pRtpReceive.SetDataTimes(20);
	m_pRtpReceive.SetIPAddress(RP_GetSrcIP(), RP_GetSrcPort(), RP_GetLocalPort() );
	m_pRtpReceive.BeginReceive();
/*
	RTPSession sess;

	// Now, we'll create a RTP session, set the destination, send some
	// packets and poll for incoming data.

	RTPUDPv4TransmissionParams transparams;
	RTPSessionParams sessparams;

	// IMPORTANT: The local timestamp unit MUST be set, otherwise
	//            RTCP Sender Report info will be calculated wrong
	// In this case, we'll be sending 10 samples each second, so we'll
	// put the timestamp unit to (1.0/10.0)
	sessparams.SetOwnTimestampUnit(1.0 / 10.0);

	//sessparams.SetAcceptOwnPackets(true);
	transparams.SetPortbase(RP_GetLocalPort()); //local
	int status = sess.Create(sessparams, &transparams);
	RtpCheckError(status);

	//	uint32_t destip = ntohl(RP_GetDestIP());

	RTPIPv4Address addr(RP_GetSrcIP(), RP_GetSrcPort());

	status = sess.AddDestination(addr);
	RtpCheckError(status);

	//////////////////
	while (TRUE)
	{
		sess.BeginDataAccess();

		// check incoming packets
		if (sess.GotoFirstSourceWithData())
		{
			do
			{
				RTPPacket *pack;

				while ((pack = sess.GetNextPacket()) != NULL)
				{
					// You can examine the data here
					TRACE("Got packet !\n");

					// we don't longer need the packet, so
					// we'll delete it
					sess.DeletePacket(pack);
				}
			} while (sess.GotoNextSourceWithData());
		}

		sess.EndDataAccess();


		RTPTime::Wait(RTPTime(1, 0));
	}

	sess.BYEDestroy(RTPTime(10, 0), 0, 0);
	*/
}

/*
{
	RTPUDPv4TransmissionParams transparams;
	RTPSessionParams sessparams;
	list<uint32_t> localip;
	RTPSession sess;
	uint16_t portbase = 8888;
	uint32_t destip, srcip;
	string ipstr = "239.255.0.1";
	string ipsrc = "114.212.114.200";
	int status, i, num;
	destip = inet_addr(ipstr.c_str());//���ַ���ת��Ϊ32λ�����ֽ���
	srcip = inet_addr(ipsrc.c_str());
	destip = ntohl(destip);//��32λ�����ֽ���ת���������ֽ���
	srcip = ntohl(srcip);
	localip.push_back(srcip);

	sessparams.SetOwnTimestampUnit(1.0 / 8000);

	sessparams.SetAcceptOwnPackets(true);
	transparams.SetPortbase(portbase);
	//transparams.SetLocalIPList(localip);
	transparams.SetBindIP(srcip);
	transparams.SetMulticastInterfaceIP(srcip);
	RTPIPv4Address addr(destip, portbase);
	status = sess.Create(sessparams, &transparams);
	checkerror(status);
	status = sess.SupportsMulticasting();
	checkerror(status);
	status = sess.JoinMulticastGroup(addr);
	checkerror(status);
	//sess.SetDefaultPayloadType(96);
	//sess.SetDefaultMark(false);
	//sess.SetDefaultTimestampIncrement(160);

	while (1)
	{
		sess.BeginDataAccess();

		if (sess.GotoFirstSourceWithData())
		{
			do
			{
				RTPPacket *pack;
				uint32_t packetLen;
				uint8_t *packetData;
				uint8_t j = 11;
				while ((pack = sess.GetNextPacket()) != NULL)
				{
					packetLen = pack->GetPacketLength() - 1;
					packetData = pack->GetPacketData();
					printf("RECV data: ");
					while (j++ < packetLen)
					{
						printf("%c", *(packetData + j));
					}
					printf("\n");
					sess.DeletePacket(pack);
				}


			} while (sess.GotoNextSourceWithData());

		}
		sess.EndDataAccess();

	}

	return 0;

}
*/