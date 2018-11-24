#pragma once
#include "RtpBase.h"

///
class RTP_EXP CRtpSend : public CRtpBase
{
public:
	CRtpSend();
	~CRtpSend();

public:
	void BeginSend();
	void StopSend();
	void PushData();

public:
	//lparam: 1: clip info
	BOOL	OnTaskNotify(WPARAM wParam = NULL, LPARAM lParam = NULL);

protected:
	HANDLE			m_hSendThread;

	CIPEvent		m_eventStop;
	CIPEvent		m_eventSend;
	CIPEvent		m_eventTimer;

	static unsigned int __stdcall ThreadSendFrameProc(void* in_pThreadParameter);
	static void CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);

	unsigned int	SendFrameRoutine();

	HANDLE			m_hTimerQueue;
	HANDLE			m_hTimerSend;
};