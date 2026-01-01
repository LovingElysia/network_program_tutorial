#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<WinSock2.h>

//#pragma coment(lib,"ws2_32.lib")    WSAStartup会调用一个动态库,所以，你必须包含，但这是仅仅适用于windows方法。 通用方法请在IDE中包含依赖


int main()
{
	WORD ver{ MAKEWORD(2,2) }; //版本号
	WSADATA data;
	WSAStartup(ver, &data);    //开启套接字库
	 
	WSACleanup();       //关闭套接字库
	return 0;
}