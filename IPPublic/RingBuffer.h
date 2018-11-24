#pragma once

#include <iostream>
#include "afxmt.h"

using namespace std;

class IP_PUBLIC_EXP CRingBuffer
{
private:
	int				m_front;
	int				m_rear;
	byte*			m_data;
	unsigned int    m_size;		//总内存的大小
	unsigned int    m_sizeUnit; //每块内存的大小
	unsigned int	m_nUnitCount;

	CCriticalSection	m_lock;

public:
	CRingBuffer();
	~CRingBuffer();

	void	AllocMem(unsigned size);
	void	AdjustUnit(unsigned int sizeUnit);
	bool	isEmpty();
	bool	isFull();
	BOOL	push(void* pNewData);
	void*	pop();
	void*	GetFront();
};
