#include "stdafx.h"
#include "RtpUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
// This function checks if there was a RTP error. If so, it displays an error
// message and exists.
//
void RtpCheckError(int rtperr, BOOL bTrace, BOOL bAssert)
{
	if (rtperr < 0)
	{
		std::string strErr = RTPGetErrorString(rtperr);

		CString strTrace(strErr.c_str());
		strTrace += _T("\n");
		if (bTrace)
			TRACE(strTrace);
		if (bAssert)
			ASSERT(FALSE);
	}
}