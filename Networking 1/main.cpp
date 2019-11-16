#include <WinSock2.h>
#include <stdio.h>

//#include "server.h"

int main()
{
	WORD winsock_version = 0x202;
	WSADATA winsock_data;
	if ( /*WSAStartup( winsock_version, &winsock_data )*/ true )
	{
		
		printf("WSAStartup failed: %d", WSAGetLastError() );
		return 0;
	}
	return 1;
}