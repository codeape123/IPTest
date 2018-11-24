#pragma once

#include "rtpsession.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#include "rtplibraryversion.h"

///
class RTP_EXP CRtpBase
{
public:
	CRtpBase();
	~CRtpBase();

public:
	void SetIPAddress(uint32_t u32IP, uint16_t u16Port, uint16_t u16PortLocal){ m_u32IP = u32IP; m_u16Port = u16Port; m_u16PortLocal = u16PortLocal; };
	void SetDataTimes(int iDataTimes) { m_iDataTimes = iDataTimes; }; //设置数据次数（一秒内）

protected:
	jrtplib::RTPSession			m_oSessRTP;
	jrtplib::RTPUDPv4TransmissionParams m_oTransParams;
	jrtplib::RTPSessionParams	m_oSessParams;

	int					m_iDataTimes; //每秒处理几次数据，用于计算timestamp unit；比如音频是8000HZ，这里就设置8000

	uint32_t			m_u32IP;;
	uint16_t			m_u16Port;
	uint16_t			m_u16PortLocal;

	jrtplib::RTPPacket*			m_pPack;
};
