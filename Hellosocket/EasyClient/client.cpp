#include<Windows.h>
#include<WinSock2.h>
#include<cstdio>

#pragma comment(lib,"ws2_32.lib")    //WSAStartup会调用一个动态库,所以，你必须包含，但这是仅仅适用于windows方法。 通用方法请在IDE中包含依赖


int main()
{
	WORD ver{ MAKEWORD(2,2) }; //版本号
	WSADATA data;
	WSAStartup(ver, &data);    //开启套接字库

	//创建套接字
	SOCKET _sock{ socket(AF_INET,SOCK_STREAM,0) };
	if (INVALID_SOCKET == _sock) {
		printf("错误,建立socket失败\n");
	}
	else { printf("建立socket成功\n"); };

	//服务器地址信息
	sockaddr_in serveraddr{};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(3456);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int ret{ connect(_sock, (sockaddr*)&serveraddr, sizeof(serveraddr)) };

	if (SOCKET_ERROR == ret) {
		printf("错误,建立连接失败\n");
	}
	else { printf("建立连接成功\n"); }

	while (true) {
		char msgbuf[256]{};
		scanf("%s", msgbuf);
		if (0 == strcmp(msgbuf, "exit")) {
			break;
		}
		send(_sock, msgbuf, 256, 0);
		
		char rcvbuf[256]{};
		int n_len{ recv(_sock,rcvbuf,sizeof(rcvbuf),0) };
		printf("%s", rcvbuf);
	}
	closesocket(_sock);
	WSACleanup();       //关闭套接字库
	return 0;
}