#include "stdafx.h"
#include "RtpReceive.h"
#include "RtpUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CRtpReceive
CRtpReceive::CRtpReceive()
{
	m_hReceiveThread = NULL;
}

CRtpReceive::~CRtpReceive()
{
}

void CRtpReceive::BeginReceive()
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
	m_eventStop.Reset();

	unsigned int uiThreadID;
	m_hReceiveThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, ms_kuiDefaultStackSize, ThreadReceiveFrameProc, this, 0, &uiThreadID));
	if (m_hReceiveThread == NULL)
	{
		ASSERT(FALSE);
		return ;
	}
	VERIFY(::SetThreadPriority(m_hReceiveThread, THREAD_PRIORITY_NORMAL));

	m_eventReceive.Set();

	return ;

}

void CRtpReceive::StopReceive()
{
	m_eventStop.Set();
}

/////////////////
unsigned int CRtpReceive::ThreadReceiveFrameProc(void* in_pThreadParameter)
{
	CRtpReceive* pRtpReceive = (CRtpReceive*)in_pThreadParameter;
	if (pRtpReceive == NULL)
		return 0;

	return pRtpReceive->ReceiveFrameRoutine();
}

unsigned int CRtpReceive::ReceiveFrameRoutine()
{
	unsigned long ulWaitResult = 0;
	unsigned long ulWaitEventsArraySize = 2;
	HANDLE ahWorkerThreadControlEvents[2];

	ahWorkerThreadControlEvents[0] = (HANDLE)m_eventStop;
	ahWorkerThreadControlEvents[1] = (HANDLE)m_eventReceive;

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
		else if (ulWaitResult == WAIT_OBJECT_0 + 1) //Receive
		{
			m_oSessRTP.BeginDataAccess();

			// check incoming packets
			if (m_oSessRTP.GotoFirstSourceWithData())
			{
				do
				{
					RTPPacket *pack;

					while ((pack = m_oSessRTP.GetNextPacket()) != NULL)
					{
						// You can examine the data here
						TRACE("Got packet !\n");

						// we don't longer need the packet, so
						// we'll delete it
						m_oSessRTP.DeletePacket(pack);
					}
				} while (m_oSessRTP.GotoNextSourceWithData());
			}

			m_oSessRTP.EndDataAccess();
		}
		else
		{
			Sleep(0);
			ASSERT(false);
		}
	}

	m_eventStop.Reset();
	m_eventReceive.Reset();

	return 0;
}