// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>

void main(int argc, char* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD(1,1);
	
	err = WSAStartup( wVersionRequested, &wsaData );//加载套接字库
	if (err != 0 )
	{
		return;
	}	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return; 
	}

	SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);//创建套接字。

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("49.140.166.92");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//向服务器发出连接请求。

	char recvBuf[256];//和服务器端进行通信。
	recv(sockClient,recvBuf,256,0);
	printf("%s\n",recvBuf);


	char sendBuf[256];
	char szhostname[32];
	if(gethostname(szhostname,sizeof(szhostname))==0) 
	{
       struct hostent* pHost;
   	   pHost=gethostbyname(szhostname);
	   strcpy(sendBuf,inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]));//addr为本机的IP地址
	   strcat(sendBuf,":\t");
   }


	
	char input[256];	
    gets(input);
	strcat(sendBuf,input);

	send(sockClient,sendBuf,strlen(sendBuf)+1,0);
	closesocket(sockClient);//关闭套接字。
	WSACleanup();//必须调用这个函数清除参数

}
/*	SOCKET sock;   //socket套接字

    char szMsg[] = "this is a UDP test package";//被发送的字段

    //1.启动SOCKET库，版本为2.0

    WORD wVersionRequested;

    WSADATA wsaData;

    int err;  

    wVersionRequested = MAKEWORD( 2, 0 ); 

    err = WSAStartup( wVersionRequested, &wsaData );

    if ( 0 != err ) //检查Socket初始化是否成功

    {

       printf("Socket2.0初始化失败，Exit!");

       return;

    }

    //检查Socket库的版本是否为2.0

    if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )

    {

       WSACleanup( );

       return;

    }

    //2.创建socket，

    sock = socket(

       AF_INET,           //internetwork: UDP, TCP, etc

       SOCK_DGRAM,        //SOCK_DGRAM说明是UDP类型

       0                  //protocol

       );

    if (INVALID_SOCKET == sock ) {

       printf("Socket 创建失败，Exit!");

       return;

    }

    //3.设置该套接字为广播类型，

    bool opt = true;

    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char FAR *>(&opt), sizeof(opt));

    //4.设置发往的地址

    sockaddr_in addrto;            //发往的地址 

    memset(&addrto,0,sizeof(addrto));

    addrto.sin_family = AF_INET;               //地址类型为internetwork

    addrto.sin_addr.s_addr = INADDR_BROADCAST; //设置ip为广播地址

    addrto.sin_port = htons(7861);             //端口号为7861

    int nlen=sizeof(addrto);

    unsigned int uIndex = 1;

    while(true)

    {

       Sleep(1000); //程序休眠一秒

       //向广播地址发送消息

       if( sendto(sock, szMsg, strlen(szMsg), 0, (sockaddr*)&addrto,nlen)

           == SOCKET_ERROR )

           printf("WSAGetLastError()");

       else

           printf("%d,:an UDP package is sended.",uIndex++);

    }

    if (!closesocket(sock)) //关闭套接字

    {

       WSAGetLastError();

       return;

    }

    if (!WSACleanup())       //关闭Socket库

    {

       WSAGetLastError();

       return;

    }  
*/
