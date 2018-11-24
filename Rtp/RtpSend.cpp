#include "stdafx.h"
#include "RtpSend.h"
#include "stdio.h"
#include "RtpUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CRtpSend
CRtpSend::CRtpSend()
{
	m_hSendThread = NULL;

	m_hTimerQueue = NULL;
	m_hTimerSend = NULL;
}

CRtpSend::~CRtpSend()
{
}

//
//void CRtpSend::CreateTimer()
//{
//	//创建一个TimerQueue
//	m_hTimerQueue = CreateTimerQueue();
//
//	if (NULL == m_hTimerQueue)
//	{
//		TRACE("CRtpSend CreateTimerQueue failed (%d)\n", GetLastError());
//	}
//}
//
//void CFFVideoDecodec::DeleteTimer()
//{
//	if (m_hTimerQueue == NULL)
//		return;
//
//	StopTimer();
//
//	// Delete all timers in the timer queue.
//	if (!DeleteTimerQueue(m_hTimerQueue))
//		TRACE("DeleteTimerQueue failed (%d)\n", GetLastError());
//
//	m_hTimerQueue = NULL;
//}

void CRtpSend::BeginSend()
{
	//1.
	// IMPORTANT: The local timestamp unit MUST be set, otherwise
	//            RTCP Sender Report info will be calculated wrong
	// In this case, we'll be sending 10 samples each second, so we'll
	// put the timestamp unit to (1.0/10.0)
	m_oSessParams.SetOwnTimestampUnit(1.0 / m_iDataTimes);

	m_oSessParams.SetAcceptOwnPackets(true);
	m_oTransParams.SetPortbase(m_u16PortLocal); //local
	int status = m_oSessRTP.Create(m_oSessParams, &m_oTransParams);
	RtpCheckError(status);

	//	uint32_t destip = ntohl(SP_GetDestIP());

	RTPIPv4Address addr(m_u32IP, m_u16Port);

	status = m_oSessRTP.AddDestination(addr);
	RtpCheckError(status);

	//2.
	//CreateTimer();

	//3.
	m_eventStop.Reset();
	m_eventSend.Reset();

	unsigned int uiThreadID;
	m_hSendThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, ms_kuiDefaultStackSize, ThreadSendFrameProc, this, 0, &uiThreadID));
	if (m_hSendThread == NULL)
	{
		ASSERT(FALSE);
		return ;
	}
	VERIFY(::SetThreadPriority(m_hSendThread, THREAD_PRIORITY_NORMAL));

	return;

}

void CRtpSend::StopSend()
{
	//StopTimer();

	m_eventStop.Set();

	if (m_hSendThread != NULL)
	{
		WaitForSingleObject(m_hSendThread, 5000);
		SAFE_CLOSE_HANDLE(m_hSendThread);
	}
}

void CRtpSend::PushData()
{
	m_eventSend.Set();
}

/////////////////
unsigned int CRtpSend::ThreadSendFrameProc(void* in_pThreadParameter)
{
	CRtpSend* pRtpSend = (CRtpSend*)in_pThreadParameter;
	if (pRtpSend == NULL)
		return 0;

	return pRtpSend->SendFrameRoutine();
}

unsigned int CRtpSend::SendFrameRoutine()
{
	unsigned long ulWaitResult = 0;
	unsigned long ulWaitEventsArraySize = 2;
	HANDLE ahWorkerThreadControlEvents[2];

	ahWorkerThreadControlEvents[0] = (HANDLE)m_eventStop;
	ahWorkerThreadControlEvents[1] = (HANDLE)m_eventSend;

#define SEND_DATA_LEN 100
	char szSend[SEND_DATA_LEN];
	int iDataIdx(0);

	for (;;)
	{
		ulWaitResult = WaitForMultipleObjects(ulWaitEventsArraySize,        // how many events to wait for
			ahWorkerThreadControlEvents,  // events array
			FALSE,                        // wake up on any signal
			INFINITE);                    // INFINITE timeout      

		if (ulWaitResult == WAIT_OBJECT_0 + 0) //stop
		{
			break;
		}
		else if (ulWaitResult == WAIT_OBJECT_0 + 1) //Send
		{
			/** Sends the RTP packet with payload \c data which has length \c len.
			*  It will use payload type \c pt, marker \c mark and after the packet has been built, the
			*  timestamp will be incremented by \c timestampinc.
			*/
			std::string strSend;
			sprintf_s(szSend, SEND_DATA_LEN, "send data %d\n", iDataIdx++);

			int status = m_oSessRTP.SendPacket(szSend, SEND_DATA_LEN, 0, false, m_iDataTimes); //m_iDataTimes????
			RtpCheckError(status);

			m_eventSend.Reset();
		}
		else
		{
			Sleep(0);
			ASSERT(false);
		}
	}

	m_eventStop.Reset();
	m_eventSend.Reset();

	m_oSessRTP.BYEDestroy(RTPTime(10, 0), 0, 0);
	
	return 0;
}

BOOL CRtpSend::OnTaskNotify(WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{
	if (lParam == 0)//lparam: 0:  Get video info
	{
	}
	else if (lParam == 1)//lparam: 1:  Get video data buffer
	{
		m_eventSend.Set();		
	}
	return TRUE;
}