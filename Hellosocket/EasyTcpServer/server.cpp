#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<Windows.h>
#include<WinSock2.h>
#include<cstdio>

#pragma comment(lib,"ws2_32.lib")    //WSAStartup会调用一个动态库,所以，你必须包含，但这是仅仅适用于windows方法。 通用方法请在IDE中包含依赖


int main()
{
	WORD ver{ MAKEWORD(2,2) }; //版本号
	WSADATA data;
	WSAStartup(ver, &data);    //开启套接字库

	//构造一个监听套接字
	SOCKET _sock{ socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) };  //AF_INET表示使用IPv4协议，SOCK_STREAM表示使用面向连接的TCP协议，IPPROTO_TCP表示使用TCP传输协议
	
	sockaddr_in _sin{};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(3456);             //将主机字节序号转换为网络字节序号
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;  //INADDR_ANY 会指定一个可用的IP地址
	//绑定套接字
	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR) {
		printf("绑定套接字失败\n");
	}
	else { printf("绑定套接字成功\n"); }

	//监听套接字
	if (listen(_sock, 5) == SOCKET_ERROR) {
		printf("监听失败\n");
	}
	else { printf("监听成功\n"); }

	//等待连接
	
	sockaddr_in clientaddr;
	int len{ sizeof(clientaddr) };
	char msgbuf[]{ "Hello,I am server" };

	while (true) {

		SOCKET client_fd{ accept(_sock,(sockaddr*)&clientaddr,&len) };
		if (client_fd == INVALID_SOCKET) {
			printf("错误,接收到无效的客户端\n");
		}
		else { printf("接收到客户端 IP=%s\n",inet_ntoa(clientaddr.sin_addr)); }


		send(client_fd, msgbuf, strlen(msgbuf) + 1, 0);  //strlen不会统计结束符
	}
	closesocket(_sock);

	WSACleanup();       //关闭套接字库
	return 0;
}