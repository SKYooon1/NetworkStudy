#include <iostream>
#include "../Common.h"

void getListeningPort(const char* ip, int port);

int main(int argc, char* argv[])
{
	// 扩加 檬扁拳
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	if (argc == 3)
	{
		const char* localLoopIp = const_cast<char*>("127.0.0.1");	// localLoopIp
		int min = atoi(argv[1]);
		int max = atoi(argv[2]);

		for (int port{ min }; port < max; ++port)
			getListeningPort(localLoopIp, port);
	}
	else if (argc > 3)
	{
		int min = atoi(argv[2]);
		int max = atoi(argv[3]);

		for (int port{ min }; port < max; ++port)
			getListeningPort(argv[1], port);
	}

}

void getListeningPort(const char* ip, int port)
{
	// 家南 积己
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(port);

	if (connect(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)))
	{
		std::cout << port << " is LISTENING state." << std::endl;
	}
}