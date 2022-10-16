#include <iostream>
#include <fstream>
#include "../../Common.h"

int connectToServer(SOCKET& sock, const char* ip, short port);

int main(int argc, char* argv[])
{
	char* serverIP{ const_cast<char*>("127.0.0.1") };
	const short serverPort{ 9000 };
	const short bufferSize{ 512 };
	// char* fileName{ const_cast<char*>("test.mp4") };

	// ����� �μ��� ������ 1��° �μ��� ���� �̸�
	// if (argc > 1) fileName = argv[1];

	// ����� �μ��� 2�� �̻��̸� 2��° �μ��� IP
	if (argc > 2) serverIP = argv[2];

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// ���� ����
	if (connectToServer(sock, serverIP, serverPort) == SOCKET_ERROR)
		err_quit("connect()");

	// ������ ��ſ� ����� ����
	char buf[bufferSize + 1];

	// ������ ������ ���
	while (true) {
		// ������ �Է�
		printf("\n[���� ������] ");
		if (fgets(buf, bufferSize + 1, stdin) == nullptr)
			break;

		// '\n' ���� ����
		const int len = static_cast<int>(strlen(buf));
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// ������ ������
		int val = send(sock, buf, static_cast<int>(strlen(buf)), 0);
		if (val == SOCKET_ERROR)
		{
			err_display("send()");
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", val);

		// ������ �ޱ�
		val = recv(sock, buf, val, MSG_WAITALL);
		if (val == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (val == 0)
			break;

		// ���� ������ ���
		buf[val] = '\0';
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", val);
		printf("[���� ������] %s\n", buf);
	}

	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;

}

int connectToServer(SOCKET& sock, const char* ip, short port)
{
	struct sockaddr_in address {};

	address.sin_family = AF_INET;

	inet_pton(AF_INET, ip, &address.sin_addr);

	address.sin_port = htons(port);

	return connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address));
}