#include<stdio.h>
#include<winsock.h>

#pragma once(lib,"ws2_32.lib")

#pragma warning(disabl:4996)

int main()
{
	WSADATA wsa;
	WORD    verNo;
	int     sts;

	verNo = MAKEWORD(2, 2);

	sts = WSAStartup(
		verNo,
		&wsa
	);

	if (sts == SOCKET_ERROR)
	{
		int errCode = WSAGetLastError();
		printf("WSAStartup Failed : %d\n", errCode);
		return -1;
	}

	printf("wVwesion = %u\n", wsa.wVersion);

	printf("");


}
