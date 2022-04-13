// UDPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
	   return;
	}


	if ( LOBYTE( wsaData.wVersion ) != 1 ||
			 HIBYTE( wsaData.wVersion ) != 1 ) {
	   WSACleanup( );
	   return; 
	}

	

	SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addrSrv;
//	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	char szhostname[32];
	if(gethostname(szhostname,sizeof(szhostname))==0) 
	{
       struct hostent* pHost;
   	   pHost=gethostbyname(szhostname);
	   addrSrv.sin_addr.S_un.S_addr=((struct in_addr*)pHost->h_addr_list[0])->S_un.S_addr;
	}
	
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6101);

	while(1)
	{
		sendto(sockClient,"world",strlen("world")+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		Sleep(100);
	}
	closesocket(sockClient);
	WSACleanup();
}


