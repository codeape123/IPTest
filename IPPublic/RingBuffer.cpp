#include "stdafx.h"
#include "Ringbuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CRingBuffer::CRingBuffer()
{
	m_size = 0;
	m_nUnitCount = 0;
	m_front = 0;
	m_rear = 0;
	m_data = NULL;
}

CRingBuffer::~CRingBuffer()
{
	_aligned_free(m_data);
}

void CRingBuffer::AllocMem(unsigned size)
{
	m_size = size;
	m_data = (byte*)_aligned_malloc(m_size, 16);
}

void CRingBuffer::AdjustUnit(unsigned int sizeUnit)
{
	CSingleLock l(&m_lock, TRUE);
	if (m_data == NULL)
	{
		TRACE("Error allocation aligned memory.");
		ASSERT(FALSE);
	}

	m_front = 0;
	m_rear = 0;

	m_sizeUnit = sizeUnit;
	m_nUnitCount = m_size / m_sizeUnit;
}

bool CRingBuffer::isEmpty()
{
	CSingleLock l(&m_lock, TRUE);
	return m_front == m_rear;
}

bool CRingBuffer::isFull()
{
	CSingleLock l(&m_lock, TRUE);
	return m_front == (m_rear + 1) % m_nUnitCount;
}

BOOL CRingBuffer::push(void* pNewData)
{
	CSingleLock l(&m_lock, TRUE);

	if (isFull())
	{
		TRACE(_T("ringbuf push Fail, Full ! m_front = %d, m_rear = %d \n"), m_front, m_rear);
		return FALSE;
	}

	int iNext = (m_rear + 1) % m_nUnitCount;
	TRACE(_T("ringbuf push Suc ! m_front = %d, m_rear = %d -> %d \n"), m_front, m_rear, iNext );

	void* pRearUnit = m_data + m_rear * m_sizeUnit;
	memcpy_s(pRearUnit, m_sizeUnit, pNewData, m_sizeUnit);

	m_rear = iNext;

	return TRUE;
}

void* CRingBuffer::pop()
{
	CSingleLock l(&m_lock, TRUE);
	if (isEmpty())
	{
		TRACE(_T("ringbuf pop Fail, Empty ! m_front = %d, m_rear = %d \n"), m_front, m_rear);
		return NULL;
	}

	void* pTemp = m_data + m_front * m_sizeUnit;
	int iOldFront = m_front;
	m_front = (m_front + 1) % m_nUnitCount;
	TRACE(_T("ringbuf pop Suc ! m_front = %d -> %d, m_rear = %d \n"), iOldFront, m_front, m_rear);

	return pTemp;
}

void* CRingBuffer::GetFront()
{
	CSingleLock l(&m_lock, TRUE);
	if (isEmpty())
	{
		TRACE(_T("ringbuf GetFront Fail, Empty ! m_front = %d, m_rear = %d \n"), m_front, m_rear);
		return NULL;
	}

	void* pFront = m_data + m_front * m_sizeUnit;
	TRACE(_T("ringbuf GetFront Suc ! m_front = %d, m_rear = %d \n"), m_front, m_rear);

	return pFront;
}