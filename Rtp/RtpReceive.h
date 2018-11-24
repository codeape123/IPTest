#pragma once
#include "RtpBase.h"

///
class RTP_EXP CRtpReceive : public CRtpBase
{
public:
	CRtpReceive();
	~CRtpReceive();

public:
	void BeginReceive();
	void StopReceive();

protected:
	HANDLE			m_hReceiveThread;

	CIPEvent		m_eventStop;
	CIPEvent		m_eventReceive;

	static unsigned int __stdcall ThreadReceiveFrameProc(void* in_pThreadParameter);
	unsigned int	ReceiveFrameRoutine();

};