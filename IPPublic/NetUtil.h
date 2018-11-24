#pragma once

void IP_PUBLIC_EXP NetSockStart();
void IP_PUBLIC_EXP NetSockEnd();
BOOL IP_PUBLIC_EXP NetGetLocalIp(in_addr& addrIP, int iIdx = 0);