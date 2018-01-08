
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <MMSystem.h>
#include <windows.h>
#include <process.h>
#include <WS2tcpip.h>
#include "NetService.h"
#include "E3DNet.h"
#pragma comment (lib,"ws2_32.lib")
#pragma comment(lib, "winmm.lib") 

WSADATA		wsData;				//WinSock Async 环境数据
SOCKADDR_IN ServerAddr;		//服务器地址
SOCKET		ClientSocket;	//连接套接字 SOCKET是一个结构体 代表系统的网卡
bool		bExit = false;
HANDLE		hThread = NULL;
unsigned int threadID = 0;

unsigned __stdcall NetMain(void*)
{
	int nRcv;
	//3.进入收发数据的循环
	char Buffer[CMD_BUFFER_LENGTH] = { 0 };
	while(!bExit)
	{
		EnterCriticalSection(&E3DNet::GetInstance().p_NetCS);
		if (0 >= (nRcv = recv(ClientSocket, Buffer, sizeof(Buffer), 0)))
		{
			break;
		}
		int cmdLength = CMD_BUFFER_LENGTH;
		E3DNet::GetInstance().GetNetMsg((BYTE*)Buffer, cmdLength);
		LeaveCriticalSection(&E3DNet::GetInstance().p_NetCS);
		Sleep(1);
	}
	return 0;
}

void Send(std::string msg)
{
	send(ClientSocket, msg.c_str(), msg.length(), 0);		//发送数据 //把消息传过去
}

void Close()
{
	//4.关闭套接字
	shutdown(ClientSocket, SD_SEND);
	closesocket(ClientSocket);
	WSACleanup();	//关闭套接字环境
}

void CreateTCP(const char *ip, int port)
{
	//启动套接字环境  开启网络环境 0x0202是版本号
    WSAStartup(0x0202,&wsData);	
	//1.[建立套接字]
	ClientSocket= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(ClientSocket==INVALID_SOCKET)
	{
		WSACleanup();
		return;
	}

	//2.[连接到指定的服务器端口]
	memset(&ServerAddr,0,sizeof(ServerAddr)); 
	//地址族:网间网络地址 表示intenet网
	ServerAddr.sin_family=AF_INET;		
	//端口号转换成网络字节顺序  htons转成互联网的字节读取方向方式
	ServerAddr.sin_port=htons(port);	
	inet_pton(AF_INET, ip, (void*)&ServerAddr.sin_addr.S_un.S_addr);

	connect(ClientSocket,(SOCKADDR*)&ServerAddr,sizeof(ServerAddr));
	//创建线程
	hThread = (HANDLE)_beginthreadex(NULL, 0, &NetMain, NULL, 0, &threadID);
	
}